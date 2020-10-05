cmake_minimum_required(VERSION 3.5)
project(st_audiofile)

option(ST_AUDIO_FILE_USE_SNDFILE "Use sndfile" OFF)

add_library(st_audiofile STATIC
  "src/st_audiofile.c"
  "src/st_audiofile_common.c"
  "src/st_audiofile_libs.c"
  "src/st_audiofile_sndfile.c")
target_include_directories(st_audiofile
  PRIVATE "thirdparty/dr_libs")

add_executable(st_info
  "src/st_info.c")
target_link_libraries(st_info
  PRIVATE st_audiofile)

if(ST_AUDIO_FILE_USE_SNDFILE)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(Sndfile "sndfile" REQUIRED)
  target_compile_definitions(st_audiofile
    PUBLIC "ST_AUDIO_FILE_USE_SNDFILE=1")
  target_include_directories(st_audiofile
    PRIVATE ${Sndfile_INCLUDE_DIRS})
  target_link_libraries(st_audiofile
    PRIVATE ${Sndfile_LIBRARIES})
  link_directories(
    ${Sndfile_LIBRARY_DIRS})
endif()
