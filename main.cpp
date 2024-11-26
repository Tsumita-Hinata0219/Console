#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {

    string moji;
    cin >> moji;

    vector<string> v;

    bool end = false;;

    while (!end) {
        string s{};
        getline(cin, s);
        stringstream ss{ s };
        if (s == "END_OF_TEXT") {
            end = true;
            break;
        }
        while (getline(ss, s, ' ')) {     // スペース（' '）で区切って，格納
            v.push_back(s);
        }
    }

    int count = 0;
    for (auto& e : v) {
        transform(e.begin(), e.end(), e.begin(), ::tolower);
        transform(moji.begin(), moji.end(), moji.begin(), ::tolower);
        if (e.find(moji) != string::npos) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}
