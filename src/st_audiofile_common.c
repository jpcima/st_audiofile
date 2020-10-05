#include "st_audiofile.h"
#include <stddef.h>

const char* st_get_type_string(st_audio_file* af)
{
    return st_type_string(st_get_type(af));
}

const char* st_type_string(int type)
{
    const char *type_string = NULL;

    switch (type) {
    case st_audio_file_wav:
        type_string = "WAV";
        break;
    case st_audio_file_flac:
        type_string = "FLAC";
        break;
    case st_audio_file_other:
        type_string = "other";
        break;
    }

    return type_string;
}
