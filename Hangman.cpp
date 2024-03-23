#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;
const int maxGuesses = 7;

class HangmanGame
{
public:
    string name;
    char letter;
    int wrongGuesses;
    string word;
    // REQ!! VECTORS. Define a new vector that hold all the words
    vector<string> words;

    HangmanGame() : wrongGuesses(0){};

    // Get suprise word from word.txt file
    void getWord(const string &filename)
{
    // Opens the file called words.txt and adds it to a list to pick a word from
    // STRETCH myself! This picks a random word from a words text file.
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Error: unable to open words.txt" << endl;
        exit(1);
    }

    // Adds the files to a string list to them be randomly selected
    string line;
    while (getline(inFile, line))
    {
        words.push_back(line); // Now, it populates the class member vector.
    }

    inFile.close();

    if (words.empty())
    {
        cerr << "Error: No words found in the file" << endl;
        exit(1);
    }
}


    void selectWord()
    {
        // generates a random number from 0-19
        srand(time(NULL));
        int n = rand() % 19;
        // This sets the word as the word at the ranom index we picked above
        word = words[n];
    }

    // Function for when the user guesses a word
    int guessLetterFill(char guess, string selectWord, string &guessWord){
        int matches = 0;
        int len = selectWord.length();
        for(int i = 0; i < len; i++){
            if (guess == guessWord[i])
                return 0;
            if (guess == selectWord[i]){
                guessWord[i] = guess;
                matches++;
            }
        }
        return matches;

    }


};

int main(){

    HangmanGame hangman;
    
    hangman.getWord("words.txt");
    hangman.selectWord();
    string unknownWord(hangman.word.length(), '$');


    string hangman_art[7] = {
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
        "=========="};

    // welcome player and explain the game
    cout << "\n••••••••••••••••••••••••••••••••••••••••••••••••••••••••••";
    cout << "\nWelcome to HANGMAN!!\n";
    cout << "A random word has been picked from a word list.\n";
    cout << "Each letter in the word has been changed to be a dollar sign.\n";
    cout << "It ranges from 3-5 letter words\n";
    cout << "You get" << maxGuesses << "number of tries to guess the word\n";
    cout << "LETS PLAY!";
    cout << "\n••••••••••••••••••••••••••••••••••••••••••••••••••••••••••";

    // Loop until the guesses are used up. until wrong guesses is less than max guesses!
    // REQ! CONDITIONALS. Uses logical math operations and a while statement.
    while (hangman.wrongGuesses < maxGuesses)
    {
        cout << "\n\n"
             << unknownWord;
        cout << "\n\nGuess a letter: ";
        cin >> hangman.letter;

        // REQ! CONDTIONALS. If statement
        if (hangman.guessLetterFill(hangman.letter, hangman.word, unknownWord) == 0)
        {

            cout << hangman_art[hangman.wrongGuesses + 1] << endl;
            cout << endl
                 << "Sorry, that letter is not in the word!" << endl;
            hangman.wrongGuesses++;
        }
        else
        {
            cout << hangman_art[hangman.wrongGuesses] << endl;
            cout << endl
                 << "Nice work. You got a letter!" << endl;
        }
        // This will let the user kow how many guesses they have left.
        // REQ! EXPRESSION to figure out how many guesses are left. It takes your max amount of guesses and subtracts how many guesses youve take.
        cout << "You have " << maxGuesses - hangman.wrongGuesses;
        cout << " guesses left." << endl;
        // Check if user guessed the word.
        if (hangman.word == unknownWord)
        {
            cout << hangman.word << endl;
            cout << "Congrats you got the secret word and lived!\n";
            break;
        }
    }
    if (hangman.wrongGuesses == maxGuesses)
    {
        cout << "Sorry, you lose...you've been hanged." << endl;
        cout << "The word was : " << hangman.word << endl;
    }
    cin.ignore();
    cin.get();
    return 0;
}
