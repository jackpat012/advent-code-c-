#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>

using namespace std;

vector<long long> parser(string file) {															// Function to separate text file into long long's in vector.
	vector<long long> result;
	fstream File(file);
	string line;
	while (getline(File, line)) {
		string temp;
		for (int i = 0; i < line.size(); i++) {													// Loop to ignore dashes and commas.
			if ((line[i] == ',' || line[i] == '-') && temp != "") {
				result.push_back(stoll(temp));
				temp = "";
			}
			else if (i == (line.size() - 1)) {													// Catch last number in string.
				temp += line[i];
				result.push_back(stoll(temp));
				temp = "";
				break;
			}
			else {
				temp += line[i];
			}
		}
	}

	return result;
}

long long validCheck(vector<long long> arr) {
	long long sum = 0;
	for (int i = 0; i < arr.size(); i += 2) {													// Set odd indexes to beginning of range, even indexes to end of range.
		for (long long j = arr[i]; j <= arr[i + 1]; j++) {
			int digits = floor(log10(j)) + 1;													// Mathematically find number of digits in a given number.
			if (digits % 2 != 0) {																// Two repeats requires an even number of digits.
				continue;
			}
			int divisor = pow(10, digits / 2);													// Find divisor to have half of digits be fractional.
			int firstHalf = floor(j / divisor);
			int lastHalf = j - (divisor * firstHalf);
			if (firstHalf == lastHalf) {														
				sum += j;
			}
		}
	}
	return sum;
}

int main() {

	auto begin = chrono::high_resolution_clock::now();
	long long result = validCheck(parser("input.txt"));
	cout << "Result: " << result << endl;
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - begin);					
	cout << "Time: " << duration << endl;														// Executes in ~60 milliseconds on AMD 7800X3D.

	return 0;
}
