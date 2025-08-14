#include "Commands.hpp"

#include "Colors.hpp"

void command_help(const Window& win)
{
    win.clear();

    win.print(L"usage:\n\n");

    win.print(L"------ Files listing section ------\n", NcursesColors::FS_Directory);

    win.print(L"-a\t\t\t", NcursesColors::FS_Directory);
    win.print(L"list ");
    win.print(L"almost all ", NcursesColors::FS_Directory);
    win.print(L"files, excluding '.' and '..'.\n");

    win.print(L"-A\t\t\t", NcursesColors::FS_Directory);
    win.print(L"list ");
    win.print(L"all ", NcursesColors::FS_Directory);
    win.print(L"files, including '.' and '..'.\n");

    win.print(L"-d\t\t\t", NcursesColors::FS_Directory);
    win.print(L"list directories only.\n");

    // mainWin.print(L"-l follow symbolic links.                                \n");
    win.print(L"-f\t\t\t", NcursesColors::FS_Directory);
    win.print(L"print full path for each file entry.\n");

    // mainWin.print(L"-x stay on current filesystem only                       \n");
    win.print(L"-L depth\t\t", NcursesColors::FS_Directory);
    win.print(L"max descendant depth.\n");

    // mainWin.print(L"-R                                                       \n");
    win.print(L"-P pattern\t\t", NcursesColors::FS_Directory);
    win.print(L"list only items that satisfy Pattern.\n");

    win.print(L"-I pattern\t\t", NcursesColors::FS_Directory);
    win.print(L"ignore.\n");

    win.print(L"--gitignore\t\t", NcursesColors::FS_Directory);
    win.print(L"ignores files specified in .gitignore file.\n");

    win.print(L"--ignorefile file\t", NcursesColors::FS_Directory);
    win.print(L"ignores files specified in [file].\n");

    // mainWin.print(L"--matchdirs  \t \n                ");
    // mainWin.print(L"--metafirst \t \n                ");
    win.print(L"--prune \t\t\t", NcursesColors::FS_Directory);
    win.print(L"hide empty directories.\n");

    // mainWin.print(L"--info \t\t\tPrune empty files\n");
    // mainWin.print(L"--infofile\t\tPrune empty files   \n");
    // mainWin.print(L"--noreport \t                                            \n");
    // mainWin.print(L"--charset \t                                             \n");
    win.print(L"--filelimit\t\t\n");
    win.print(L"-o\t\t\t\n");
    win.print(L"------ Files options ------\n", NcursesColors::FS_Directory);
    win.print(L"-q print unprintable characters as '?'  \t \n");
    win.print(L"-N print unprintable characters as is   \t \n");
    win.print(L"-Q quote filenames with double quotes   \t \n");
    // mainWin.print( L"-p print the protections for each file  \t \n");
    // mainWin.print( L"-u Displays file owner or UID number  \t \n");
    // mainWin.print( L"-g Displays file group owner or GID number.  \t \n");
    win.print(L"-s Print the size in bytes of each file.  \t \n");
    win.print(L"-h Print the size in a more human readable way.  \t \n");
    // mainWin.print(L"--si Like -h, but use in SI units (powers of 1000).  \t \n");
    // mainWin.print(L"--du Compute size of directories by their contents.  \t \n");
    win.print(L"--D print the date since last modification.  \t \n");
    // mainWin.print( L"--timefmt <f> Print and format time according to the format <f> \n");
    // mainWin.print( L"-F            Appends '/', '=', '*', '@', '|' or '>' as per ls -F. \n");
    // mainWin.print( L"--inodes      Print inode number of each file. \n");
    // mainWin.print( L"--device      Print device ID number to which each file belongs. \n");

    win.refresh();
}


void redraw(const Window& win, const std::vector<FilePrintRepr>& reprs)
{
    win.clear();
    for (const auto& repr : reprs)
        printFileRepr(repr, win);
    win.refresh();
}