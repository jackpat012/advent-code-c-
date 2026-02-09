#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

using namespace std;

vector<long long> parser(string filename) {
    ifstream File(filename);                                                                                    // Load File
    string line;
    vector<string> commasRemoved;                                                                               // Temp array for hosting removed commas
    vector<long long> dashesRemoved;                                                                            // Output array
       
    while (getline(File, line)) {                                                                               // Loop to remove commas, push into temp array {xxxx-yyyy, wwww-zzzz, ... }
        string temp = "";
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                if (!temp.empty()) {
                    commasRemoved.push_back(temp);
                }
                temp = ""; 
            }
            else {
                temp += line[i];
            }
        }
        if (!temp.empty()) {
            commasRemoved.push_back(temp);
        }
    }
    File.close();
    for (int i = 0; i < commasRemoved.size(); i++) {                                                            // Loop to remove dashes, push numbers into individual elements {xxxx, yyyy, wwww, zzzz, ... }
        string numTemp = "";
        for (int j = 0; j < commasRemoved[i].size(); j++) {
            if (commasRemoved[i][j] == '-') {
                if (!numTemp.empty()) {
                    dashesRemoved.push_back(stoll(numTemp));
                }
                numTemp = "";
            }
            else if (isdigit(commasRemoved[i][j])) { 
                numTemp += commasRemoved[i][j];
            }
        }
        if (!numTemp.empty()) {
            dashesRemoved.push_back(stoll(numTemp));
        }
    }
    return dashesRemoved;
}

long long validCheck(vector<long long> nums) {
    long long count = 0;
    for (long long i = 0; i < nums.size(); i += 2) {
        for (long long j = nums[i]; j <= nums[i + 1]; j++) {                                                    // Odd indexes are beginning of range, even indexes are end of range.
            string numString = to_string(j);
            long long digits = numString.size();
            if (digits % 2 != 0) {                                                                              // Skip if number of digits in an integer are odd.
                continue;
            }
            string firstHalf = numString.substr(0, digits / 2);
            string secondHalf = numString.substr(digits / 2);
            if (firstHalf == secondHalf) {                                                                      // Compare first half of number with second half, if equal then number is invalid.
                count += j;
            }
        }
    }
    return count;
 }

int main() {

    auto now = chrono::high_resolution_clock::now();
	vector<long long> arr = parser("input.txt");
    long long counter = validCheck(arr);
    auto stop = chrono::high_resolution_clock::now();

    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(stop - now) << endl;                        // ~1.46s on AMD 7800X3D
    cout << "Result: " << counter << endl;

	return 0;
}
