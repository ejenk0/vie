# vie

A lightweight, pure C, ncurses based command line text editor.

Features in development intend to target the development usecase

## Purpose

1. To practice and improve my ability to develop in a text-based environment by restricting myself to using only vim, git, make, gdb, [lynx](https://lynx.invisible-island.net/) etc. Also to get more comfortable using Linux, specifically Arch Linux, for development.
2. To better understand what goes into parsing code. I intend to learn about parsing and syntax trees to develop code highlighting, linting etc.
3. To learn how to develop complex, console based applications
4. To have an alternative editor choice to vim that satisfies my needs out of the box without having to spend serious time configuring and personalising vim/neovim.
5. To improve my confidence and familiarity with C.

## Success Requirments

- [x] Load and view a file: `vie myfile`
- [x] Navigable cursor
- [ ] `vim` style basic navigation binds
    - [ ] 'g' home, ';' end, 'u' pgup, 'n' pgdwn
    - [ ] 'w', 'e', '$' (or equivalent)
- [ ] `vim` style basic edit binds: `x`,`r`, ...
- [ ] `vim` style insert mode
- [ ] Line numbers
- [ ] Project files explorer/selector
- [ ] Syntax highlighting for basic languages/config schemas
- [ ] Smart "execute" bind for select languages

[View the devlog](https://github.com/ejenk0/vie/blob/master/DEVLOG.md)
