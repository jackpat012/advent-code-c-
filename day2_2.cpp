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
	for (int i = 0; i < arr.size(); i += 2) {													
		for (long long j = arr[i]; j <= arr[i + 1]; j++) {
			int digits = floor(log10(j)) + 1;													// Find number of digits in number.													
			int P, k = 0;
			for (k = 1; k <= floor(digits / 2); k++) {											// Geometric Test for Periodicity.
				if (digits % k != 0) {															// All periodic numbers are evenly divisible by k.
					continue;
				} 
				else {														
					int divisor = pow(10, (digits - k));										
					P = floor(j / divisor);														// If it exists, P is the repeating portion of the integer.
					long long interim = P * ((pow(10, digits) - 1) / (pow(10, k) - 1));			// If a number is periodic, j = P.
					if (j == interim) {
						sum += j;
						break;																	// No need to test for additional k values if j is periodic for one k.
					}
				}
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
	cout << "Time: " << duration << endl;														// Executes in ~300 milliseconds on AMD 7800X3D.

	return 0;
}
