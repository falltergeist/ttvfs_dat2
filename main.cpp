#include "ttvfs/ttvfs.h"
#include "VFSDat2ArchiveLoader.h"
#include <cstdio>

#include <iostream>

int main(int argc, char *argv[])
{
    ttvfs::Root vfs;
    vfs.AddLoader(new ttvfs::DiskLoader);
    vfs.AddArchiveLoader(new ttvfs::VFSDat2ArchiveLoader);
    ttvfs::Dir *x = vfs.AddArchive("master.dat");
    //std::cout << x << std::endl;
    //vfs.Mount("master.dat", "");

    ttvfs::File *vf = vfs.GetFile("text/english/credits.txt");
    if(!vf)
    {
        printf("ERROR: text/english/credits.txt doesn't exist\n");
        return 1;
    }
    if(!vf->open("r"))
    {
        printf("ERROR: Failed to open text/english/credits.txt for reading\n");
        return 2;
    }

    char buf[513];
    size_t bytes = vf->read(buf, 512);
    buf[bytes] = 0;

    puts(buf);

    vf->close();

    return 0;
}