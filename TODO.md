This is a brief todo list/roadmap

Release v1.0:

- [ ] Error checking and exception raising (swears, polarbear, shirokuma)  
(this is a big one)
- [ ] Coloring - ncurses supports 256 colors for 256x256 color pairs
  - [ ] Invalid cell highlighting
  - [ ] Highlight the current "editing" cell
- [ ] Prospective cell marking
  - [ ] Redo layout to support 9 markers
  - [ ] Mark cells in the same row, column, or box with the same markers. Possibly a different color for each number? 
- [ ] Intro screen, skippable with command line flag [#1](https://github.com/lfowles/shirokuma/issues/1)
- [ ] Win screen, which will restart or quit the game
- [ ] Load sudoku files - [file formats](http://www.sudocue.net/fileformats.php)
  - [ ] Basic machinery
  - [ ] .sdk format - as described by Sudocue, not Sadman
    - [ ] Where to display extra information?
  - [ ] .ss format (both versions)
- [ ] Better navigation/entry controls
  - [ ] Find better alternative to using 1-9/a-i
  - [ ] Distinguish edit/navigation modes if keeping the 1-9/a-i scheme
- [ ] Helpers
  - [ ] Timer
- [ ] Local leaderboards
  
Future:
- [ ] Support .ss file format
- [ ] Networking
  - [ ] Daily games
  - [ ] Leaderboards
- [ ] Expand to other similar fill-in games?
  - [ ] Do this as separate apps, see what 
- [ ] Generate puzzles
- [ ] Load puzzles from some online sudoku API if it exists
