#ifndef VFS_DAT2_ARCHIVE_LOADER_H
#define VFS_DAT2

#include <ttvfs.h>
#include <VFSArchiveLoader.h>

VFS_NAMESPACE_START

class Dat2ArchiveLoader : public VFSArchiveLoader
{
public:
    virtual ~Dat2ArchiveLoader() {}
    virtual Dir *Load(File *arch, VFSLoader **ldr, void *opaque = NULL);
};

VFS_NAMESPACE_END

#endif
