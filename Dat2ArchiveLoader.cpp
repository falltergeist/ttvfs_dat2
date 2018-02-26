#include <iostream>
#include <ttvfs/VFSFile.h>
#include "Dat2ArchiveLoader.h"
#include "Dat2ArchiveRef.h"
#include "Dat2Dir.h"

namespace ttvfs
{
    Dir *Dat2ArchiveLoader::Load(File *archive, VFSLoader ** /*unused*/, void * /*unused*/)
    {
        CountedPtr <Dat2ArchiveRef> ref = new Dat2ArchiveRef(archive);
        if (!ref->init() || !ref->openRead()) {
            return NULL;
        }
        Dat2Dir *vd = new Dat2Dir(ref, archive->fullname(), true);
        vd->load();
        return vd;
    }
}
