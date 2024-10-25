#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

string Convertor(const string& input) {
    // Leet•¶Žš‚Ì‘Î‰ž•\
    unordered_map<char, char> leetMap = {
        {'A', '4'}, {'E', '3'}, {'G', '6'}, {'I', '1'},
        {'O', '0'}, {'S', '5'}, {'Z', '2'}
    };

    string resutl;
    for (char str : input) {
        // ‘Î‰ž•\‚É‚ ‚ê‚Î’u‚«Š·‚¦‚é
        if (leetMap.find(str) != leetMap.end()) {
            resutl += leetMap[str];
        }
        else {
            resutl += str;
        }
    }
    return resutl;
}

int main(void) {

    string input;
    cin >> input;
    string leetStr = Convertor(input);
    cout << leetStr << endl;

	return 0;
}
