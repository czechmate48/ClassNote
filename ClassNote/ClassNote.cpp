#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <cstring>
using namespace std;

char const FILE_PATH[13] = "FilePath.txt"; //holds the name of the filePath text file name constant

void CreateFilePathTextFile(); //Creates a filepath text file in case one doesn't already exist
void OpenFile(char* argv); //Opens the text file sent in as an argument
void SetFilePath(); //Sets the path for text file (note) retrieval
void DisplayHelpScreen(); //Displays the help screen 

int main(int argc, char* argv[]) {
	
	bool modifier = false; //Tells whether the command line input contains a modifier
	char fpOption[4] = "-fp"; //Leave one space for the null terminator
	char filePathOption[11] = "--filePath"; //Same as fp but in extended form
	char hOption[3] = "-h";
	char helpOption[7] = "--help";

	CreateFilePathTextFile();

	if (argc > 1) {
		for (int i = 0; i < argc; ++i) {
			if (strcmp(fpOption, argv[i]) == 0 || strcmp(filePathOption, argv[i]) == 0) { //You are comparing to cstrings here, not regular string variables. NOTE -> RETURNS 0 IF EQUAL NOT 1
				SetFilePath();
				modifier = true;
			}
			else if (strcmp(hOption, argv[i]) == 0 || strcmp(helpOption, argv[i]) == 0) {
				DisplayHelpScreen();
				modifier = true;
			}
		}
	}

	if (!modifier && argc > 1) { //If there is no modifier and there is another argument (a notepad file)
		OpenFile(argv[1]);
	}

	return 0;
}

void CreateFilePathTextFile() {
	//if ()
}

void OpenFile(char* argv) {

	string filePath = "";
	string curString = ""; //holds the current string data being read by the instreams to read the filepath and open the file
	char curChar = ' '; //holds the current char being read from the file. MUST use a char as string will prevent noskipws from working correctly
	string fileName = argv; //holds the name of the file to be read

	ifstream instream(FILE_PATH);

	if (!instream) {
		cout << endl << "ERROR 1: UNABLE TO OPEN FILE ";
		cout << endl << "Please make sure the file path is set correctly. ";
		cout << "If errors persist, please use the '--filePath' modifier to set the read path." << endl;
		cout.flush(); //Don't forget to flush!
		exit(1); //Exits the program
	}

	while (!instream.eof()) {
		instream >> curString;
		filePath = filePath + curString;
		filePath = filePath + " "; //Append a space as the instream will skip spaces
	}

	filePath.erase(filePath.begin() + (filePath.length() - 1), filePath.begin() + filePath.length()); //Removes the unnecessary space placed at the end
	instream.close(); //Close the filestream to open a new one

	instream.open(filePath + "\\" + fileName + ".txt"); //Add .txt in the program so the command doesn't require it. 

	if (!instream) {
		cout << endl << "ERROR 2: UNABLE TO OPEN FILE " << endl;
		cout << endl << "Troubleshooting step 1: Make sure the name of the file is spelled correctly.";
		cout << endl << "Troubleshooting step 2: Ensure the file is located inside the folder set by the File Path. " << endl;
		cout << endl << "If errors persist, please use '--help' modifier to investigate further." << endl;
		cout.flush(); //Don't forget to flush!
		exit(1); //Exits the program
	}

	cout << endl; //New line just for cleaninless and readability;

	while (!instream.eof()) {
		instream >> noskipws >> curChar;
		cout << curChar;
	}

	cout << endl; //New line just for cleaninless and readability;

}

void SetFilePath() {

	cout << "Please enter a file path: ";

	string filePath = " "; //File path input by user
	ofstream outStream(FILE_PATH);

	getline(cin, filePath);

	char filePathChar[100];
	strcpy_s(filePathChar, filePath.c_str());

	for (int i = 0; filePathChar[i] != '\0'; ++i) {
		outStream << filePathChar[i];
	}

	return;

}

void DisplayHelpScreen() {

	cout << endl << "DESCRIPTION" << endl;
	cout << endl << "Prints the contents of a text file into the command line to allow easy access to personal notes " << endl;
	cout << endl << "USAGE" << endl;
	cout << endl << "Command [OPTION] Filename" << endl;
	cout << endl << "OPTIONS" << endl;
	cout << endl << "-fp, --filePath " << endl << "     " << "set the location (directory) where personal notes are stored" << endl;
	cout << endl << "-h, --help " << endl << "     " << "display this help and exit" << endl;
}
