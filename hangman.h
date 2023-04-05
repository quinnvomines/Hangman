#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h
        
    Class definition for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman        

    author: 

    last modified: 9/24/2017
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cctype>
#include <list>
#include <set>

using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
    hangman();

    // start a new game where player gets num_guesses unsuccessful tries
	void start_new_game(int num_guesses, int length, bool see_total_remain);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    string get_display_word();

    //If guess is right, updates word
    void set_display_word(char replace, vector<int> positions);
    //Blank word
    void set_initial_display_word(string word);

    // How many guesses remain?
	int get_guesses_remaining();

	//Guesses remaining
	void set_guesses_remaining(int new_guess);

    // What characters have already been guessed (for display)?
    string get_guessed_chars();

    //Adds guessed characters
    void set_guessed_chars(char add);

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();

    // Return the true hidden word.
    string get_hidden_word();

    //Get list of words
    list<string> get_words();

    //Set list of  words
    void set_words(list<string> words);

private:
    list<string> words;
    int num_guesses;
    int length;
    bool see_total_remain;
    string display_word;
    string chars_guessed;

};

#endif
