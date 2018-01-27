cmake_minimum_required(VERSION 3.9)

include_directories(.)

add_subdirectory(ttvfs)

find_package(ZLIB REQUIRED)
if(NOT ZLIB_FOUND)
    message(FATAL_ERROR "Zlib library not found")
endif(NOT ZLIB_FOUND)
include_directories(${ZLIB_INCLUDE_DIRS})

set(SRC
        ttvfs_dat2.h
        main.cpp
        VFSDat2ArchiveLoader.cpp
        VFSDat2ArchiveLoader.h
        VFSDat2ArchiveRef.cpp
        VFSDat2ArchiveRef.h
        VFSDat2Dir.cpp
        VFSDat2Dir.h
        VFSDat2File.cpp
        VFSDat2File.h
)

link_libraries(ttvfs ${ZLIB_LIBRARIES})
add_executable(main ${SRC})
