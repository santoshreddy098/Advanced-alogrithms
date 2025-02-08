#include <iostream>
#include <string>
#include <vector>
using namespace std;

class LongestCommonSubstring {
private:
    void printTable(const vector<vector<int>>& dp, const string& str1, const string& str2) {
        cout << "\nDynamic Programming Table:\n";
        cout << "    ";
        for (char c : str2) {
            cout << c << " ";
        }
        cout << "\n";
        
        for (size_t i = 0; i <= str1.length(); i++) {
            if (i == 0) cout << "  ";
            else cout << str1[i-1] << " ";
            
            for (size_t j = 0; j <= str2.length(); j++) {
                cout << dp[i][j] << " ";
            }
            cout << "\n";
        }
    }

public:
    string findLCS(string str1, string str2) {
        // Create DP table
        vector<vector<int>> dp(str1.length() + 1, vector<int>(str2.length() + 1, 0));
        
        // Track maximum length and ending position
        int maxLength = 0;
        int endPosition = 0;
        
        // Fill the DP table
        for (size_t i = 1; i <= str1.length(); i++) {
            for (size_t j = 1; j <= str2.length(); j++) {
                if (str1[i-1] == str2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    if (dp[i][j] > maxLength) {
                        maxLength = dp[i][j];
                        endPosition = i - 1;
                    }
                }
            }
        }
        
        // Print the DP table
        printTable(dp, str1, str2);
        
        // Extract and return the longest common substring
        return str1.substr(endPosition - maxLength + 1, maxLength);
    }
};

int main() {
    LongestCommonSubstring lcs;
    string str1, str2;
    
    while (true) {
        // Get first string
        cout << "Enter the first string: ";
        getline(cin, str1);
        
        // Get second string
        cout << "Enter the second string: ";
        getline(cin, str2);
        
        // Validate string lengths
        if (str1.length() != str2.length()) {
            cout << "Error: Strings must be of equal length!\n";
            cout << "String 1 length: " << str1.length() << "\n";
            cout << "String 2 length: " << str2.length() << "\n";
            cout << "Please try again.\n\n";
            continue;
        }
        
        // Validate that strings are not empty
        if (str1.empty() || str2.empty()) {
            cout << "Error: Strings cannot be empty! Please try again.\n\n";
            continue;
        }
        
        // Display input strings
        cout << "\nString 1: " << str1 << endl;
        cout << "String 2: " << str2 << endl;
        
        // Find and display result
        string result = lcs.findLCS(str1, str2);
        cout << "\nOne of the longest common substrings: " << result << endl;
        cout << "Length of longest common substring: " << result.length() << endl;
        
        // Ask if user wants to try again
        char tryAgain;
        cout << "\nWould you like to try another pair of strings? (y/n): ";
        cin >> tryAgain;
        cin.ignore(); // Clear the newline character from input buffer
        
        if (tolower(tryAgain) != 'y') {
            cout << "Thank you for using the program!\n";
            break;
        }
        cout << "\n";
    }
    
    return 0;
}