#include <vector>
#include <cmath>
#include <iostream>
#include <list>

// ��ԃf�[�^��ێ�����N���X
class SpatialData {
public:
    SpatialData(int level, int index, int value)
        : level(level), index(index), value(value) {}

    int level;  // ���������ԃ��x��
    int index;  // ��ԓ��̃C���f�b�N�X
    int value;  // ���ۂ̃f�[�^
};

// ���`�l���؃N���X
class LinearQuadtree {
private:
    std::vector<std::list<int>> nodes_;  // ���`�z��Ŏl���؂�ێ�����i���X�g�ɕύX�j
    int levelDepth_;                     // ��ԃ��x���̐[��

public:

    LinearQuadtree(int depth) : levelDepth_(depth) {
        int numNodes = 0;

        // ��ԃ��x���̐[���ɉ������m�[�h�����v�Z
        for (int i = 0; i <= levelDepth_ - 1; ++i) {
            numNodes += int(std::pow(4, i));  // 4^i �̃m�[�h
        }

        // ���`�z��̃T�C�Y��ݒ肵�A�����l�Ƃ��ċ�̃��X�g��ݒ�
        nodes_.resize(numNodes);
    }

    // ���䋉���̘a���g���āA���x��L�̍ŏ��̗v�f�ԍ����v�Z
    int levelOffset(int level) const {
        if (level == 0) return 0;
        return (pow(4, level) - 1) / 3;
    }

    // ���x��L�ł̃m�[�h�ԍ�N�ɑΉ�����z��C���f�b�N�X���v�Z
    int getIndex(int level, int nodeNumber) const {
        return levelOffset(level) + nodeNumber;
    }

    // SpatialData ����l��}��
    void insertSpatialData(const SpatialData& data) {
        int index = getIndex(data.level, data.index);
        if (index < nodes_.size()) {
            nodes_[index].push_back(data.value);  // �����C���f�b�N�X�ɒl��ǉ�
        }
        else {
            std::cerr << "Error: Index out of bounds" << std::endl;
        }
    }

    // ���`�l���؂���l���擾�i�����̒l������ꍇ���ׂĕԂ��j
    std::list<int> getValues(int level, int nodeNumber) const {
        int index = getIndex(level, nodeNumber);
        if (index < nodes_.size()) {
            return nodes_[index];
        }
        else {
            std::cerr << "Error: Index out of bounds" << std::endl;
            return std::list<int>();  // �G���[���̕Ԃ�l�Ƃ��ċ󃊃X�g
        }
    }

    // �l���؂̏�Ԃ�\��
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

    // SpatialData ���g���Ēl��ݒ�
    std::vector<SpatialData> spatialDataList = {
        SpatialData(0, 0, 10),  // ���[�g��� 10   
        SpatialData(1, 0, 20),  // �e���  0�Ԗ� 20
        SpatialData(1, 1, 30),  // �e���  1�Ԗ� 30
        SpatialData(2, 11, 40), // �q��� 11�Ԗ� 40
        SpatialData(3, 47, 50), // ����� 47�Ԗ� 50
        SpatialData(1, 0, 60),  // �e���  0�Ԗ� 60
        SpatialData(3, 63, 600), // ����� 63�Ԗ� 600
    };

    for (const auto& data : spatialDataList) {
        quadtree.insertSpatialData(data);
    }

    // �l���؂�\��
    quadtree.printTree();

    return 0;
}

