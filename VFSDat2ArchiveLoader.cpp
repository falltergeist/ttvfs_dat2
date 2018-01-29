#include <VFSInternal.h>
#include "VFSDat2ArchiveLoader.h"
#include "VFSDat2Dir.h"
#include "VFSDat2ArchiveRef.h"

#include <iostream>

VFS_NAMESPACE_START

Dir *VFSDat2ArchiveLoader::Load(File *arch, VFSLoader ** /*unused*/, void * /*unused*/)
{
    CountedPtr<Dat2ArchiveRef> ref = new Dat2ArchiveRef(arch);
    if(!ref->init() || !ref->openRead())
        return NULL;
    Dat2Dir *vd = new Dat2Dir(ref, arch->fullname(), true);
    vd->load();
    return vd;
}

VFS_NAMESPACE_END
