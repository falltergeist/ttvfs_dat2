#ifndef VFS_DAT2_DIR_H
#define VFS_DAT2_DIR_H

#include <ttvfs/VFSDir.h>
#include <ttvfs/VFSRefcounted.h>

namespace ttvfs
{
    class Dat2ArchiveRef;

    class Dat2Dir : public Dir
    {
        public:
            Dat2Dir(Dat2ArchiveRef *handle, const char *subpath, bool canLoad);

            virtual ~Dat2Dir();

            virtual void load();

            virtual const char *getType() const { return "Dat2Dir"; }

            virtual void close();

            virtual DirBase *createNew(const char *dir) const;

        protected:
            CountedPtr<Dat2ArchiveRef> _archiveHandle;
            bool _canLoad;
            const bool _couldLoad;
    };
}
#endif
