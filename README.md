# FileLister
A program similar to the tree command in MSDOS, only mine shows all files, not just the folders. Done using dirent.h, version adapted for Windows

The dirent.h and dirent.c have been adapted to work on Visual C community
To run it use ctrl+F5 from Visual C or run the .exe file from Windows cmd by going to the folder and use:

file_browser_dirent.exe or
file_browser_dirent.exe > runlog.doc 
Be careful in the second case not to use run.log or runlog.txt because with notepad and even npp++ you will have a crashed output because of the MSDOS characters I use to draw the tree.

It has a limitation: it considers files without '.' char in them folders, which is not always true, since there are simple files without extension and make sure not to hide the file extension.


move up
