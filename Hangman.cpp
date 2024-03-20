#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

const int maxGuesses = 7;
int letterFill(char, string, string &);

int main()
{
    std::string hangman_art[7] = {
    " +---+\n"
    " |   |\n"
    "     |\n"
    "     |\n"
    "     |\n"
    "     |\n"
    "==========",
    " +---+\n"
    " |   |\n"
    " O   |\n"
    "     |\n"
    "     |\n"
    "     |\n"
    "==========",
    " +---+\n"
    " |   |\n"
    " O   |\n"
    " |   |\n"
    "     |\n"
    "     |\n"
    "==========",
    " +---+\n"
    " |   |\n"
    " O   |\n"
    "/|   |\n"
    "     |\n"
    "     |\n"
    "==========",
    " +---+\n"
    " |   |\n"
    " O   |\n"
    "/|\\  |\n"
    "     |\n"
    "     |\n"
    "==========",
    " +---+\n"
    " |   |\n"
    " O   |\n"
    "/|\\  |\n"
    "/    |\n"
    "     |\n"
    "==========",
    " +---+\n"
    " |   |\n"
    " O   |\n"
    "/|\\  |\n"
    "/ \\  |\n"
    "     |\n"
    "=========="
};
    // Sets variables that will be used in the game
    string name;
    char letter;
    int wrongGuesses = 0;
    string word;

    // Opens the file called words.txt and adds it to a list to pick a word from
    ifstream inFile("words.txt");
    if (!inFile)
    {
        cerr << "Error: undable to open words.txt" << endl;
        return 1;
    }

    // Adds the files to a string list to them be randomly selected
    vector<string> words;
    string line;
    while (getline(inFile, line))
    {
        words.push_back(line);
    }

    inFile.close();

    if (words.empty())
    {
        cerr << "Error: No words found in words.txt" << endl;
        return 1;
    }

    // generates a random number from 0-19
    srand(time(NULL));
    int n = rand() % 19;
    //This sets the word as the word at the ranom index we picked above
    word = words[n];

    // Get the new word and change the characters to _
    string unknownWord(word.length(), '$');

    // welcome player and explain the game
    cout << "\n••••••••••••••••••••••••••••••••••••••••••••••••••••••••••";
    cout << "\nWelcome to HANGMAN!!\n";
    cout << "A random word has been picked from a word list.\n";
    cout << "Each letter in the word has been changed to be a dollar sign.\n";
    cout << "It ranges from 3-5 letter words\n";
    cout << "You get"<< maxGuesses << "number of tries to guess the word\n";
    cout << "LETS PLAY!";
    cout << "\n••••••••••••••••••••••••••••••••••••••••••••••••••••••••••";

    // Loop until the guesses are used up. until wrong guesses is less than max guesses!
    while (wrongGuesses < maxGuesses)
    {
        cout << "\n\n"
             << unknownWord;
        cout << "\n\nGuess a letter: ";
        cin >> letter;

        if (letterFill(letter, word, unknownWord) == 0)
        {
        
            cout << hangman_art[wrongGuesses + 1] << endl;
            cout << endl
                 << "Sorry, that letter is not in the word!" << endl;
            wrongGuesses++;
        }
        else
        {
            cout << hangman_art[wrongGuesses] << endl;
            cout << endl
                 << "Nice work. You got a letter!" << endl;
        }
        // This will let the user kow how many guesses they have left.
        cout << "You have " << maxGuesses - wrongGuesses;
        cout << " guesses left." << endl;
        // Check if user guessed the word.
        if (word == unknownWord)
        {
            cout << word << endl;
            cout << "Congrats you got the secret word and lived!\n";
            break;
        }
    }
    if (wrongGuesses == maxGuesses)
    {
        cout << "Sorry, you lose...you've been hanged." << endl;
        cout << "The word was : " << word << endl;
    }
    cin.ignore();
    cin.get();
    return 0;
}


int letterFill(char guess, string secretword, string &guessword)
{
    int i;
    int matches = 0;
    int len = secretword.length();
    for (i = 0; i < len; i++)
    {
        if (guess == guessword[i])
            return 0;

        if (guess == secretword[i])
        {
            guessword[i] = guess;
            matches++;
        }
    }
    return matches;
}