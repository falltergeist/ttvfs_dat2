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

add_library(ttvfs_dat2 ${SRC})

install(TARGETS ttvfs_dat2 DESTINATION lib)
