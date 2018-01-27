#ifndef VFS_DAT2_ARCHIVE_REF
#define VFS_DAT2_ARCHIVE_REF

#include <ttvfs/VFSFile.h>
#include <vector>

VFS_NAMESPACE_START

class Dat2ArchiveRef : public Refcounted
{
public:
    Dat2ArchiveRef(File *archive);
    ~Dat2ArchiveRef();
    bool openRead();
    void close();
    bool init();
    const char *fullname() const;

    std::vector<int> fileSizes;
    std::vector<int> dataSizes;
    std::vector<int> compressed;
    std::vector<int> dataOffsets;

//protected:
    CountedPtr<File> archiveFile;
};


VFS_NAMESPACE_END

#endif
