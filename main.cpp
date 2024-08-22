#include <vector>
#include <cmath>
#include <iostream>
#include <list>

// 空間データを保持するクラス
class SpatialData {
public:
    SpatialData(int level, int index, int value)
        : level(level), index(index), value(value) {}

    int level;  // 所属する空間レベル
    int index;  // 空間内のインデックス
    int value;  // 実際のデータ
};

// 線形四分木クラス
class LinearQuadtree {
private:
    std::vector<std::list<int>> nodes_;  // 線形配列で四分木を保持する（リストに変更）
    int levelDepth_;                     // 空間レベルの深さ

public:

    LinearQuadtree(int depth) : levelDepth_(depth) {
        int numNodes = 0;

        // 空間レベルの深さに応じたノード数を計算
        for (int i = 0; i <= levelDepth_ - 1; ++i) {
            numNodes += int(std::pow(4, i));  // 4^i 個のノード
        }

        // 線形配列のサイズを設定し、初期値として空のリストを設定
        nodes_.resize(numNodes);
    }

    // 等比級数の和を使って、レベルLの最初の要素番号を計算
    int levelOffset(int level) const {
        if (level == 0) return 0;
        return (pow(4, level) - 1) / 3;
    }

    // レベルLでのノード番号Nに対応する配列インデックスを計算
    int getIndex(int level, int nodeNumber) const {
        return levelOffset(level) + nodeNumber;
    }

    // SpatialData から値を挿入
    void insertSpatialData(const SpatialData& data) {
        int index = getIndex(data.level, data.index);
        if (index < nodes_.size()) {
            nodes_[index].push_back(data.value);  // 同じインデックスに値を追加
        }
        else {
            std::cerr << "Error: Index out of bounds" << std::endl;
        }
    }

    // 線形四分木から値を取得（複数の値がある場合すべて返す）
    std::list<int> getValues(int level, int nodeNumber) const {
        int index = getIndex(level, nodeNumber);
        if (index < nodes_.size()) {
            return nodes_[index];
        }
        else {
            std::cerr << "Error: Index out of bounds" << std::endl;
            return std::list<int>();  // エラー時の返り値として空リスト
        }
    }

    // 四分木の状態を表示
    void printTree() const {
        for (int i = 0; i < nodes_.size(); ++i) {
            std::cout << "Index " << i << ": ";
            for (int value : nodes_[i]) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int maxLevel = 4;
    LinearQuadtree quadtree(maxLevel);

    // SpatialData を使って値を設定
    std::vector<SpatialData> spatialDataList = {
        SpatialData(0, 0, 10),  // ルート空間 10   
        SpatialData(1, 0, 20),  // 親空間  0番目 20
        SpatialData(1, 1, 30),  // 親空間  1番目 30
        SpatialData(2, 11, 40), // 子空間 11番目 40
        SpatialData(3, 47, 50), // 孫空間 47番目 50
        SpatialData(1, 0, 60),  // 親空間  0番目 60
        SpatialData(3, 63, 600), // 孫空間 63番目 600
    };

    for (const auto& data : spatialDataList) {
        quadtree.insertSpatialData(data);
    }

    // 四分木を表示
    quadtree.printTree();

    return 0;
}

