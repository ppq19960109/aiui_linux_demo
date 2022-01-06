#ifndef _ALSA_H_
#define _ALSA_H_
#ifdef __cplusplus
extern "C"
{
#endif /* C++ */

    int audio_play_init(const int rate, const int channels, const int bits_per_sample);
    int audio_play(char *data, int len, const char last);
    void audio_play_end(void);
    void audio_play_start(void);
    void audio_play_deinit(void);
#ifdef __cplusplus
} /* extern "C" */
#endif /* C++ */
#endif