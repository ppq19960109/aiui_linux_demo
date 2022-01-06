#ifdef _WIN32
#include <windows.h>
#define AIUI_SLEEP Sleep
#else
#include <unistd.h>
#define AIUI_SLEEP(x) usleep(x * 1000)
#endif

#undef AIUI_LIB_COMPILING
#include "speech_recognizer.h"
#include "aiui/AIUI_V2.h"
#include "json/json.h"
#include <fstream>
#include <iostream>
#include <thread>
#include "alsa.h"
using namespace std;
using namespace VA;
using namespace aiui_v2;
/* wav音频头部格式 */
typedef struct _wave_pcm_hdr
{
    char riff[4]; // = "RIFF"
    int size_8;   // = FileSize - 8
    char wave[4]; // = "WAVE"
    char fmt[4];  // = "fmt "
    int fmt_size; // = 下一个结构体的大小 : 16

    short int format_tag;      // = PCM : 1
    short int channels;        // = 通道数 : 1
    int samples_per_sec;       // = 采样率 : 8000 | 6000 | 11025 | 16000
    int avg_bytes_per_sec;     // = 每秒字节数 : samples_per_sec * bits_per_sample / 8
    short int block_align;     // = 每采样点字节数 : wBitsPerSample / 8
    short int bits_per_sample; // = 量化比特数: 8 | 16

    char data[4];  // = "data";
    int data_size; // = 纯数据长度 : FileSize - 44
} wave_pcm_hdr;

wave_pcm_hdr default_wav_hdr =
    {
        {'R', 'I', 'F', 'F'},
        0,
        {'W', 'A', 'V', 'E'},
        {'f', 'm', 't', ' '},
        16,
        1,
        1,
        16000,
        32000,
        2,
        16,
        {'d', 'a', 't', 'a'},
        0};

class MyListener : public IAIUIListener
{
public:
    void onEvent(const IAIUIEvent &event) override
    {
        try
        {
            __onEvent(event);
        }
        catch (std::exception &e)
        {
            printf("%s", e.what());
        }
    }

private:
    void __onEvent(const IAIUIEvent &event)
    {
        printf("__onEvent:%d\n", event.getEventType());
        switch (event.getEventType())
        {
        //SDK 状态回调
        case AIUIConstant::EVENT_STATE:
        {
            switch (event.getArg1())
            {
            case AIUIConstant::STATE_IDLE:
            {
                cout << "EVENT_STATE:"
                     << "IDLE" << endl;
            }
            break;

            case AIUIConstant::STATE_READY:
            {
                cout << "EVENT_STATE:"
                     << "READY" << endl;
            }
            break;

            case AIUIConstant::STATE_WORKING:
            {
                cout << "EVENT_STATE:"
                     << "WORKING" << endl;
            }
            break;
            }
        }
        break;

            //唤醒事件回调
        case AIUIConstant::EVENT_WAKEUP:
        {
            cout << "EVENT_WAKEUP:" << event.getInfo() << endl;
        }
        break;

            //休眠事件回调
        case AIUIConstant::EVENT_SLEEP:
        {
            cout << "EVENT_SLEEP:arg1=" << event.getArg1() << endl;
        }
        break;

            //VAD事件回调，如找到前后端点
        case AIUIConstant::EVENT_VAD:
        {
            switch (event.getArg1())
            {
            case AIUIConstant::VAD_BOS:
            {
                cout << "EVENT_VAD: BOS" << endl;
            }
            break;

            case AIUIConstant::VAD_EOS:
            {
                cout << "EVENT_VAD: EOS" << endl;
            }
            break;

            case AIUIConstant::VAD_VOL:
            {
            }
            break;
            }
        }
        break;
        case AIUIConstant::EVENT_TTS:
        {
            cout << "EVENT_TTS" << endl;
            switch (event.getArg1())
            {
            case AIUIConstant::TTS_SPEAK_BEGIN:
                cout << "开始播放" << endl;
                break;
            case AIUIConstant::TTS_SPEAK_PROGRESS:
                // cout << "缓冲进度为" + "mTtsBufferProgress" + ", 播放进度为" + event.getData().getInt("percent") << endl; // 播放进度

                break;
            case AIUIConstant::TTS_SPEAK_PAUSED:
                cout << "暂停播放" << endl;
                break;

            case AIUIConstant::TTS_SPEAK_RESUMED:
                cout << "恢复播放" << endl;
                break;

            case AIUIConstant::TTS_SPEAK_COMPLETED:
                cout << "播放完成" << endl;
                break;
            }
        }
        break;

            //最重要的结果事件回调
        case AIUIConstant::EVENT_RESULT:
        {
            Json::Value bizParamJson;
            Json::Reader reader;

            if (!reader.parse(event.getInfo(), bizParamJson, false))
            {
                cout << "parse error!" << endl
                     << event.getInfo() << endl;
                break;
            }
            // cout << bizParamJson.toStyledString() << endl;
            Json::Value &data = (bizParamJson["data"])[0];
            Json::Value &params = data["params"];
            Json::Value &content = (data["content"])[0];

            string sub = params["sub"].asString();

            if (sub == "nlp" || sub == "iat" || sub == "tts" || sub == "asr" ||
                sub == "esr_pgs" || sub == "esr_fsa" || sub == "esr_iat")
            {
                Json::Value empty;
                Json::Value contentId = content.get("cnt_id", empty);

                if (contentId.empty())
                {
                    cout << "Content Id is empty" << endl;
                    break;
                }

                string cnt_id = contentId.asString();
                int dataLen = 0;
                const char *buffer = event.getData()->getBinary(cnt_id.c_str(), &dataLen);

                if (sub == "tts")
                {
                    std::cout << "tts result: " << dataLen << std::endl;
                    Json::Value &&isUrl = content.get("url", empty);

                    if (isUrl.asString() == "1")
                    {
                        std::cout << string(buffer, dataLen) << std::endl;
                    }
                    else
                    {
                        Json::Value dts = content.get("dts", empty);
                        if (dts.empty())
                        {
                            cout << "dts is empty" << endl;
                            break;
                        }
                        std::cout << "tts dts: " << dts.asInt() << std::endl;
#if 0
                        static FILE *fp = NULL;

                        if (dts.asInt() == 0)
                        {
                            default_wav_hdr.size_8 = 0;
                            default_wav_hdr.data_size = 0;

                            fp = fopen("aiui_tts.wav", "wb");
                            if (NULL == fp)
                            {
                                printf("open %s error.\n", "aiui_tts.wav");
                                break;
                            }
                            fwrite(&default_wav_hdr, sizeof(default_wav_hdr), 1, fp);
                            fwrite(buffer, dataLen, 1, fp);
                            default_wav_hdr.data_size += dataLen; //计算data_size大小
                        }
                        else if (dts.asInt() == 2)
                        {
                            /* 修正wav文件头数据的大小 */
                            default_wav_hdr.size_8 += default_wav_hdr.data_size + (sizeof(default_wav_hdr) - 8);
                            /* 将修正过的数据写回文件头部,音频文件为wav格式 */
                            fseek(fp, 4, 0);
                            fwrite(&default_wav_hdr.size_8, sizeof(default_wav_hdr.size_8), 1, fp);       //写入size_8的值
                            fseek(fp, 40, 0);                                                             //将文件指针偏移到存储data_size值的位置
                            fwrite(&default_wav_hdr.data_size, sizeof(default_wav_hdr.data_size), 1, fp); //写入data_size的值
                            fclose(fp);
                            fp = NULL;
                        }
                        else
                        {
                            fwrite(buffer, dataLen, 1, fp);
                            default_wav_hdr.data_size += dataLen; //计算data_size大小
                        }
#else
                        if (dts.asInt() == 0)
                        {
                            // audio_play_init(16000, 1, 16);
                            audio_play_start();
                            audio_play((char *)buffer, dataLen, 0);
                        }
                        else if (dts.asInt() == 2)
                        {
                            audio_play((char *)buffer, dataLen, 1);
                            audio_play_end();
                            // audio_play_deinit();
                        }
                        else
                        {
                            audio_play((char *)buffer, dataLen, 0);
                        }

#endif
                    }
                }
                else
                {
                    if (buffer)
                    {
                        string resultStr = string(buffer, dataLen);
                        cout << sub << ": " << event.getInfo() << endl
                             << resultStr << endl;
                    }
                }
            }
        }
        break;

            //上传资源数据的返回结果
        case AIUIConstant::EVENT_CMD_RETURN:
        {
            if (AIUIConstant::CMD_BUILD_GRAMMAR == event.getArg1())
            {
                if (event.getArg2() == 0)
                {
                    cout << "build grammar success." << endl;
                }
                else
                {
                    cout << "build grammar error, errcode = " << event.getArg2() << endl;
                    cout << "error reasion is " << event.getInfo() << endl;
                }
            }
            else if (AIUIConstant::CMD_UPDATE_LOCAL_LEXICON == event.getArg1())
            {
                if (event.getArg2() == 0)
                {
                    cout << "update lexicon success" << endl;
                }
                else
                {
                    cout << "update lexicon error, errcode = " << event.getArg2() << endl;
                    cout << "error reasion is " << event.getInfo() << endl;
                }
            }
        }
        break;

        case AIUIConstant::EVENT_ERROR:
        {
            cout << "EVENT_ERROR:" << event.getArg1() << endl;
            cout << " ERROR info is " << event.getInfo() << endl;
        }
        break;
        }
    }
};

MyListener listener;

#define TEST_ROOT_DIR "./AIUI/"
#define CFG_FILE_PATH "./AIUI/cfg/aiui.cfg"
#define TEST_AUDIO_PATH "./AIUI/audio/test.pcm"
#define LOG_DIR "./AIUI/log/"
#define MSC_DIR "./AIUI/msc/"

string readFileAsString(const string &path)
{
    std::ifstream t(path, std::ios_base::in | std::ios::binary);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    return str;
}

streamsize Read(istream &stream, char *buffer, streamsize count)
{
    // This consistently fails on gcc (linux) 4.8.1 with failbit set on read
    // failure. This apparently never fails on VS2010 and VS2013 (Windows 7)
    streamsize reads = stream.rdbuf()->sgetn(buffer, count);

    // This rarely sets failbit on VS2010 and VS2013 (Windows 7) on read
    // failure of the previous sgetn()
    stream.rdstate();

    // On gcc (linux) 4.8.1 and VS2010/VS2013 (Windows 7) this consistently
    // sets eofbit when stream is EOF for the conseguences  of sgetn(). It
    // should also throw if exceptions are set, or return on the contrary,
    // and previous rdstate() restored a failbit on Windows. On Windows most
    // of the times it sets eofbit even on real read failure
    stream.peek();

    return reads;
}

IAIUIAgent *agent = nullptr;

void createAgent()
{
    if (agent)
    {
        return;
    }

    Json::Value paramJson;

    std::cout << CFG_FILE_PATH << std::endl;

    string fileParam = readFileAsString(CFG_FILE_PATH);

    Json::Reader reader;
    if (reader.parse(fileParam, paramJson, false))
    {
        agent = IAIUIAgent::createAgent(paramJson.toStyledString().c_str(), &listener);
    }

    if (!agent)
    {
        std::cout << "create agent fail" << std::endl;
    }
    else
    {
        std::cout << "create agent sucess" << std::endl;
    }
}

void wakeup()
{
    if (NULL != agent)
    {
        IAIUIMessage *wakeupMsg = IAIUIMessage::create(AIUIConstant::CMD_WAKEUP);
        agent->sendMessage(wakeupMsg);
        wakeupMsg->destroy();
    }
}

void reset_wakeup()
{
    if (NULL != agent)
    {
        IAIUIMessage *wakeupMsg = IAIUIMessage::create(AIUIConstant::CMD_RESET_WAKEUP);
        agent->sendMessage(wakeupMsg);
        wakeupMsg->destroy();
    }
}

//停止AIUI服务，此接口是与stop()对应，调用stop()之后必须调用此接口才能继续与SDK交互，如果你没有调用过stop(),就不需要调用该接口
void start()
{
    if (NULL != agent)
    {
        IAIUIMessage *startMsg = IAIUIMessage::create(AIUIConstant::CMD_START);
        agent->sendMessage(startMsg);
        startMsg->destroy();
    }
}

//停止AIUI服务
void stop()
{
    if (NULL != agent)
    {
        IAIUIMessage *stopMsg = IAIUIMessage::create(AIUIConstant::CMD_STOP);
        agent->sendMessage(stopMsg);
        stopMsg->destroy();
    }
}

struct speech_rec iat;
struct speech_rec_notifier recnotifier = {0};

static void writeAudioRecord(char *data, unsigned int len)
{
    AIUIBuffer textData = aiui_create_buffer_from_data(data, len);

    IAIUIMessage *writeMsg = IAIUIMessage::create(
        AIUIConstant::CMD_WRITE,
        0,
        0,
        "data_type=audio",
        textData);

    agent->sendMessage(writeMsg);
    writeMsg->destroy();
}
/* demo recognize the audio from microphone */
static void mic_start()
{
    printf("mic_start\n");
    int errcode;

    errcode = sr_init(&iat, NULL, SR_MIC, &recnotifier);
    if (errcode)
    {
        printf("speech recognizer init failed\n");
        return;
    }
    iat.write_recorder_data = writeAudioRecord;
    errcode = sr_start_listening(&iat);
    if (errcode)
    {
        printf("start listen failed %d\n", errcode);
    }
}
static void mic_stop()
{
    printf("mic_stop\n");
    int errcode = sr_stop_listening(&iat);
    if (errcode)
    {
        printf("stop listening failed %d\n", errcode);
    }

    IAIUIMessage *msg = IAIUIMessage::create(
        AIUIConstant::CMD_STOP_WRITE,
        0,
        0,
        "data_type=audio");
    agent->sendMessage(msg);
    msg->destroy();

    sr_uninit(&iat);
}
// 写入测试音频
void writeAudio()
{
    // if (NULL != agent) {
    //     IAIUIMessage* stopMsg =
    //         IAIUIMessage::create(AIUIConstant::CMD_START_RECORD, 0, 0, "data_type=audio");
    //     agent->sendMessage(stopMsg);
    //     stopMsg->destroy();
    // }
    mic_start();
}

void stopAudio()
{
    // if (NULL != agent)
    // {
    //     IAIUIMessage *stMsg = IAIUIMessage::create(AIUIConstant::CMD_STOP_RECORD);
    //     agent->sendMessage(stMsg);
    //     stMsg->destroy();

    //     IAIUIMessage *stopMsg =
    //         IAIUIMessage::create(AIUIConstant::CMD_STOP_SAVE, 0, 0, "data_type=raw_audio");
    //     agent->sendMessage(stopMsg);
    //     stopMsg->destroy();
    // }
    mic_stop();
}

void writeAudioFromLocal()
{
    if (NULL != agent)
    {
        ifstream testData(TEST_AUDIO_PATH, std::ios::in | std::ios::binary);

        if (testData.is_open())
        {
            char buff[1280];
            while (testData.good() && !testData.eof())
            {
                memset(buff, '\0', 1280);
                testData.read(buff, 1280);

                // textData内存会在Message在内部处理完后自动release掉
                AIUIBuffer textData = aiui_create_buffer_from_data(buff, 1280);

                IAIUIMessage *writeMsg = IAIUIMessage::create(
                    AIUIConstant::CMD_WRITE,
                    0,
                    0,
                    "data_type=audio",
                    textData);

                agent->sendMessage(writeMsg);
                writeMsg->destroy();

                // 必须暂停一会儿模拟人停顿，太快的话后端报错
                AIUI_SLEEP(40);
            }

            testData.close();

            IAIUIMessage *msg = IAIUIMessage::create(
                AIUIConstant::CMD_STOP_WRITE,
                0,
                0,
                "data_type=audio");
            agent->sendMessage(msg);
            msg->destroy();
        }
        else
        {
            printf("file[%s] open error", TEST_AUDIO_PATH);
        }
    }
}

//文本语义测试接口
void writeText()
{
    if (NULL != agent)
    {
        string text = "合肥明天天气怎么样";

        // textData内存会在Message在内部处理完后自动release掉
        AIUIBuffer textData = aiui_create_buffer_from_data(text.c_str(), text.length());

        IAIUIMessage *writeMsg = IAIUIMessage::create(
            AIUIConstant::CMD_WRITE, 0, 0, "data_type=text,tts_res_type=url", textData);

        agent->sendMessage(writeMsg);
        writeMsg->destroy();
    }
}

void testTTs()
{
    if (NULL != agent)
    {
        string text = "敕勒川，阴山下。天似穹庐，笼盖四野。天苍苍，野茫茫。风吹草低见牛羊。";

        AIUIBuffer textData = aiui_create_buffer_from_data(text.c_str(), text.length());

        IAIUIMessage *ttsMsg = IAIUIMessage::create(
            AIUIConstant::CMD_TTS, 1, 0, "text_encoding=utf-8,vcn=x2_xiaojuan,speed=30", textData);

        agent->sendMessage(ttsMsg);
        ttsMsg->destroy();
    }
}

void testTTs2()
{
    if (NULL != agent)
    {
        string text = "敕勒川，阴山下。天似穹庐，笼盖四野。天苍苍，野茫茫。风吹草低见牛羊。";
        // textData内存会在Message在内部处理完后自动release掉
        AIUIBuffer textData = aiui_create_buffer_from_data(text.c_str(), text.length());

        IAIUIMessage *ttsMsg = IAIUIMessage::create(
            AIUIConstant::CMD_TTS, 1, 0, "text_encoding=utf-8,tts_res_type=url", textData);

        agent->sendMessage(ttsMsg);
        ttsMsg->destroy();
    }
}

void destroy()
{
    if (NULL != agent)
    {
        agent->destroy();
        agent = NULL;
    }
}

void buildGrammar()
{
    if (NULL != agent)
    {
        string grammer = readFileAsString("AIUI/asr/call.bnf");

        auto msg =
            IAIUIMessage::create(AIUIConstant::CMD_BUILD_GRAMMAR, 0, 0, grammer.c_str(), NULL);
        agent->sendMessage(msg);
        msg->destroy();
    }
}

void help()
{
    static string s =
        "demo示例为输入命令，调用对应的函数，使用AIUI "
        "SDK完成文本理解，语义理解，文本合成等功能，如：\r\n"
        "c命令，创建AIUI代理，与AIUI SDK交互都是通过代理发送消息的方式进行, "
        "所以第一步必须是输入该命令；\r\n"
        "s命令，初始化内部组件 第二步；\r\n"
        "w命令，发送外部唤醒命令唤醒AIUI，AIUI只有在唤醒过后才可以交互；第三步\r\n"
        "rw命令，发送外部休眠命令 AIUI进入休眠状态\r\n"
        "wo令，sdk内部启动4麦录音 sdk会返回云端识别的听写，语义结果；\r\n"
        "so命令，停止内部4麦录音\r\n"
        "wrt命令，字符串文本写入sdk，sdk会返回云端识别的语义结果；\r\n"
        "wra命令， 音频文件写入sdk，sdk会返回云端识别的语义结果；\r\n"
        "tts命令，单合成示例，返回合成的音频，demo将音频保存为本地的pcm文件；\r\n"
        "stts命令，单合成示例，返回合成的音频的url保存为本地的txt文件；\r\n"
        "bg命令，构建语法\r\n"
        "help命令，显示本demo提供的示例的介绍；\r\n"
        "输入c命令后，正常情况返回结果为：\r\n"
        "EVENT_STATE:READY\r\n"
        "输入w命令后，正常情况返回结果为: \r\n"
        "EVENT_WAKEUP\r\n"
        "EVENT_STATE:WORKING\r\n"
        "听写，语义，合成等结果在onEvent函数，该函数是结果回调，请仔细研究。\r\n"
        "内部录音流程 c -> s -> w -> wo\r\n"
        "input cmd:";

    cout << s << endl;
}
#define AIUI_LINUX
#ifdef AIUI_LINUX
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>

static void GenerateMACAddress(char *mac)
{
    // reference: https://stackoverflow.com/questions/1779715/how-to-get-mac-address-of-your-machine-using-a-c-program/35242525
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        return;
    };

    struct ifconf ifc;
    char buf[1024];
    int success = 0;

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1)
    {
        return;
    }

    struct ifreq *it = ifc.ifc_req;
    const struct ifreq *const end = it + (ifc.ifc_len / sizeof(struct ifreq));
    struct ifreq ifr;

    for (; it != end; ++it)
    {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0)
        {
            if (!(ifr.ifr_flags & IFF_LOOPBACK))
            { // don't count loopback
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0)
                {
                    success = 1;
                    break;
                }
            }
        }
        else
        {
            return;
        }
    }

    unsigned char mac_address[6];
    if (success)
        memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);

    sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", mac_address[0], mac_address[1], mac_address[2], mac_address[3], mac_address[4], mac_address[5]);
}
#elif defined(AIUI_WINDOWS)
#include <stdio.h>
#include <IPHlpApi.h>
#pragma comment(lib, "IPHLPAPI.lib")

static void GenerateMACAddress(char *mac)
{
    ULONG ulSize = 0;
    PIP_ADAPTER_INFO adapterInfo = NULL;
    PIP_ADAPTER_INFO adapterInfoTmp = NULL;

    GetAdaptersInfo(adapterInfo, &ulSize);

    if (0 == ulSize)
    {
        return;
    }

    adapterInfo = (PIP_ADAPTER_INFO)malloc(ulSize);

    if (adapterInfo == NULL)
    {
        return;
    }

    memset(adapterInfo, 0, ulSize);

    adapterInfoTmp = adapterInfo;

    GetAdaptersInfo(adapterInfo, &ulSize);

    while (adapterInfo)
    {

        _snprintf(mac,
                  64,
                  "%02x:%02x:%02x:%02x:%02x:%02x",
                  adapterInfo->Address[0],
                  adapterInfo->Address[1],
                  adapterInfo->Address[2],
                  adapterInfo->Address[3],
                  adapterInfo->Address[4],
                  adapterInfo->Address[5]);

        if (std::strcmp(adapterInfo->GatewayList.IpAddress.String, "0.0.0.0") != 0)
            break;

        adapterInfo = adapterInfo->Next;
    }

    free(adapterInfoTmp);

    adapterInfoTmp = NULL;
}
#endif

#define AIUI_KEY_SERIAL_NUM "sn"
#define AIUI_KEY_AUTH_PUBLIC_KEY "auth_public_key"
#define AIUI_KEY_AUTH_PRIVATE_KEY "auth_private_key"

int main()
{
#ifdef WIN32
    system("chcp 65001 >nul");
#endif

    std::cout << "Version: " << getVersion() << std::endl;

    help();

    AIUISetting::setAIUIDir(TEST_ROOT_DIR);
    AIUISetting::setMscDir(MSC_DIR);

    AIUISetting::setNetLogLevel(_debug);
    AIUISetting::setLogLevel(_debug);

    char mac[64] = {0};
    GenerateMACAddress(mac); // 设备唯一ID, 可自己重新实现

    printf("sn is: %s\n", mac);

    //为每一个设备设置对应唯一的SN（最好使用设备硬件信息(mac地址，设备序列号等）生成），以便正确统计装机量，避免刷机或者应用卸载重装导致装机量重复计数
    AIUISetting::setSystemInfo(AIUI_KEY_SERIAL_NUM, mac);

    string cmd;
    audio_play_init(16000, 1, 16);
    createAgent();
    start();
    wakeup();
    while (true)
    {
        cin >> cmd;

        if (cmd == "c")
        {
            cout << "createAgent" << endl;
            createAgent();
        }
        else if (cmd == "w")
        {
            cout << "wakeup" << endl;
            wakeup();
        }
        else if (cmd == "rw")
        {
            cout << "wakeup" << endl;
            reset_wakeup();
        }
        else if (cmd == "s")
        {
            cout << "start" << endl;
            start();
        }
        else if (cmd == "st")
        {
            cout << "stop" << endl;
            stop();
        }
        else if (cmd == "d")
        {
            cout << "destroy" << endl;
            destroy();
        }
        else if (cmd == "e")
        {
            cout << "exit" << endl;
            break;
        }
        else if (cmd == "wo")
        {
            cout << "start record" << endl;
            writeAudio();
        }
        else if (cmd == "so")
        {
            cout << "stop record" << endl;
            stopAudio();
        }
        else if (cmd == "wrt")
        {
            cout << "writeText" << endl;
            writeText();
        }
        else if (cmd == "wra")
        {
            cout << "writeAudio" << endl;
            writeAudioFromLocal();
        }
        else if (cmd == "stts")
        {
            testTTs2();
        }
        else if (cmd == "tts")
        {
            testTTs();
        }
        else if (cmd == "bg")
        {
            buildGrammar();
        }
        else if (cmd == "q")
        {
            audio_play_deinit();
            destroy();

            break;
        }
        else if (cmd == "h")
        {
            help();
        }
        else
        {
            cout << "invalid cmd, input again." << endl;
        }
    }
}
