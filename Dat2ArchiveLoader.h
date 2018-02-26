#ifndef VFS_DAT2_ARCHIVE_LOADER_H
#define VFS_DAT2

#include <ttvfs/VFSArchiveLoader.h>

namespace ttvfs
{
    class Dir;
    class File;
    class VFSLoader;

    class Dat2ArchiveLoader : public VFSArchiveLoader
    {
        public:
            virtual ~Dat2ArchiveLoader() {};
            virtual Dir *Load(File *arch, VFSLoader **ldr, void *opaque);
    };
}

#endif
