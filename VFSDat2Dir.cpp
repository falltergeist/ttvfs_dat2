#include "VFSDat2File.h"
#include "VFSDat2Dir.h"
#include <ttvfs/VFSTools.h>
#include <ttvfs/VFSInternal.h>
#include <ttvfs/VFSFile.h>

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

    int read16(File *file)
    {
        char buffer[2];
        file->read(&buffer, 2);

        return int((unsigned char)(buffer[1]) << 8 |
                   (unsigned char)(buffer[0]));
    }

    int read8(File *file)
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

//#define MZ ((mz_zip_archive*)_archiveHandle->mz)

void Dat2Dir::load()
{
    if(!_canLoad)
        return;

    const Dat2ArchiveRef *czref = _archiveHandle;
    Dat2ArchiveRef *zref = const_cast<Dat2ArchiveRef*>(czref);

    _archiveHandle->openRead();

    File *file = _archiveHandle->archiveFile.content();

    file->seek(-8, SEEK_END);

    int filesTreeSize = read32(file);
    int totalSize = read32(file);

    file->seek( - filesTreeSize - 8, SEEK_END);

    int filesCount = read32(file);

    for (unsigned int i = 0; i != filesCount; ++i) {

        int filenameSize = read32(file);

        std::string filename;
        filename.resize(filenameSize);
        file->read(&filename[0], filenameSize);
        std::replace(filename.begin(), filename.end(), '\\', '/');
        //std::cout << filename << std::endl;
        // todo: to lower

        zref->compressed.push_back(read8(file));
        zref->fileSizes.push_back(read32(file));
        zref->dataSizes.push_back(read32(file));
        zref->dataOffsets.push_back(read32(file));

        std::string dir = filename;
        StripLastPath(dir);

        if (!getDir(dir.c_str())) {
            _createAndInsertSubtree(dir.c_str());
        }


        //std::cout << filename << " " << (!!compressed ? "YES" : "NO") << std::endl;
        //if (!!compressed) continue;

        //StripLastPath(filename);
        //_createAndInsertSubtree(filename.c_str());
        //continue;

        Dat2File *vf = new Dat2File(filename.c_str(), _archiveHandle, i);
        _addRecursiveSkip(vf, fullnameLen() + 1);
    }

    //const Dat2ArchiveRef *czref = _archiveHandle;
    //std::cout << _archiveHandle->archiveFile.content()->size() << std::endl;
    /*
    const unsigned int files = mz_zip_reader_get_num_files(MZ);
    const size_t len = fullnameLen() + 1; // +1 for trailing '/' when used as path name in addRecursive()

    mz_zip_archive_file_stat fs;
    for (unsigned int i = 0; i < files; ++i)
    {
        if(mz_zip_reader_is_file_encrypted(MZ, i))
            continue;
        if(!mz_zip_reader_file_stat(MZ, i, &fs))
            continue;
        if(mz_zip_reader_is_file_a_directory(MZ, i))
        {
            _createAndInsertSubtree(fs.m_filename);
            continue;
        }
        if(getFile(fs.m_filename))
            continue;

        ZipFile *vf = new ZipFile(fs.m_filename, _archiveHandle, fs.m_file_index);
        _addRecursiveSkip(vf, len);
    }
    */
    _canLoad = false;

}



VFS_NAMESPACE_END
