/*
El Hadji Omar Bane
Keywords II
7/15/2022
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>

using namespace std;


void display_overview(bool skip = false); // gives the user an overview of the program and how to use it. Can be skipped for testing purposes
void display_directions(bool skip = false); // gives the user the programs directions. Can be skipped
string get_users_name(bool skip = false); // gets the user's name. can be skipped
string form_code_word(vector<string> source_vector); // gets three random words from the secret code word. can be skipped
char get_next_guess(vector<char>guessed_letters); // returns the user's guess
string get_fragmented_code_word(vector<char> used_letters, string code_word); // gets code word using the letters the user has used
bool test_user(string code_word);


int main() {
// Display Title of the program to the user
	cout << "Keywords II" << endl;

	string usersName = get_users_name(); // gets the user's name

	cout << "Welcome " << usersName << endl << endl;

	int simulationsRun = 1;// Create an int var to count the number of simulations being run starting at 1

	display_overview(); // Display an overview of what Keywords II is to the recruit 
	display_directions();// Display directions to the recruit on how to use Keywords

	const vector<string> KEYWORDS = {"Salamander", "Enigma", "Pheromone", "Seven", "Stone", "Tangable", "Redactable", "Kettle", "Crew", "Glass"};// Create a collection of 10 words you had written down manually
	
	int runningSimulation = true;
	cout << "Simulations ran: " << simulationsRun << endl;

	system("pause");
	system("CLS");
	while (runningSimulation) {
		bool guessedSecretWord = test_user(form_code_word(KEYWORDS));

		if (!guessedSecretWord) { cout << "You have failed the Keywords II course" << endl; }// If the recruit has made too many incorrect guesses

		else { cout << "congratulations!! You've guessed the secret words" << endl; }//Congratulate the recruit on guessing the secret words

	// Ask the recruit if they would like to run the simulation again
		cout << "would you like to run the simulation again?[y/n]" << endl;
		char usersChoice;
		cin >> usersChoice;

		if (tolower(usersChoice) == 'y') {// If the recruit wants to run the simulation again
			simulationsRun++;
			cout << "Simulations ran: " << simulationsRun << endl;// Display the simulation # is starting to the recruit. 
		}

		else {
			cout << "Then this concludes the simulation. Have a good day, " << usersName << "." << endl;
			system("pause");
			runningSimulation = false;
		}
		for (int i = 0; i < 5; i++) {
			cout << endl;
		}
	}
	
	return 0;
}

int myrandom(int i) { return std::rand() % i; }

string form_code_word(vector<string> source_vector) {
	srand(unsigned(time(0))); // initializes randomizer

	string code_word = "";
	
	random_shuffle(source_vector.begin(), source_vector.end(), myrandom); // shuffles the source vector

	vector<string> randomized_vector = source_vector; // setting the randomized vector to equal the randomized source words

	randomized_vector.erase(randomized_vector.begin(), randomized_vector.begin() + 7); // erases 7 of the 10 values 

	
	for (vector<string>::iterator i_randomized_vector = randomized_vector.begin(); i_randomized_vector < randomized_vector.end(); i_randomized_vector++) {code_word += *i_randomized_vector;} // adds the words on randomized vector onto the codeword

	return code_word;
}

char get_next_guess(vector<char>guessed_letters) {
	cout << "Guess a letter in the code word" << endl;
	char guess;

	cin >> guess;
	auto result = find(guessed_letters.begin(), guessed_letters.end(), guess);

	if (result == end(guessed_letters)) { return guess; } // letter has not been guessed yet
	else { return get_next_guess(guessed_letters); } // re-asks for guess
	}

string get_fragmented_code_word(vector<char> used_letters, string code_word) { // gets the code word but with the letters you have used
	string fragmented_word;

	for (int i = 0; i < code_word.length(); i++) { // goes through all the letterss of the code word

		auto uppercase_result = find(used_letters.begin(), used_letters.end(), toupper(code_word[i]));
		auto lowercase_result = find(used_letters.begin(), used_letters.end(), tolower(code_word[i]));

		// the character of the code word has been used
		if (uppercase_result != end(used_letters) || lowercase_result != end(used_letters)) { fragmented_word += code_word[i]; }
	}

	return fragmented_word;
}

void display_overview(bool skip) {
	if (!skip) {
		cout << "In this simulation, a code word is randomly made. Your goal is to find out what the code word is." << endl;
	}
	return;
}

void display_directions(bool skip) {
	if (!skip) {
		cout << "To pass the simulation, You are required to guess the letters in the code word." << endl;
	}
	
	return;
}

string get_users_name(bool skip) {
	if (skip) { return "Robert"; } // Doesn't ask what the user's name is and makes the name is Robert.

	cout << "what is your name?" << endl;

	string inputted_name;
	getline(cin, inputted_name);

	return inputted_name;

}

bool passed_simulation(vector<char> used_letters, string code_word){
	return get_fragmented_code_word(used_letters, code_word) == code_word;
	}

bool test_user(string code_word) {
	int incorrect_guesses = 0;
	int max_tries = round(code_word.length() / 2);
	vector<char> used_letters;

	while (incorrect_guesses < max_tries && !passed_simulation(used_letters, code_word)) {	// While recruit hasn’t made too many incorrect guesses and hasn’t guessed the secret word
		cout << "You have " << max_tries - incorrect_guesses << " tries left" << endl;// Tell recruit how many incorrect guesses he or she has left
		
		cout << endl;
		cout << "You have used the following letters: ";// Show recruit the letters he or she has guessed
		for (vector<char>::iterator i_used_letters = used_letters.begin(); i_used_letters < used_letters.end(); i_used_letters++) { cout << *i_used_letters << " "; } // displays all the letters guessed
		cout << endl;
		cout << "Currently, the code word looks like: " << get_fragmented_code_word(used_letters, code_word) << endl;// Show player how much of the secret word he or she has guessed

		cout << endl;
		char usersGuess = get_next_guess(used_letters);// Get recruit's next guess
		system("CLS");

		used_letters.push_back(usersGuess);// Add the new guess to the group of used letters

		if (code_word.find(tolower(usersGuess)) != string::npos || code_word.find(toupper(usersGuess)) != string::npos) {cout << "You have guessed correctly" << endl;} // If the guess is in the secret word

		else {
			cout << "Your guess was incorrect" << endl;	// Tell the recruit the guess is incorrect
			incorrect_guesses++;// Increment the number of incorrect guesses the recruit has made
		}
		cout << endl;
	}

	return passed_simulation(used_letters, code_word);
}