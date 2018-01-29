set(SRC
        ttvfs_dat2.h
        VFSDat2ArchiveLoader.cpp
        VFSDat2ArchiveLoader.h
        VFSDat2ArchiveRef.cpp
        VFSDat2ArchiveRef.h
        VFSDat2Dir.cpp
        VFSDat2Dir.h
        VFSDat2File.cpp
        VFSDat2File.h
        miniz.c
        miniz.h
)

set(TTVFS_DAT2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "ttvfs_dat2 include directory - for external includers" FORCE)

add_library(ttvfs_dat2 ${SRC})

install(TARGETS ttvfs_dat2 DESTINATION lib)
