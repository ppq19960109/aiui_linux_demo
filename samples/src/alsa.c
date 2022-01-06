#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <alsa/asoundlib.h>

#define SAMPLE_RATE (16000)
#define CHANNELS (1)
#define FRAME_SIZE (2 * CHANNELS)

static snd_pcm_t *handle;
static snd_pcm_uframes_t frames;
static int frame_size;
static char *buffer;
static int buffer_len = 0;
static int period_frames_size;

int audio_play_init(const int rate, const int channels, const int bits_per_sample)
{
    int rc;
    int dir = 0;

    int err;

    //以播放模式打开设备
    rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0); //SND_PCM_ASYNC
    if (rc < 0)
    {
        fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
        exit(1);
    }
    //配置硬件参数结构体
    snd_pcm_hw_params_t *params;

#if 0
    unsigned int val;
    //params申请内存
    snd_pcm_hw_params_malloc(&params);

    //使用pcm设备初始化hwparams
    err = snd_pcm_hw_params_any(handle, params);
    if (err < 0)
    {
        fprintf(stderr, "Can not configure this PCM device: %s\n", snd_strerror(err));
        exit(1);
    }

    //设置多路数据在buffer中的存储方式
    //SND_PCM_ACCESS_RW_INTERLEAVED每个周期(period)左右声道的数据交叉存放
    err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (err < 0)
    {
        fprintf(stderr, "Failed to set PCM device to interleaved: %s\n", snd_strerror(err));
        exit(1);
    }

    //设置16位采样格式，S16为有符号16位,LE是小端模式
    snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;
    err = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    if (err < 0)
    {
        fprintf(stderr, "Failed to set PCM device to 16-bit signed PCM: %s\n", snd_strerror(err));
        exit(1);
    }

    //设置声道数,双声道
    err = snd_pcm_hw_params_set_channels(handle, params, channels);
    if (err < 0)
    {
        fprintf(stderr, "Failed to set PCM device to mono: %s\n", snd_strerror(err));
        exit(1);
    }

    //采样率44.1KHZ
    val = rate;
    //设置采样率,如果采样率不支持，会用硬件支持最接近的采样率
    err = snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);
    if (err < 0)
    {
        fprintf(stderr, "Failed to set PCM device to sample rate =%d: %s\n", val, snd_strerror(err));
        exit(1);
    }

    unsigned int buffer_time, period_time;
    //获取最大的缓冲时间,buffer_time单位为us,500000us=0.5s
    snd_pcm_hw_params_get_buffer_time_max(params, &buffer_time, 0);
    printf("max buffer_time:%d\n", buffer_time);
    if (buffer_time > 90 * 100000)
        buffer_time = 90 * 100000;

    //设置缓冲时间
    err = snd_pcm_hw_params_set_buffer_time_near(handle, params, &buffer_time, 0);
    if (err < 0)
    {
        fprintf(stderr, "Failed to set PCM device to buffer time =%d: %s\n", buffer_time, snd_strerror(err));
        exit(1);
    }
    
    period_time = buffer_time / 2;
    printf("period_time before:%d\n", period_time);
    //设置周期时间
    err = snd_pcm_hw_params_set_period_time_near(handle, params, &period_time, 0);
    if (err < 0)
    {
        fprintf(stderr, "Failed to set PCM device to period time =%d: %s\n", period_time, snd_strerror(err));
        exit(1);
    }
    snd_pcm_uframes_t buffer_size;
    snd_pcm_hw_params_get_buffer_size_max(params, &buffer_size);
    printf("max buffer_size before:%d\n", buffer_size);
    snd_pcm_hw_params_set_buffer_size_near(handle, params, &buffer_size);
    printf("max buffer_size:%d\n", buffer_size);
    snd_pcm_uframes_t period_size = buffer_size / 4;
    snd_pcm_hw_params_set_period_size_near(handle, params, &period_size, 0);
    printf("period_size before:%d\n", period_size);
    //让这些参数作用于PCM设备
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0)
    {
        fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
        exit(1);
    }
    snd_pcm_hw_params_get_period_time(params, &period_time, &dir);
    printf("period_time:%d\n", period_time);
#else
    if ((err = snd_pcm_set_params(handle,
                                  SND_PCM_FORMAT_S16,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  channels,
                                  rate,
                                  0,
                                  10 * 1000000)) < 0)
    {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(1);
    }

    snd_pcm_hw_params_alloca(&params);
    /* get the current hwparams */
    err = snd_pcm_hw_params_current(handle, params);
    if (err < 0)
    {
        printf("Unable to determine current params: %s\n", snd_strerror(err));
        exit(1);
    }

    if (snd_pcm_hw_params_supports_audio_ts_type(params, 0))
        printf("Playback supports audio compat timestamps\n");
    if (snd_pcm_hw_params_supports_audio_ts_type(params, 1))
        printf("Playback supports audio default timestamps\n");
    if (snd_pcm_hw_params_supports_audio_ts_type(params, 2))
        printf("Playback supports audio link timestamps\n");
    if (snd_pcm_hw_params_supports_audio_ts_type(params, 3))
        printf("Playback supports audio link absolute timestamps\n");
    if (snd_pcm_hw_params_supports_audio_ts_type(params, 4))
        printf("Playback supports audio link estimated timestamps\n");
    if (snd_pcm_hw_params_supports_audio_ts_type(params, 5))
        printf("Playback supports audio link synchronized timestamps\n");

    snd_pcm_sw_params_t *swparams_p;
    snd_pcm_sw_params_alloca(&swparams_p);
    /* get the current swparams */
    err = snd_pcm_sw_params_current(handle, swparams_p);
    if (err < 0)
    {
        printf("Unable to determine current swparams_p: %s\n", snd_strerror(err));
        exit(1);
    }
    snd_pcm_uframes_t uframes;
    snd_pcm_sw_params_get_avail_min(handle, &uframes);
    printf("avail_min : %d\n", uframes);
    // /* enable tstamp */
    // err = snd_pcm_sw_params_set_tstamp_mode(handle, swparams_p, SND_PCM_TSTAMP_ENABLE);
    // if (err < 0)
    // {
    //     printf("Unable to set tstamp mode : %s\n", snd_strerror(err));
    //     exit(1);
    // }

    // err = snd_pcm_sw_params_set_tstamp_type(handle, swparams_p, SND_PCM_TSTAMP_TYPE_MONOTONIC_RAW);
    // if (err < 0)
    // {
    //     printf("Unable to set tstamp type : %s\n", snd_strerror(err));
    //     exit(1);
    // }

    // /* write the sw parameters */
    // err = snd_pcm_sw_params(handle, swparams_p);
    // if (err < 0)
    // {
    //     printf("Unable to set swparams_p : %s\n", snd_strerror(err));
    //     exit(1);
    // }

    unsigned int buffer_time;
    snd_pcm_hw_params_get_buffer_time_max(params, &buffer_time, &dir);
    printf("get_buffer_time_max:%d\n", buffer_time);
    snd_pcm_hw_params_set_buffer_time_near(handle, params, &buffer_time, &dir);
    snd_pcm_hw_params_get_buffer_time(params, &buffer_time, &dir);
    printf("get_buffer_time:%ld\n", buffer_time);

    snd_pcm_uframes_t buffer_size;
    snd_pcm_hw_params_get_buffer_size_max(params, &buffer_size);
    printf("get_buffer_size_max:%d\n", buffer_size);
    snd_pcm_hw_params_set_buffer_size_near(handle, params, &buffer_size);
    printf("set_buffer_size_near:%d\n", buffer_size);
    snd_pcm_hw_params_get_buffer_size(params, &buffer_size);
    printf("get_buffer_size:%ld\n", buffer_size);
#endif
    unsigned int frame_time;

    snd_pcm_hw_params_get_period_time(params, &frame_time, &dir);
    printf("period_time:%ld\n", frame_time);
    snd_pcm_hw_params_get_period_size(params, &frames, &dir);
    printf("period_size frames:%ld\n", frames);
    // 1 frame = channels * sample_size.
    frame_size = channels * (bits_per_sample / 8);
    period_frames_size = frames * frame_size; /* 2 bytes/sample, 1 channels */
    printf("frame_size:%d,period_frames_size:%d dir:%d\n", frame_size, period_frames_size, dir);
    buffer = (char *)malloc(period_frames_size);
    return 0;
}
void audio_play_start(void)
{
    int err;
    // err = snd_pcm_drop(handle);
    // if (err < 0)
    // {
    //     fprintf(stderr, "snd_pcm_drain: %s\n", snd_strerror(err));
    // }
    // err = snd_pcm_prepare(handle);
    // if (err < 0)
    // {
    //     fprintf(stderr, "can not recover: %s\n", snd_strerror(err));
    // }
}
void audio_play_end(void)
{
    int err;
    // err = snd_pcm_drain(handle);
    // if (err < 0)
    // {
    //     fprintf(stderr, "snd_pcm_drain: %s\n", snd_strerror(err));
    // }
    // err = snd_pcm_wait(handle, 2000);
    // if (err < 0)
    // {
    //     fprintf(stderr, "snd_pcm_wait: %s\n", snd_strerror(err));
    snd_pcm_sframes_t sframes = snd_pcm_avail(handle);
    printf("snd_pcm_avail:%d\n", sframes);
}
int audio_play(char *data, int len, const char last)
{
    snd_pcm_uframes_t uframes;
    while (len > 0)
    {
        if (buffer_len + len <= period_frames_size)
        {
            memcpy(&buffer[buffer_len], data, len);
            buffer_len += len;

            uframes = buffer_len / frame_size;

            len = 0;
            if (last == 0)
                return 0;
            else
                buffer_len = 0;
        }
        else
        {
            memcpy(&buffer[buffer_len], data, period_frames_size - buffer_len);

            uframes = frames;
            buffer_len = 0;
            len -= period_frames_size - buffer_len;
        }

        int rc, err;
        rc = snd_pcm_writei(handle, buffer, uframes); //rc / FRAME_SIZE
        if (rc == -EPIPE)
        {
            fprintf(stderr, "underrun occurred\n");
            err = snd_pcm_prepare(handle);
            if (err < 0)
            {
                fprintf(stderr, "can not recover from underrun: %s\n", snd_strerror(err));
            }
        }
        else if (rc < 0)
        {
            fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
        }
        else if (rc != uframes)
        {
            fprintf(stderr, "short write, write %d frames\n", rc);
        }
        // snd_pcm_delay(handle,1000);
        usleep(10*1000);
    }
    return 0;
}

void audio_play_deinit(void)
{
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);
}