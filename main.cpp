#include <ttvfs/ttvfs.h>
#include "VFSDat2ArchiveLoader.h"
#include <cstdio>

#include <iostream>

int main(int argc, char *argv[])
{
    ttvfs::Root vfs;
    vfs.AddLoader(new ttvfs::DiskLoader);
    //vfs.AddArchiveLoader(new ttvfs::VFSZipArchiveLoader);
    //vfs.AddArchive("master.zip");
    //std::cout << x << std::endl;

    vfs.AddArchiveLoader(new ttvfs::VFSDat2ArchiveLoader);
    vfs.AddArchive("master.dat");
    vfs.Mount("master.dat", "");

    std::string filename = "text\\english\\cuts\\artimer1.txt";

    ttvfs::File *vf = vfs.GetFile(filename.c_str());
    if (!vf) {

        printf("ERROR: can't find\n");
        return 1;
    }

    if(!vf->open("r")) {
        printf("ERROR: can't open\n");
        return 2;
    }

    std::cout << vf->size() << std::endl;

    char buf[vf->size()];
    size_t bytes = vf->read(buf, vf->size());
    buf[bytes] = 0;

    puts(buf);

    vf->close();

    return 0;
}
