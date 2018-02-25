#include "Dat2File.h"
#include "Dat2Dir.h"
#include <cstdio>
#include <iostream>

VFS_NAMESPACE_START

    int read32(File *file)
    {
        char buffer[4];
        file->read(&buffer, 4);

        return int((unsigned char)(buffer[3]) << 24 |
                   (unsigned char)(buffer[2]) << 16 |
                   (unsigned char)(buffer[1]) << 8 |
                   (unsigned char)(buffer[0]));
    }

    char read8(File *file)
    {
        char buffer;
        file->read(&buffer, 1);

        return buffer;
    }


    Dat2Dir::Dat2Dir(Dat2ArchiveRef *handle, const char *fullpath, bool canLoad)
        : Dir(fullpath, NULL)
, _archiveHandle(handle)
, _canLoad(canLoad)
, _couldLoad(canLoad)
{
}

Dat2Dir::~Dat2Dir()
{
    close();
}

void Dat2Dir::close()
{
    _archiveHandle->close();
    _canLoad = _couldLoad; // allow loading again after re-opening (in case archive was replaced)
}

DirBase *Dat2Dir::createNew(const char *fullpath) const
{
    const Dat2ArchiveRef *czref = _archiveHandle;
    Dat2ArchiveRef *zref = const_cast<Dat2ArchiveRef*>(czref);
    return new Dat2Dir(zref, fullpath, false);
}

void Dat2Dir::load()
{
    if (!_canLoad)
        return;

    const Dat2ArchiveRef *czref = _archiveHandle;
    Dat2ArchiveRef *zref = const_cast<Dat2ArchiveRef*>(czref);

    _archiveHandle->openRead();

    File *file = _archiveHandle->archiveFile.content();

    file->seek(-8, SEEK_END);

    int filesTreeSize = read32(file);

    file->seek( - filesTreeSize - 8, SEEK_END);

    int filesCount = read32(file);

    for (unsigned int i = 0; i != filesCount; ++i) {

        int filenameSize = read32(file);

        std::string filename;
        filename.resize(filenameSize);
        file->read(&filename[0], filenameSize);
        std::replace(filename.begin(), filename.end(), '\\', '/');
        // todo: to lower

        char isCompressed = read8(file);
        unsigned int unpackedSize = read32(file);
        unsigned int packedSize = read32(file);
        unsigned int dataOffset = read32(file);

        std::string dir = filename;
        StripLastPath(dir);

        if (!getDir(dir.c_str())) {
            _createAndInsertSubtree(dir.c_str());
        }

        Dat2File *vf = new Dat2File(filename.c_str(), _archiveHandle);
        vf->setIsCompressed(isCompressed);
        vf->setPackedSize(packedSize);
        vf->setUnpackedSize(unpackedSize);
        vf->setDataOffset(dataOffset);
        _addRecursiveSkip(vf, fullnameLen() + 1);
    }
    _canLoad = false;
}

VFS_NAMESPACE_END
