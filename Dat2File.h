#ifndef VFS_DAT2_FILE_H
#define VFS_DAT2_FILE_H

#include <ttvfs.h>

#include "Dat2ArchiveRef.h"

VFS_NAMESPACE_START

class Dat2File : public File
{
public:
    Dat2File(const char *name, Dat2ArchiveRef *zref);
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

    void setIsCompressed(bool value);
    bool getIsCompressed();

    void setDataOffset(unsigned int value);
    unsigned int getDataOffset();

    void setPackedSize(unsigned int value);
    unsigned int getPackedSize();

    void setUnpackedSize(unsigned int value);
    unsigned int getUnpackedSize();

protected:
    unsigned char *_uncompressedData;
    vfspos _pos;
    CountedPtr<Dat2ArchiveRef> _archiveHandle;

    bool _isCompressed;
    unsigned int _dataOffset;
    unsigned int _packedSize;
    unsigned int _unpackedSize;

};

VFS_NAMESPACE_END

#endif
