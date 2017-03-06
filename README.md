# My_tar :

## Description :

I did this project in less than two days. The goal of this project was to discover how the archiver and compresser tar works.

To do so we concatenate all the files and repository in one archive file separate by official tar headers. Then we compresse this archive with the zlib.

## How to use :

   To archive : ./my_tar cf [archive_name.tar] [file1 file2 ...]

   To unarchive : ./my_tar xf [archive_name.tar]

   To list files : ./my_tar tf [archive_name.tar]

To compress or decompress you have to use z flag.
I did also the verbose option (v), that list archive/unarchive files.
