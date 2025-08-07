# intfs
Interactive file listing.

# Planed feautures

- 1. limit displayed files, to avoid visual cluttering.
- 2. expand/collaps directories by just clicking on them.
- 3. utility remembers settings for each launched directory.
- 4. updates whenever files changed using inotify.
- 5. fuzzy search.
- 6. maximum integration with external utilities & programs such as tmux, vim, helix editor.

# TODO

 - [x] basic file listing
 - [x] limit shown quantity of files and depth of directories 
 - [i] colorization
 - [ ] get rid of recursion
 - [ ] usage of colors from LS_COLORS     
 - [ ] command line arguments
 - [ ] ignore to parse/show/auto update specified files/patterns/directories' content
 - [ ] config files
 - [ ] expand/collapse, recursive expand/collapse
 - [ ] mouse & keyboard support
 - [ ] command line
 - [ ] fuzzy search 
 - [ ] caching parsed directories based on date of modification
 - [ ] memozition of directories layouts
 - [ ] watch for files updates
 - [ ] doxygen documentation
 - [ ] full tests code coverage

 - [ ] symblinks supports 
 - [ ] support for c++ modules
 - [ ] panels, preview for file content

 - [ ] visualize not only filesystems, but any type of tree-like structures;
       e.g. html, json, yaml, xml, toml 