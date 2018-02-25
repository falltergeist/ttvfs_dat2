#include "Dat2File.h"
#include <stdio.h>
#include "miniz.h"
#include <iostream>

VFS_NAMESPACE_START

Dat2File::Dat2File(const char *name, Dat2ArchiveRef *zref)
    : File(joinPath(zref->fullname(), name).c_str()),
      _pos(0),
      _archiveHandle(zref),
      _uncompressedData(0),
      _isCompressed(false)
{
}

Dat2File::~Dat2File()
{
    close();
    delete [] _uncompressedData;
}

bool Dat2File::open(const char *mode /* = NULL */)
{
    if (getIsCompressed()) {
        File *file = _archiveHandle->archiveFile.content();

        unsigned char compressedData[getPackedSize()];
        file->seek(getDataOffset(), SEEK_SET);
        file->read(compressedData, getPackedSize());

        _uncompressedData = new unsigned char[getUnpackedSize()]{0};

        // unpacking
        mz_stream zStream;
        zStream.total_in  = zStream.avail_in  = getPackedSize();
        zStream.avail_in = getPackedSize();
        zStream.next_in  = compressedData;
        zStream.total_out = zStream.avail_out = getUnpackedSize();
        zStream.next_out = _uncompressedData;
        zStream.zalloc = 0;
        zStream.zfree = 0;
        zStream.opaque = 0;
        mz_inflateInit(&zStream );
        mz_inflate(&zStream, MZ_FINISH);
        mz_inflateEnd(&zStream );
    }

    return true; // does not have to be opened
}

bool Dat2File::isopen() const
{
    return true; // is always open
}

bool Dat2File::iseof() const
{
    return _pos >= _unpackedSize;
}

void Dat2File::close()
{
}

bool Dat2File::seek(vfspos pos, int whence)
{
    const vfspos end = 0xFFFFFFFF;
    switch(whence)
    {
        case SEEK_SET:
            if(pos >= end) // zip files have uint32 range only
                return false;
            _pos = pos;
            break;

        case SEEK_CUR:
            if(_pos + pos >= end)
                return false;
            _pos += pos;
            break;

        case SEEK_END:
            if(pos >= size())
                return false;
            _pos = size() - pos;
            break;

        default:
            return false;
    }

    return true;
}

bool Dat2File::flush()
{
    // FIXME: use this to actually write to zip file?
    return false;
}

vfspos Dat2File::getpos() const
{
    return _pos;
}

size_t Dat2File::read(void *dst, size_t bytes)
{
    size_t bytesToRead = bytes;
    if (bytes + _pos > size()) {
        bytesToRead = size() - _pos;
    }

    if (_isCompressed) {
        unsigned char *startptr = _uncompressedData + _pos;
        unsigned char *endptr = _uncompressedData + size();
        bytes = std::min<size_t>(endptr - startptr, bytes); // limit in case reading over buffer size
        memcpy(dst, startptr, bytes); //  binary copy
    } else {
        File *file = _archiveHandle->archiveFile.content();
        file->seek(_dataOffset + _pos, SEEK_SET);
        file->read(dst, bytesToRead);
    }
    _pos += bytesToRead;
    return bytesToRead;
}

size_t Dat2File::write(const void *src, size_t bytes)
{
    return 0;
}

vfspos Dat2File::size()
{
    if (!_archiveHandle->openRead()) {
        return npos;
    }

    return _unpackedSize;
}

void Dat2File::setIsCompressed(bool value)
{
    _isCompressed = value;
}

bool Dat2File::getIsCompressed()
{
     return _isCompressed;
}

void Dat2File::setDataOffset(unsigned int value)
{
    _dataOffset = value;
}

unsigned int Dat2File::getDataOffset()
{
    return _dataOffset;
}

void Dat2File::setPackedSize(unsigned int value)
{
    _packedSize = value;
}

unsigned int Dat2File::getPackedSize()
{
    return _packedSize;
}

void Dat2File::setUnpackedSize(unsigned int value)
{
    _unpackedSize = value;
}

unsigned int Dat2File::getUnpackedSize()
{
    return _unpackedSize;
}

VFS_NAMESPACE_END
