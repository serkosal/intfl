# intfs
Interactive file listing.


# Dependencies
ncurses**W** - for unicode support.
ncurses      - for colors and mouse support on many of the UNIX systems. 

- for usage libncurses6 
- for unicode symbols usage support libncursesw6 
- for compiling libncurses-dev 
- for man-pages ncurses-doc

# Planed feautures

- 1. limit displayed files, to avoid visual cluttering.
- 2. expand/collaps directories by just clicking on them.
- 3. utility remembers settings for each launched directory.
- 4. updates whenever files changed using inotify.
- 5. fuzzy search.
- 6. maximum integration with external utilities & programs such as tmux, vim, helix editor.

# TODO

 - [x] basic file listing
 - [x] limit quantity of shown files and depth of directories 
 - [x] colorization
 - [x] basic keyboard support
 - [x] basic commands support

 - [x] unicode support (GCC version above 12.3, I've problems on 12.2.0)
 - [x] better input handling
 - [ ] support command line arguments [IN DEVELOPMENT]
 - [ ] add color support of executables files & different file extensions
 - [ ] usage of colors from LS_COLORS
 - [ ] ignore to parse/show/auto update specified files/patterns/directories' content
 - [ ] mouse support [IN DEVELOPMENT]

 - [ ] better commands, ability to launch shell commands
 - [ ] expand/collapse, recursive expand/collapse [IN DEVELOPMENT]
 - [ ] config files
 - [ ] command line
 - [ ] fuzzy search 
 - [ ] caching parsed directories based on last modification date
 - [ ] memozition of directories layouts
 - [ ] watch for files updates
 - [ ] doxygen documentation
 - [ ] full tests code coverage

 - [ ] get rid of recursion
 - [ ] symblinks supports 
 - [ ] support for c++ modules
 - [ ] panels, preview for file content

 - [ ] visualize not only filesystems, but any type of tree-like structures;
       e.g. html, json, yaml, xml, toml 