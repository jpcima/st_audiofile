#pragma once
#include <stdint.h>
#include <stdbool.h>
#if defined(_WIN32)
#include <wchar.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct st_audio_file st_audio_file;

typedef enum st_audio_file_type {
    st_audio_file_wav,
    st_audio_file_flac,
    st_audio_file_other,
} st_audio_file_type;

st_audio_file* st_open_file(const char* filename);
#if defined(_WIN32)
st_audio_file* st_open_file_w(const wchar_t* filename);
#endif
void st_close(st_audio_file* af);
int st_get_type(st_audio_file* af);
const char* st_get_type_string(st_audio_file* af);
const char* st_type_string(int type);
uint32_t st_get_channels(st_audio_file* af);
float st_get_sample_rate(st_audio_file* af);
uint64_t st_get_frame_count(st_audio_file* af);
bool st_seek(st_audio_file* af, uint64_t frame);
uint64_t st_read_s16(st_audio_file* af, int16_t* buffer, uint64_t count);
uint64_t st_read_f32(st_audio_file* af, float* buffer, uint64_t count);
void* st_get_internal_handle(st_audio_file* af);

#ifdef __cplusplus
} // extern "C"
#endif
