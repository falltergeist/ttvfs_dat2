#ifndef VFS_DAT2_ARCHIVE_REF
#define VFS_DAT2_ARCHIVE_REF

#include <ttvfs/VFSRefcounted.h>
#include <vector>

namespace ttvfs
{
    class File;

    class Dat2ArchiveRef : public Refcounted
    {
        public:
            explicit  Dat2ArchiveRef(File *archive);
            ~Dat2ArchiveRef();

            bool openRead();
            void close();
            bool init();
            const char *fullname() const;

            CountedPtr<File> archiveFile;
    };
}
#endif
