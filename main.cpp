#include <vector>
#include <iostream>

// ��ԃf�[�^��ێ�����N���X
class SpatialData {
public:
    SpatialData(int level, int index, int value)
        : level(level), index(index), value(value) {}

    int level;  // ���������ԃ��x��
    int index;  // ��ԓ��̃C���f�b�N�X
    int value;  // ���ۂ̃f�[�^
};

// ���`4���؂̃N���X
class LinearQuaternaryTree {
public:
    LinearQuaternaryTree(int maxLevel) : maxLevel(maxLevel) {
        int numNodes = 0;
        for (int i = 0; i <= maxLevel; ++i) {
            numNodes += 4 * (1 << (2 * i));  // 4^i �̃m�[�h
        }
        nodes.resize(numNodes, -1);  // �����l�Ƃ��� -1 ��ݒ�
    }

    void Insert(const SpatialData& data) {
        int offset = GetOffset(data.level);
        int nodeIndex = offset + data.index;
        if (nodeIndex < nodes.size()) {
            nodes[nodeIndex] = data.value;
        }
        else {
            std::cerr << "Invalid index!" << std::endl;
        }
    }

    int Query(int level, int index) {
        int offset = GetOffset(level);
        int nodeIndex = offset + index;
        if (nodeIndex < nodes.size()) {
            return nodes[nodeIndex];
        }
        else {
            std::cerr << "Invalid index!" << std::endl;
            return -1;
        }
    }

private:
    int maxLevel;
    std::vector<int> nodes;

    int GetOffset(int level) {
        int offset = 0;
        for (int i = 0; i < level; ++i) {
            offset += 4 * (1 << (2 * i));
        }
        return offset;
    }
};

int main() {
    int maxLevel = 3;  // �ő僌�x��
    LinearQuaternaryTree tree(maxLevel);

    // �f�[�^���쐬
    SpatialData data1(2, 5, 42);  // ���x��2�A�C���f�b�N�X5��42
    SpatialData data2(2, 6, 99);  // ���x��2�A�C���f�b�N�X6��99
    SpatialData data3(1, 3, 77);  // ���x��1�A�C���f�b�N�X3��77

    // �f�[�^��}��
    tree.Insert(data1);
    tree.Insert(data2);
    tree.Insert(data3);

    // �f�[�^���N�G��
    int dataValue1 = tree.Query(2, 5);
    int dataValue2 = tree.Query(2, 6);
    int dataValue3 = tree.Query(1, 3);

    std::cout << "level 2, space 5: " << dataValue1 << std::endl;
    std::cout << "level 2, space 6: " << dataValue2 << std::endl;
    std::cout << "level 1, space 3: " << dataValue3 << std::endl;




    return 0;
}

