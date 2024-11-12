#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

struct VEC2 {
    double x;
    double y;
};

int main()
{
    // 入力を受け取る
    std::string input;
    std::getline(std::cin, input);
    // いったん出力
    std::cout << input << std::endl;

    // 初期座標 原点座標 角度
    VEC2 init;
    VEC2 origin;
    double angle;

    // 値を取り出す
    std::stringstream ss(input);
    ss >> init.x >> init.y >> origin.x >> origin.y >> angle;
    // いったん出力
    std::cout << init.x << " " << init.y << std::endl;
    std::cout << origin.x << " " << origin.y << std::endl;
    std::cout << angle << std::endl;

    // targetを求める
    angle = angle * (3.1415926535897932 / 180); // 度数法->弧度法
    VEC2 target = {
        (init.x - origin.x) * std::cos(angle) - (init.y - origin.y) * std::sin(angle) + origin.x,
        (init.x - origin.x) * std::sin(angle) + (init.y - origin.y) * std::cos(angle) + origin.y,
    };

    // 小さい数を0として処理するための閾値
    const double EPSILON = 1e-5;

    // 非常に小さい値を0として表示
    if (std::abs(target.x) < EPSILON) target.x = 0.0;
    if (std::abs(target.y) < EPSILON) target.y = 0.0;

    std::cout << target.x << " " << target.y << std::endl;

    return 0;
}
