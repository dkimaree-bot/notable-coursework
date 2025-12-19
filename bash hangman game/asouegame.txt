#!/bin/bash


#==============================================================================
 #  Assignment: BASH/KSH Lab - Hangman App
 #
 #    Author: KIMAREE DUNN
 #    Collaboration: None
 #   Language: Bash shell script
 #             Uses: tr, sed, awk, shuf, grep
 #
 #  To Compile: Made executable with chmod +x asoue.sh
 # 
 #    Class: OPS102
 #  Professor: Harvey Kaduri
 #   Due Date: December 1, 2025
 #  Submitted: November 29, 2025
 #
 #-----------------------------------------------------------------------------
 #
 # Description: Hangman word-guessing game themed around
 # "A Series of Unfortunate Events". The program selects a random word from a word list and asks
 #the user to guess it letter by letter with a max of 6 wrong guesses allowed.
 #
 #    Input: Desired word length  at the start of the game, then single letter guesses during gameplay
 #
 #    Output:  - Themed ASCII art banner
#   - Masked word with underscores for unguessed letters
#   - alphabet showing guessed/available letters with colors
#   - Wrong guess counter
#   - ASCII hangman drawing that builds with wrong guesses
#   - Specific feedback messages for each type of input
#   - Win/loss message showing the correct word
 #
 #  Algorithm:  1. Validate/load word list from asoue.txt file
#  			    2. Prompt user word length/sanitize input
#  			    3. Filter word list by length (use default if none matches)
# 			    4. Randomly select a word
#  			    5. Initialize masked word with underscores( that replaces letters)
#   6. Enter game loop:
#      a. Display current game state
#      b. Accept/validate letter input
#      c. Check if letter already guessed
#      d. Update mask
#      e. Compare old/new mask and determine correct/wrong guess
#      f. Increment wrong counter for incorrect guess
#      g. Display hangman ASCII art to wrong guesses
#      h. Check win condition (masked == word)
#      i. Check loss condition (wrong >= 6)
#   7. Display final win/loss message with revealed word
 #
 #  Required Features Not Included: n/a
 #
 #  Known Bugs: None identified.
 #
#==============================================================================



# ------------------ CONFIGURATION ------------------
usage() {
cat <<EOF
Usage: $0
Runs ASOUE-themed Hangman game.

You will be asked for a desired word length and then play the game
with up to six wrong guesses.
EOF
}

# ------------------ BANNER FUNCTION ------------------
fnBanner() {
echo -e "\033[38;5;25m
  _   __   _      ___    /                               \\
 /_) (_ \` / ) / / )_    ( ( _   _   _   _   _ _   _   _   )
/ / .__) (_/ (_/ (__     \\ ) ) (_( ) ) (_( ) ) ) (_( ) ) /
                                         _)
\033[0m"
}
#------------------------------------------------------

wordFile="asoue.txt"

# test() to check file if exists
if test ! -f "$wordFile"; then
    echo "Error: File $wordFile not found."
    exit 1
fi

# make sure file is not empty, get unique cleaned list
wordList=$(tr '[:upper:]' '[:lower:]' < "$wordFile" | sed '/^$/d')


if test -z "$wordList"; then
    echo "Error: Word list is empty or invalid."
    exit 1
fi

fnBanner

read -p "Enter the word length (minimum 3): " userChosenLen

# untaint and sanity check
desiredLen=$(echo "$userChosenLen" | tr -dc '0-9')

if test -z "$desiredLen"; then
    echo "Invalid input, using default length 6."
    desiredLen=6
fi

filteredList=$(echo "$wordList" | awk -v len="$desiredLen" 'length($0)==len')

# if user enters a value that doesnt match the length of a word from the list, use default length
if test -z "$filteredList"; then
    echo "No words of length $desiredLen found — using default length 6."
    desiredLen=6
    filteredList=$(echo "$wordList" | awk 'length($0)==6')
fi


# pick random word
word=$(echo "$filteredList" | shuf -n1)
wordLength=${#word}

# ANSI codes
clrGreen="\033[38;5;73m"      # teal green (for correct input)
clrYellow="\033[38;5;179m"    # yellow (revealed letters)
clrRed="\033[0;31m"           # red (for when input is wrong)
clrOrange="\033[38;5;130m"    # rust orange (title)
clrGray="\033[38;5;246m"      # gray (used letters)
clrBanner="\033[38;5;25m"     # blue (for the banner)
clrReset="\033[0m"


# masked word
masked=""
for ((i=0; i<${#word}; i++)); do
    c="${word:$i:1}"
    if [[ "$c" =~ [a-z] ]]; then
        masked+="_"
    else
        masked+="$c"   # allows punctuation to stay
    fi
done


wrong=0
guessArray=()   # guess array that displays when user makes a wrong guess

hangmanParts=(
    "     _______
    |/      | "
    "    |      (_)"
    "    |      \\|/"
    "    |       |"
    "    |      / \\\\"
    "    |
   _|___"
)



# MASK UPDATE

fnUpdateMask() {
    local word="$1"
    local guessed="$2"
    # returns the mask with only the guessed letters showing
    echo "${word//[^$guessed]/_}"
}


# DISPLAY FUNCTION

fnDisplay() {
    local displayWord=""
    local alphabet=""

    # color masking
    for ((i=0; i<wordLength; i++)); do
        char=${masked:$i:1}

        if [[ "$char" != "_" ]]; then
            displayWord+="${clrYellow}${char}${clrReset}"
        else
            displayWord+="_"
        fi
    done

    # build guessed alphabet showing
    for letter in {a..z}; do
        if printf "%s " "${guessArray[@]}" | grep -q "$letter"; then
            alphabet+="${clrGray}${letter}${clrReset}"
        else
            alphabet+="$letter"
        fi
    done

    echo -e "${clrOrange}A Series of Unfortunate Events (Hangman Game)!${clrReset}"
    echo -e "Word: $displayWord"
    echo -e "Alphabet: $alphabet"
    echo "Wrong guesses: $wrong/6"
}

clear
fnDisplay

# GAME LOOP

while true; do

    read -n1 -p "Enter a letter: " userInput
    echo

    # validate input
    # invalid input counting as wrong guess
	if [[ -z "$userInput" ]]; then
    	echo -e "${clrRed}Invalid! empty input.${clrReset}"
    	wrong=$(expr $wrong + 1)
    	sleep 1; clear; fnDisplay
    continue
	fi

	if [[ "$userInput" =~ [[:space:]] ]]; then
    	echo -e "${clrRed}Invalid! Spaces are not allowed.${clrReset}"
    	wrong=$(expr $wrong + 1)
    	sleep 1; clear; fnDisplay
    continue
	fi


	if [[ ${#userInput} -ne 1 ]]; then
    	echo -e "${clrRed}Invalid! Enter only ONE character.${clrReset}"
    	wrong=$(expr $wrong + 1)
    	sleep 1; clear; fnDisplay
    continue
	fi

	# non-alphabet counts as wrong
	if [[ ! "$userInput" =~ [a-zA-Z] ]]; then
    	echo -e "${clrRed}Invalid: letters only.${clrReset}"
    	wrong=$(expr $wrong + 1)
    	sleep 1; clear; fnDisplay
    	continue
	fi


    # normalize letters
    userInput=$(echo "$userInput" | tr '[:upper:]' '[:lower:]')

    # check if already guessed
    if printf "%s " "${guessArray[@]}" | grep -q "$userInput"; then
        echo -e "${clrOrange}Already guessed.${clrReset}"
        sleep 1
        clear
        fnDisplay
        continue
    fi

    # store guess
    guessArray+=("$userInput")

    # PARAMETER SUBSTITUTION
    # Build a mask with guessed chars
    newMask=$(fnUpdateMask "$word" "${guessArray[*]}")


    # compare old to  new to decide if correct
    if [[ "$newMask" != "$masked" ]]; then
        echo -e "${clrGreen}Correct!${clrReset}"

        # update masked word
        masked="$newMask"

        sleep 1
        clear
        fnDisplay
    else
        # WRONG GUESS
        # expr
        wrong=$(expr $wrong + 1)

        echo -e "${clrRed}Wrong!${clrReset}"
        for ((i=0; i<wrong; i++)); do
            echo -e "${clrRed}${hangmanParts[i]}${clrReset}"
        done

        sleep 1
        clear
        fnDisplay
    fi

    # WIN condition
    if [[ "$masked" == "$word" ]]; then
        fnDisplay
        echo -e "${clrGreen}You win! The word was: $word${clrReset}"
        break
    fi

    # LOSS condition
    if (( wrong >= 6 )); then
        echo -e "${clrRed}You lose ! The word was: $word${clrReset}"
        break
    fi

done

