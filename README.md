# intfs
Interactive file listing.

![Animation](https://github.com/serkosal/intfl/blob/main/demo.gif?raw=true)



# Dependencies
ncurses**W** - for unicode support.
ncurses      - for colors and mouse support on many of the UNIX systems. 

## development dependencies
doxygen for generating documentation
doxygen-awesome-css for night theme support,
download it using:
git submodule update --init --recursive

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
 - [x] expand/collapse
 - [x] mouse support
 - [x] doxygen documentation

## misc
 - [ ] more flags, commands support
 - [ ] whales spotting 
 - [ ] recursive expand/collapse
 - [ ] symblinks supports
 - [ ] panels, preview for file content
 - [ ] config files
 - [ ] memozition of directories layouts
 - [ ] watch for files updates
 - [ ] output as html, json, yaml, xml, toml 
 - [ ] visualize not only filesystems, but any type of tree-like structures;
       e.g. html, json, yaml, xml, toml 


## Search, patterns, ingores, .gitignore
 - [ ] wildcards, regex support
 - [ ] ignore to parse/print/watch-update specified files/patterns/types
 - [ ] support command line arguments
 - [ ] better commands, ability to launch shell commands
 - [ ] search, fuzzy search, regex search

## Colors
 - [ ] add color support of executables files & different file extensions
 - [ ] usage of colors from LS_COLORS
 - [ ] support of more colors



## development, refactoring, optimisations
 - [ ] full tests code coverage
 - [ ] get rid of recursion
 - [ ] caching parsed directories based on last modification date
 - [ ] support for c++ modules



