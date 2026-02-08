#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>

using namespace std;

int rotary(string filename) {
	ifstream File(filename);																			// Read text file in.
	string line;
	long long position = 50;																			// Starting position of "Dial".
	int counter = 0;


	if (File.is_open()) {
		while (getline(File, line)) {																	// Iterate through all lines of file.
			int move = stoi(line.substr(1));
			if (line[0] == 'L') {																		// Check to see if integer should be negative.
				move = -move;		
			}
			for (int i = 1; i <= abs(move); i++) {														// Loops to adjust position, first is if move is positive, second is if move is negative.
				if (move > 0) {
					position++;
					if (position == 100) {
						position = 0;
					}
				}
				else {
					position--;
					if (position == -1) {
						position = 99;
					}
				}
				if (position == 0) {
					counter++;
				}
			}
		}
	}
	return counter;
}


int main() {
	auto start = chrono::high_resolution_clock::now();
	int result = rotary("input.txt");
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << "Result: " << result << endl;
	cout << "Time taken: " << duration.count() << " microseconds." << endl;								// ~5900 microseconds on AMD 7800X3D.

	return 0;
}
