#include <iostream>
#include <vector>
#include <list>
#include <cmath>

// ダミーのCCellクラス（必要に応じて詳細を実装してください）
class CCell {
public:
    int id;  // 空間を識別するためのID（仮）
    CCell(int id) : id(id) {}
};
template <class T>
struct OBJECT_FOR_TREE {
    CCell* m_pCell;            // 登録されている小空間
    T* m_pObject;              // 任意オブジェクトへのポインタ
    OBJECT_FOR_TREE* m_pPre;   // 前の構造体へのポインタ
    OBJECT_FOR_TREE* m_pNext;  // 次の構造体へのポインタ

    OBJECT_FOR_TREE() : m_pCell(nullptr), m_pObject(nullptr), m_pPre(nullptr), m_pNext(nullptr) {}
};

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
    std::vector<std::list<OBJECT_FOR_TREE<int>>> nodes_;  // ノード内のオブジェクトリスト
    int levelDepth_;  // 空間レベルの深さ

    // 空間レベルの深さに応じたノード数を計算
    int levelOffset(int level) const {
        if (level == 0) return 0;
        return (std::pow(4, level) - 1) / 3;
    }

    // レベルLでのノード番号Nに対応する配列インデックスを計算
    int getIndex(int level, int nodeNumber) const {
        return levelOffset(level) + nodeNumber;
    }

    // ノードにオブジェクトを追加
    void addObjectToNode(int index, OBJECT_FOR_TREE<int>* obj) {
        nodes_[index].push_back(*obj);
        if (!nodes_[index].empty()) {
            obj->m_pPre = &nodes_[index].back(); // リストの末尾に追加
            if (nodes_[index].size() > 1) {
                obj->m_pPre->m_pNext = obj; // 前のオブジェクトの次を設定
            }
        }
    }

    // ノードからオブジェクトを削除
    void removeObjectFromNode(int index, OBJECT_FOR_TREE<int>* obj) {
        auto& nodeList = nodes_[index];
        for (auto it = nodeList.begin(); it != nodeList.end(); ++it) {
            if (&(*it) == obj) {
                if (obj->m_pPre) {
                    obj->m_pPre->m_pNext = obj->m_pNext;
                }
                if (obj->m_pNext) {
                    obj->m_pNext->m_pPre = obj->m_pPre;
                }
                nodeList.erase(it);
                break;
            }
        }
    }

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

    // オブジェクトの挿入
    void insertSpatialData(const SpatialData& data, OBJECT_FOR_TREE<int>* obj) {
        int index = getIndex(data.level, data.index);
        if (index < nodes_.size()) {
            addObjectToNode(index, obj);
            obj->m_pCell = nullptr;  // 初期化 (適宜設定)
        }
        else {
            std::cerr << "Error: Index out of bounds" << std::endl;
        }
    }

    // オブジェクトの移動
    void moveObject(int oldLevel, int oldIndex, int newLevel, int newIndex, OBJECT_FOR_TREE<int>* obj) {
        int oldIndexInArray = getIndex(oldLevel, oldIndex);
        int newIndexInArray = getIndex(newLevel, newIndex);

        if (oldIndexInArray < nodes_.size() && newIndexInArray < nodes_.size()) {
            removeObjectFromNode(oldIndexInArray, obj);
            addObjectToNode(newIndexInArray, obj);
            obj->m_pCell = nullptr;  // 初期化 (適宜設定)
        }
        else {
            std::cerr << "Error: Index out of bounds" << std::endl;
        }
    }

    // オブジェクトの削除
    void removeObject(int level, int index, OBJECT_FOR_TREE<int>* obj) {
        int indexInArray = getIndex(level, index);
        if (indexInArray < nodes_.size()) {
            removeObjectFromNode(indexInArray, obj);
        }
        else {
            std::cerr << "Error: Index out of bounds" << std::endl;
        }
    }

    // 線形四分木の状態を表示
    void printTree() const {
        for (int i = 0; i < nodes_.size(); ++i) {
            std::cout << "Index " << i << ": ";
            for (const auto& obj : nodes_[i]) {
                std::cout << obj.m_pObject << " ";
            }
            std::cout << std::endl;
        }
    }
};

// テスト用コード
int main() {
    LinearQuadtree quadtree(3);  // 深さ3の四分木を作成

    OBJECT_FOR_TREE<int> obj1, obj2, obj3;

    SpatialData data1(1, 2, 10);  // レベル1、インデックス2のデータ
    SpatialData data2(2, 1, 20);  // レベル2、インデックス1のデータ

    obj1.m_pObject = new int(data1.value);
    obj2.m_pObject = new int(data2.value);
    obj3.m_pObject = new int(30);  // テスト用の追加オブジェクト

    // オブジェクトの挿入
    quadtree.insertSpatialData(data1, &obj1);
    quadtree.insertSpatialData(data2, &obj2);
    quadtree.insertSpatialData(SpatialData(1, 2, 30), &obj3);

    // 状態表示
    std::cout << "Initial state:" << std::endl;
    quadtree.printTree();

    // オブジェクトの移動
    quadtree.moveObject(1, 2, 2, 1, &obj1);

    // 状態表示
    std::cout << "After moving obj1:" << std::endl;
    quadtree.printTree();

    // オブジェクトの削除
    quadtree.removeObject(2, 1, &obj2);

    // 状態表示
    std::cout << "After removing obj2:" << std::endl;
    quadtree.printTree();

    // メモリ解放
    delete obj1.m_pObject;
    delete obj2.m_pObject;
    delete obj3.m_pObject;

    return 0;
}
