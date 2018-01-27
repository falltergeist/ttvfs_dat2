#include "VFSDat2File.h"
#include "VFSDat2Dir.h"
#include <ttvfs/VFSTools.h>
#include <ttvfs/VFSInternal.h>
#include <ttvfs/VFSFile.h>

#include <iostream>

VFS_NAMESPACE_START

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

    _archiveHandle->openRead();

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

    _canLoad = false;
    */
}



VFS_NAMESPACE_END