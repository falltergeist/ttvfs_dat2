#include <iostream>
#include <ttvfs/VFSFile.h>
#include "Dat2ArchiveRef.h"

namespace ttvfs
{
    int rread32(File *file)
    {
        char buffer[4];
        file->read(&buffer, 4);

        return int((unsigned char) (buffer[3]) << 24 |
                   (unsigned char) (buffer[2]) << 16 |
                   (unsigned char) (buffer[1]) << 8 |
                   (unsigned char) (buffer[0]));
    }

    int rread16(File *file)
    {
        char buffer[2];
        file->read(&buffer, 2);

        return int((unsigned char) (buffer[1]) << 8 |
                   (unsigned char) (buffer[0]));
    }

    int rread8(File *file)
    {
        char buffer;
        file->read(&buffer, 1);

        return buffer;
    }

    Dat2ArchiveRef::Dat2ArchiveRef(File *file) : archiveFile(file)
    {
    }

    Dat2ArchiveRef::~Dat2ArchiveRef()
    {
        close();
    }

    bool Dat2ArchiveRef::init()
    {
        File *file = archiveFile.content();
        file->seek(file->size() - 4, SEEK_SET);

        // Simple check of archive integrity. last 4 bytes should be equal to the size of file
        int totalSize = rread32(file);
        if (totalSize != file->size()) {
            return false;
        }
        return true;
    }

    bool Dat2ArchiveRef::openRead()
    {
        return true;
    }

    void Dat2ArchiveRef::close()
    {
        archiveFile->close();
    }

    const char *Dat2ArchiveRef::fullname() const
    {
        return archiveFile->fullname();
    }
}
