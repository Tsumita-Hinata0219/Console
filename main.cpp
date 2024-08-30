#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;


int main(void) {

    // “ú”
    int N = 0;
    cin >> N;

    //”„”ƒğŒ
    int c_1 = 0; int c_2 = 0;
    cin >> c_1;
    cin >> c_2;

   // Še“ú‚ÌŠ”‰¿
    std::vector<int> prices(N);
    for (int i = 0; i < N; ++i) {
        cin >> prices[i];
    }

    // ‘¹‰v
    int cash = 0;
    // ‚¿Š”
    int stock = 0;

    for (int i = 0; i < N; ++i) {

        int p = prices[i];

        if (p <= c_1) {
            stock++;
            cash -= p;
        }
        else if (p <= c_2) {
            cash += stock * p;
            stock = 0;
        }
    }

    cash += stock * prices[N - 1];

    cout << cash << endl;


    return 0;
}