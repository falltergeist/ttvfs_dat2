#ifndef VFS_DAT2_FILE_H
#define VFS_DAT2_FILE_H

#include <ttvfs/VFSFile.h>
#include "VFSDat2ArchiveRef.h"

VFS_NAMESPACE_START

class Dat2File : public File
{
public:
    Dat2File(const char *name, Dat2ArchiveRef *zref, unsigned int fileIdx);
    virtual ~Dat2File();
    virtual bool open(const char *mode = NULL);
    virtual bool isopen() const;
    virtual bool iseof() const;
    virtual void close();
    virtual bool seek(vfspos pos, int whence);
    virtual bool flush();
    virtual vfspos getpos() const;
    virtual size_t read(void *dst, size_t bytes);
    virtual size_t write(const void *src, size_t bytes);
    virtual vfspos size();
    virtual const char *getType() const { return "ZipFile"; }

protected:
    bool unpack();

    char *_buf;
    vfspos _pos;
    CountedPtr<Dat2ArchiveRef> _archiveHandle;
    vfspos _bufSize;
    unsigned int _fileIdx;
    std::string _mode;
};

VFS_NAMESPACE_END

#endif