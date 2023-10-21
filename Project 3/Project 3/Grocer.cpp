#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <iterator>

using namespace std;

bool stop = false;
ifstream inFS;
int choice;
string itemSearch;
string currWord;
int wordFreq;
string produce;

// info about each item
class Produce {
public:
	void SetName(string produceName);
	void SetQuantity(int itemValue);
private:
	string name;
	int quantity;
};
//sets name of item
void Produce::SetName(string produceName) {
	name = produceName;
}
//sets quantity of item
void Produce::SetQuantity(int itemValue) {
	quantity = itemValue;
}

//menu display function
void menuDisplay() {
	cout << "Welcome to Corner Grocer's item tracking program" << endl;
	cout << endl << " 1 - Search item frequency" << endl;
	cout << " 2 - Print list of all items with number" << endl;
	cout << " 3 - Print list of all items with indicator" << endl;
	cout << " 4 - Exit Program" << endl;
	


}

int main() {

	map<string, int> stock;

	//opening the input file
	ifstream inputFile("CS210_Project_Three_Input_File.txt");

	//making sure the file opens correctly
	if (!inputFile) {
		cerr << "Error: Unable to open input file." << endl;
		return 1;
	}
	
	//opening the output file
	ofstream outputFile("frequency.dat");
	
	if (!outputFile) {
		cerr << "Error: Unable to open output file." << endl;
		return 1;
	}
	//initial while loop to iterate through the file and create and build the map of data
	while (!inputFile.eof()) {
		getline(inputFile, produce);
		if (!inputFile.fail()) {
			if (stock.count(produce) == 0) {
				stock.emplace(produce, 1);
				
			}
			else  {
				wordFreq = stock.at(produce) + 1;
				stock.erase(produce);
				stock.emplace(produce, wordFreq);
				
			}
		}
	}
	//printing data to file
	std::map<std::string, int>::iterator it = stock.begin();
	if (outputFile.is_open()) {
		for (auto i = stock.begin(); i != stock.end(); i++) {
			string word = it->first;
			int value = it->second;
			outputFile << word << " " << value << endl;
			it++;
		}
	}

	

	while (!stop) {
		menuDisplay();
		std::map<std::string, int>::iterator it = stock.begin();
		cin >> choice;
		switch (choice) {
			//menu entry 1 to allow user to search items to find values
		case 1:
			cout << "Enter item to search" << endl;
			cin >> produce;
			if (stock.count(produce) == 1) {
				cout << produce << " " << stock.at(produce) << endl;
			}
			else {
				cout << produce << " 0" << endl;
			}
			break;
			//menu entry 2 to print items with their individual values
		case 2:
			
			for (auto i = stock.begin(); i != stock.end(); i++) {
				string word = it->first;
				int value = it->second;
				cout << word << " " << value << endl;
				it++;
			}
			break;
			//menu entry 3 to print items with * as the value
		case 3:
			
			for (auto j = stock.begin(); j != stock.end(); j++) {
				string word = it->first;
				int value = it->second;
				string valueStar(value, '*');
				cout << word << " " << valueStar << endl;
				it++;
			}
			break;
			//menu entry 4 to exit the program
		case 4:
			cout << "Exiting program";
			stop = true;
			break;
			//simple attempt at a bit of an error catch for invalid inputs
		default:
			cout << "Please enter a valid input" << endl;
			break;
		}
		}


	//closing each file
	inputFile.close();
	outputFile.close();

	return 0;
}