#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class Demo {
    std::vector<int*> values; // int のポインタを保持する

public:
    void Register(int* value) { // ポインタを受け取る
        values.push_back(value);
    }

    void PrintValues() const {
        for (int* value : values) {
            std::cout << *value << " "; // ポインタが指す値を表示
        }
        std::cout << std::endl;
    }
};

class Test {
    int value = 0;
    Demo* demo = nullptr;

public:
    void Init() {
        value = 10;
        demo = new Demo();
        demo->Register(&value); // value のアドレスを登録
    }

    void Update() {
        value += 10; // value を更新
    }

    void PrintDemoValues() const {
        demo->PrintValues();
    }
};

int main(void) {
    Test* test = new Test();
    test->Init();

    // 登録した Demo 内の値を確認
    test->PrintDemoValues(); // 10

    test->Update();

    // 更新後の値を確認
    test->PrintDemoValues(); // 20

    delete test;
    return 0;
}
