#pragma once
#include "st_audiofile.h"

class ST_AudioFile {
public:
    constexpr ST_AudioFile() noexcept;
    ~ST_AudioFile() noexcept;

    ST_AudioFile(const ST_AudioFile&) = delete;
    ST_AudioFile& operator=(const ST_AudioFile&) = delete;

    explicit operator bool() const noexcept;
    void reset(st_audio_file* new_af = nullptr) noexcept;

    bool open_file(const char* filename);
#if defined(_WIN32)
    bool open_file_w(const wchar_t* filename);
#endif

    int get_type() const noexcept;
    const char* get_type_string() const noexcept;
    static const char* type_string(int type) noexcept;
    uint32_t get_channels() const noexcept;
    float get_sample_rate() const noexcept;
    uint64_t get_frame_count() const noexcept;

    bool seek(uint64_t frame) noexcept;
    uint64_t read_s16(int16_t* buffer, uint64_t count) noexcept;
    uint64_t read_f32(float* buffer, uint64_t count) noexcept;

    st_audio_file* get_handle() const noexcept;
    void* get_internal_handle() const noexcept;

private:
    st_audio_file* af_ = nullptr;
};

//------------------------------------------------------------------------------

inline constexpr ST_AudioFile::ST_AudioFile() noexcept
{
}

inline ST_AudioFile::~ST_AudioFile() noexcept
{
    reset();
}

inline ST_AudioFile::operator bool() const noexcept
{
    return af_ != nullptr;
}

inline void ST_AudioFile::reset(st_audio_file* new_af) noexcept
{
    if (af_ != new_af) {
        if (af_)
            st_close(af_);
        af_ = new_af;
    }
}

bool ST_AudioFile::open_file(const char* filename)
{
    st_audio_file* new_af = st_open_file(filename);
    reset(new_af);
    return new_af != nullptr;
}
#if defined(_WIN32)
inline bool ST_AudioFile::open_file_w(const wchar_t* filename)
{
    st_audio_file* new_af = st_open_file_w(filename);
    reset(new_af);
    return new_af != nullptr;
}
#endif

inline int ST_AudioFile::get_type() const noexcept
{
    return st_get_type(af_);
}

inline const char* ST_AudioFile::get_type_string() const noexcept
{
    return st_get_type_string(af_);
}

inline const char* ST_AudioFile::type_string(int type) noexcept
{
    return st_type_string(type);
}

inline uint32_t ST_AudioFile::get_channels() const noexcept
{
    return st_get_channels(af_);
}

inline float ST_AudioFile::get_sample_rate() const noexcept
{
    return st_get_sample_rate(af_);
}

inline uint64_t ST_AudioFile::get_frame_count() const noexcept
{
    return st_get_frame_count(af_);
}

inline bool ST_AudioFile::seek(uint64_t frame) noexcept
{
    return st_seek(af_, frame);
}

inline uint64_t ST_AudioFile::read_s16(int16_t* buffer, uint64_t count) noexcept
{
    return st_read_s16(af_, buffer, count);
}

inline uint64_t ST_AudioFile::read_f32(float* buffer, uint64_t count) noexcept
{
    return st_read_f32(af_, buffer, count);
}

inline st_audio_file* ST_AudioFile::get_handle() const noexcept
{
    return af_;
}

inline void* ST_AudioFile::get_internal_handle() const noexcept
{
    return st_get_internal_handle(af_);
}
