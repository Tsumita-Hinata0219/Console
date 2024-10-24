#include <iostream>
#include <variant>
#include <string>

// 型の定義（int と std::string のみを持つ）
using VarType = std::variant<int, std::string>;

class OtherClass {
public:
    void registerVariant(VarType& var) { // 引数を参照として受け取る
        // 特定の型を設定する例
        var = 20; // int型として20を設定
    }
};

int main() {
    VarType var; // std::variantの変数
    OtherClass obj; // OtherClassのインスタンス作成
    obj.registerVariant(var); // registerVariant関数を呼び出す

    // varがint型の場合、値を取得する
    if (std::holds_alternative<int>(var)) { // varがint型か確認
        int intValue = std::get<int>(var); // int型として取得
        std::cout << "Updated Variant (int): " << intValue << std::endl; // int型の値を表示
    }

    // varがstd::string型の場合、値を取得する例（こちらは使用していないが、例として示します）
    if (std::holds_alternative<std::string>(var)) { // varがstd::string型か確認
        std::string stringValue = std::get<std::string>(var); // std::string型として取得
        std::cout << "Updated Variant (string): " << stringValue << std::endl; // std::string型の値を表示
    }

    return 0;
}
