cmake_minimum_required(VERSION 3.2)

set(SRC
    ttvfs_dat2.h
    Dat2ArchiveLoader.cpp
    Dat2ArchiveLoader.h
    Dat2ArchiveRef.cpp
    Dat2ArchiveRef.h
    Dat2Dir.cpp
    Dat2Dir.h
    Dat2File.cpp
    Dat2File.h
    miniz.c
    miniz.h
)

set(TTVFS_DAT2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "ttvfs_dat2 include directory - for external includers" FORCE)

add_library(ttvfs_dat2 ${SRC})

install(TARGETS ttvfs_dat2 DESTINATION lib)

install(DIRECTORY ./ DESTINATION include/ttvfs_dat2 FILES_MATCHING PATTERN "*.h")
