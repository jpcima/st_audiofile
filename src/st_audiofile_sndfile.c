#include "st_audiofile.h"
#if defined(ST_AUDIO_FILE_USE_SNDFILE)
#if defined(_WIN32)
#include <windows.h>
#define ENABLE_SNDFILE_WINDOWS_PROTOTYPES 1
#endif
#include <sndfile.h>
#include <stdlib.h>

struct st_audio_file {
    SNDFILE* snd;
    SF_INFO info;
};

st_audio_file* st_open_file(const char* filename)
{
    st_audio_file* af = (st_audio_file*)malloc(sizeof(st_audio_file));
    if (!af)
        return NULL;

    af->snd = sf_open(filename, SFM_READ, &af->info);
    if (!af->snd) {
        free(af);
        return NULL;
    }

    return af;
}

#if defined(_WIN32)
st_audio_file* st_open_file_w(const wchar_t* filename)
{
    st_audio_file* af = (st_audio_file*)malloc(sizeof(st_audio_file));
    if (!af)
        return NULL;

    af->snd = sf_wchar_open(filename, SFM_READ, &af->info);
    if (!af->snd) {
        free(af);
        return NULL;
    }

    return af;
}
#endif

void st_close(st_audio_file* af)
{
    if (af->snd) {
        sf_close(af->snd);
        af->snd = NULL;
    }
}

int st_get_type(st_audio_file* af)
{
    int format = st_audio_file_other;

    switch (af->info.format & SF_FORMAT_TYPEMASK) {
    case SF_FORMAT_WAV:
        format = st_audio_file_wav;
        break;
    case SF_FORMAT_FLAC:
        format = st_audio_file_flac;
        break;
    }

    return format;
}

uint32_t st_get_channels(st_audio_file* af)
{
    return af->info.channels;
}

float st_get_sample_rate(st_audio_file* af)
{
    return af->info.samplerate;
}

uint64_t st_get_frame_count(st_audio_file* af)
{
    return af->info.frames;
}

bool st_seek(st_audio_file* af, uint64_t frame)
{
    return sf_seek(af->snd, frame, SEEK_SET) != -1;
}

uint64_t st_read_s16(st_audio_file* af, int16_t* buffer, uint64_t count)
{
    return sf_readf_short(af->snd, buffer, count);
}

uint64_t st_read_f32(st_audio_file* af, float* buffer, uint64_t count)
{
    return sf_readf_float(af->snd, buffer, count);
}

void* st_get_internal_handle(st_audio_file* af)
{
    return af->snd;
}

#endif // defined(ST_AUDIO_FILE_USE_SNDFILE)
