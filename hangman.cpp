/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author:

    last modified: 3/7/2019
*/

#include "hangman.h"

using namespace std;

// constructor
hangman::hangman() {
    ifstream fin("dictionary.txt");
    if(fin.fail()){
        cerr << "Error opening file" << endl;
    }
    string w;
    while(fin >> w){
        words.push_back(w);
    }
    fin.close();
}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses, int length, bool see_total_remain) {
    this->num_guesses = num_guesses;
    this->length = length;
    this->see_total_remain = see_total_remain;
    chars_guessed = "";
}

//Sets word list
void hangman::set_words(list<string> words) {
    this->words = words;
}

//Returns word list
list<string> hangman::get_words() {
    return words;
}

// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {
    list<string>::iterator iter;
    for(iter = words.begin(); iter != words.end(); iter++){
        for(int i = 0; i < (*iter).length(); i++){
            if(tolower((*iter).at(i)) == c){
                return true;
            }
        }
    }
    return false;
}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return display_word;
}

//Set blank word
void hangman::set_initial_display_word(string word) {
    display_word = word;
}

//If guess is right, display new word
void hangman::set_display_word(char replace, vector<int> positions) {
    for(int i = 0; i < positions.size(); i++){
        display_word.at(positions.at(i)) = replace;
    }
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return num_guesses;
}

void hangman::set_guesses_remaining(int new_guess) {
    num_guesses = new_guess;
}

// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    return chars_guessed;
}

void hangman::set_guessed_chars(char add){
    set<char> sorted;
    for(int i = 0; i < chars_guessed.length(); i++){
        sorted.insert(chars_guessed.at(i));
    }
    sorted.insert(add);
    string r = "";
    set<char>::iterator iter;
    for(iter = sorted.begin(); iter != sorted.end(); iter++){
        r += *iter;
    }
    chars_guessed = r;
}

// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    for(int i = 0; i < chars_guessed.length(); i++){
        if(chars_guessed.at(i) == c){
            return true;
        }
    }
    return false;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    if(display_word.find("-") == string::npos){
        return true;
    }
    return false;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    if(num_guesses == 0) {
        return true;
    }
    return false;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    return words.front();
}


