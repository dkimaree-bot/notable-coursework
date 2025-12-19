## BASH HANGMAN GAME
#### ASOUE Hangman Game

**Grade: 8/10**

#### Description
A Bash shell script implementation of the Hangman word-guessing game, themed around "A Series of Unfortunate Events" (ASOUE). The game features colorful ASCII art, robust input validation, and an interactive command-line interface with customizable word length selection.

#### Features
- **Custom word list**: 100+ words from the ASOUE universe
- **Word length selection**: Choose your desired word length (minimum 3 letters)
- **Color-coded interface**: Uses ANSI escape codes for visual feedback (green for correct, red for wrong, yellow for revealed letters)
- **Progressive hangman drawing**: ASCII art that builds with each wrong guess
- **Comprehensive input validation**: Handles empty input, spaces, multiple characters, non-alphabetic characters, and duplicate guesses
- **Smart alphabet tracker**: Displays which letters have been guessed with color differentiation
- **Six wrong guesses allowed** before game over
- **User-friendly feedback**: Specific messages for each type of input error

#### Technologies Used
- **Language**: Bash shell scripting
- **Unix utilities**: `tr`, `sed`, `awk`, `shuf`, `grep`
- **Concepts**: 
  - Shell parameter expansion and substitution
  - Arrays and string manipulation
  - ANSI color codes
  - File I/O and validation
  - Input sanitization (untainting)
  - Functions with arguments

#### What I Learned
- Advanced Bash scripting techniques including parameter substitution (`${string//[^$guess]/_}`)
- Working with ANSI escape codes for terminal color output
- Building interactive CLI applications with proper input validation
- Using Unix text processing utilities (`awk`, `sed`, `tr`, `shuf`) in shell scripts
- File validation and error handling in Bash
- Creating engaging user experiences in terminal-based applications
- Best practices for shell scripting (camel case, proper indentation, C-style blocks)

#### Files
- `asoue.sh` - Main game script
- `asoue.txt` - Word list file containing ASOUE-themed words

#### How to Run
```bash
chmod +x asoue.sh
./asoue.sh
```

#### Game Rules
1. Select a word length at the start
2. Guess one letter at a time
3. You have 6 wrong guesses before you lose
4. Invalid inputs (spaces, numbers, duplicates, empty) count as wrong guesses
5. Win by revealing all letters before running out of guesses
