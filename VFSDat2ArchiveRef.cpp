#include <ttvfs/VFSInternal.h>
#include "VFSDat2ArchiveRef.h"
#include <stdio.h>
//#include "miniz.h"

#include <iostream>

VFS_NAMESPACE_START

Dat2ArchiveRef::Dat2ArchiveRef(File *file) : archiveFile(file)
{
    //mz = new mz_zip_archive;
    //memset(mz, 0, sizeof(mz_zip_archive));
}

//#define MZ ((mz_zip_archive*)mz)

Dat2ArchiveRef::~Dat2ArchiveRef()
{
    close();
    //delete MZ;
}

bool Dat2ArchiveRef::init()
{
    // Simple check of archive integrity. last 4 bytes should be equal to the size of file

    File *file = archiveFile.content();
    file->seek(file->size() - 4, SEEK_SET);
    char buffer[4];
    file->read(&buffer, 4);

    int a = int((unsigned char)(buffer[3]) << 24 |
                (unsigned char)(buffer[2]) << 16 |
                (unsigned char)(buffer[1]) << 8 |
                (unsigned char)(buffer[0]));

    std::cout << a << std::endl;

    //return zip_reader_init_vfsfile(MZ, archiveFile, 0);
    return true;
}

bool Dat2ArchiveRef::openRead()
{
    //return zip_reader_reopen_vfsfile(MZ, 0);
    return true;
}

void Dat2ArchiveRef::close()
{
    /**
    switch(MZ->m_zip_mode)
    {
        case MZ_ZIP_MODE_READING:
            mz_zip_reader_end(MZ);
            break;

        case MZ_ZIP_MODE_WRITING:
            mz_zip_writer_finalize_archive(MZ);
            mz_zip_writer_end(MZ);
            break;

        case MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED:
            mz_zip_writer_end(MZ);
            break;

        case MZ_ZIP_MODE_INVALID:
            break; // nothing to do
    }
    */

    archiveFile->close();
}

const char *Dat2ArchiveRef::fullname() const
{
    return archiveFile->fullname();
}

VFS_NAMESPACE_END