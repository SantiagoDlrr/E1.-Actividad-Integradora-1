#include "transmission.h"

string readFile(const string &path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Failed to open " << path << endl;
        return "";
    }

    string line, content;
    while (getline(file, line)) {
        content += line + " ";
    }

    file.close();
    return content;
}

void printZValues(vector<int> &v){
    for(int i : v){
        cout << i << " ";
    }
    cout << endl;
}

vector<int> zNaive(const string &S) {
    size_t n = S.length();              // Use size_t for string size
    vector<int> A(n, 0);
    for (size_t i = 1; i < n; i++) {    // Use size_t for loop indices
        for (size_t j = i; j < n; j++) {
            if (S[j] == S[j - i]) {
                A[i]++;
            } else
                break;
        }
    }
    return A;
}


int analyzeTransmission(const string &tpath, const string &mpath) {
    ifstream transmissiontxt(tpath); 
    ifstream mcodetxt(mpath); 

    if (!transmissiontxt.is_open() || !mcodetxt.is_open()) {
        cout << "Failed to open one of the files" << endl;
        return -1;
    }

    string tline, transmission, mline, mcode;
    while (getline(transmissiontxt, tline)) {
        transmission += tline + " ";
    }
    while (getline(mcodetxt, mline)) {
        mcode += mline + " ";
    }

    transmissiontxt.close();
    mcodetxt.close();

    string zString = mcode + "$" + transmission;
    vector<int> zValues = zNaive(zString);

    for (size_t i = 0; i < zValues.size(); i++) {  // Use size_t for loop indices
        if (zValues[i] == static_cast<int>(mcode.length())) {
            return static_cast<int>(i - mcode.length()); // Cast to int
        }
    }

    return -1;
}


pair<int, string> longestPalindrome(const string &s) {
    int n = s.size();
    if (n == 0) return {0, ""};

    int start = 0, maxLength = 1;

    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }

    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    for (int length = 3; length <= n; ++length) {
        for (int i = 0; i < n - length + 1; ++i) {
            int j = i + length - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                start = i;
                maxLength = length;
            }
        }
    }

    return {start + 1, s.substr(start, maxLength)};
}

void analyzePalindromes(const vector<string> &files) {
    for (const string &transmissionFile : files) {
        string transmission = readFile(transmissionFile);

        transmission.erase(remove(transmission.begin(), transmission.end(), ' '), transmission.end());

        if (!transmission.empty()) {
            pair<int, string> result = longestPalindrome(transmission);
            int startIdx = result.first;
            int endIdx = startIdx + result.second.size() - 1;

            cout << startIdx << " " << endIdx << " " << result.second << endl;
        } else {
            cout << "Error al leer el archivo " << transmissionFile << endl;
        }
    }
}

pair<int, int> longestCommonSubstring(const string &s1, const string &s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    int maxLength = 0;
    int endIdx = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;

                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIdx = i - 1;
                }
            }
        }
    }

    return {endIdx - maxLength + 1, endIdx};
}