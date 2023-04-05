/*
    main.cpp
        
    Implements the user interface for hangman.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Quinn Vo

    last modified: 10/25/2020
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <map>

#include "hangman.h"

using namespace std;

// helper function prototypes
int get_integer(string prompt); // return a positive integer
char get_letter(string prompt); // return a valid lowercase letter
bool get_yesno(string prompt);  // return true == yes / false == no
string trim(string s);          // remove leading/trailing whitespace

//Function checks if length specified by user is in the dictionary
bool valid_length(int length, list<string> words){
    list<string>::iterator iter;
    for(iter = words.begin(); iter != words.end(); iter++){
        if((*iter).length() == length){
            return true;
        }
    }
    return false;
}

int main() {
    cout << "Welcome to Hangman!" << endl;
    cout << "===================" << endl << endl;

    // get the hangman object
    hangman game;

    list<string> master_list = game.get_words();

    // Keep playing the game until the user decides otherwise
    while (true) {
        //Get num guesses
        int num_guesses;
        do{
            num_guesses = get_integer("How many guesses would you like?");
            cout << endl;
        } while(num_guesses <= 0);

        //Get length of word
        int length;
        do{
            length = get_integer("How long of a word would you like? ");
        } while (!valid_length(length, master_list));


        // Prompt the user for whether they want to have a running total of the number of words remaining
        // in the word list
        bool see_total_remain = get_yesno("Show running total of words? (y/n) ");
        cout << endl;

        game.start_new_game(num_guesses, length, see_total_remain);

        //Blank word
        string w = "";
        for(int i = 0; i < length; i++){
            w += "-";
        }
        game.set_initial_display_word(w);

        list<string> all_words = master_list;

        //words with length specified by user
        list<string> possibleWords;
        list<string>::iterator iter;
        for(iter = all_words.begin(); iter != all_words.end(); iter++){
            if((*iter).length() == length){
                possibleWords.push_back(*iter);
            }
        }

        while (!game.is_won() && !game.is_lost()) {

            cout << "Your word is: " << game.get_display_word() << endl;

            //Print already guessed
            string already_guessed = game.get_guessed_chars();
            if (already_guessed.size() == 0) {
                cout << "You have not yet guessed any letters." << endl;
            } else {
                cout << "You have already guessed these letters: ";
                cout << already_guessed << endl;
            }

            cout << "You have " << game.get_guesses_remaining();
            cout << " guesses remaining." << endl << endl;

            //Take guess
            char guess = get_letter("What is your next guess?");
            while (game.was_char_guessed(guess)) {
                cout << endl << "You already guessed that!" << endl;
                guess = get_letter("What is your next guess?");
            }
            cout << endl;
            game.set_guessed_chars(guess);

            //Generate families
            map<string, list<string>> families;
            for(iter = possibleWords.begin(); iter != possibleWords.end(); iter++){
                string wcp = w;
                for(int i = 0; i < (*iter).length(); i++){
                    if(tolower((*iter).at(i)) == guess){
                        wcp.at(i) = guess;
                    }
                }
                families[wcp].push_back((*iter));
            }

            //Find largest family
            map<string, list<string>>::iterator miter;
            string large_fam = w;
            int size_large_fam = families[w].size();
            for(miter = families.begin(); miter != families.end(); miter++){
                if(miter->second.size() > size_large_fam){
                    size_large_fam = miter->second.size();
                    large_fam = miter->first;
                }
            }

            //Filter list
            possibleWords = families[large_fam];

            game.set_words(possibleWords);

            if(see_total_remain){
                cout << "Words in chosen family: " << possibleWords.size() << endl;
            }
            cout << endl;

            //Check guess
            bool good_guess = game.process_guess(guess);
            if (good_guess) {
                cout << "Good guess!" << endl;
                vector<int> positions;
                for(int i = 0; i < game.get_display_word().length(); i++){
                    if(large_fam.at(i) == guess){
                        positions.push_back(i);
                    }
                }
                game.set_display_word(guess, positions);
            } else {
                cout << "Sorry, that letter isn't in the word." << endl;
                game.set_guesses_remaining(game.get_guesses_remaining() - 1);
            }

            if (game.is_won()) {
                cout << "Congratulations! You won the game!" << endl;
                cout << "The word was: " << game.get_display_word();
                cout << endl;
            }

            if (game.is_lost()) {
                cout << "Oh no! You lost!!!" << endl;
                cout << "My secret word was: " << game.get_hidden_word() << endl;
            }
        }

        cout << endl;
        if (!get_yesno("Would you like to play again (y/n)?")) break;
    }

    cout << endl << "Thank you for playing Hangman." << endl;

    return 0;
}

// Prompt for a positive integer response, re-prompting if invalid
// input is given. This is not super-robust - it really should work
// harder to filter out responses like "123foo", but oh well.
int get_integer(string msg) {
    while (true) {
        string input;
        int result = 0;

        cout << msg << endl;
        getline(cin, input);

        result = atoi(input.c_str());
        if (result > 0) return result;

        cout << "I didn't understand that. Please enter a positive integer.";
        cout << endl;
    }
}

// Prompt for a letter of the alphabet, re-prompting if invalid
// input is given.
char get_letter(string msg) {
    while (true) {
        string input;

        cout << msg << endl;
        getline(cin, input);

        input = trim(input);

        if (input.size() == 1) {
            char result = tolower(input[0]);
            if (result >= 'a' && result <= 'z') return result;
        }

        cout << "I didn't understand that. ";
        cout << "Please enter a letter of the alphabet.";
        cout << endl;
    }
}


// Prompt for a yes/no response, re-prompting if invalid
// input is given.
bool get_yesno(string msg) {
    while (true) {
        string input;

        cout << msg << endl;
        getline(cin, input);

        input = trim(input);
        for (int i = 0; i < input.size(); i++) {
            input[i] = tolower(input[i]);
        }

        if (input == "y" || input == "yes") return true;
        if (input == "n" || input == "no") return false;

        cout << "I didn't understand that. ";
        cout << "Please enter y(es) or n(o).";
        cout << endl;
    }
}

string trim(string s) {
    int a, b;

    for (a = 0; a < s.size() && isspace(s[a]); a++);
    for (b = s.size() - 1; b >= a && isspace(s[b]); b--);

    return s.substr(a, b - a + 1);
}


