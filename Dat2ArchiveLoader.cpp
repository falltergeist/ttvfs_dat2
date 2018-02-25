#include "Dat2ArchiveLoader.h"
#include "Dat2Dir.h"
#include "Dat2ArchiveRef.h"

#include <iostream>

VFS_NAMESPACE_START

Dir *Dat2ArchiveLoader::Load(File *arch, VFSLoader ** /*unused*/, void * /*unused*/)
{
    CountedPtr<Dat2ArchiveRef> ref = new Dat2ArchiveRef(arch);
    if(!ref->init() || !ref->openRead())
        return NULL;
    Dat2Dir *vd = new Dat2Dir(ref, arch->fullname(), true);
    vd->load();
    return vd;
}

VFS_NAMESPACE_END
