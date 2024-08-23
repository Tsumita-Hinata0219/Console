#include <iostream>
#include <vector>
#include <list>
#include <cmath>

// �_�~�[��CCell�N���X�i�K�v�ɉ����ďڍׂ��������Ă��������j
class CCell {
public:
    int id;  // ��Ԃ����ʂ��邽�߂�ID�i���j
    CCell(int id) : id(id) {}
};
template <class T>
struct OBJECT_FOR_TREE {
    CCell* m_pCell;            // �o�^����Ă��鏬���
    T* m_pObject;              // �C�ӃI�u�W�F�N�g�ւ̃|�C���^
    OBJECT_FOR_TREE* m_pPre;   // �O�̍\���̂ւ̃|�C���^
    OBJECT_FOR_TREE* m_pNext;  // ���̍\���̂ւ̃|�C���^

    OBJECT_FOR_TREE() : m_pCell(nullptr), m_pObject(nullptr), m_pPre(nullptr), m_pNext(nullptr) {}
};

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
    std::vector<std::list<OBJECT_FOR_TREE<int>>> nodes_;  // �m�[�h���̃I�u�W�F�N�g���X�g
    int levelDepth_;  // ��ԃ��x���̐[��

    // ��ԃ��x���̐[���ɉ������m�[�h�����v�Z
    int levelOffset(int level) const {
        if (level == 0) return 0;
        return (std::pow(4, level) - 1) / 3;
    }

    // ���x��L�ł̃m�[�h�ԍ�N�ɑΉ�����z��C���f�b�N�X���v�Z
    int getIndex(int level, int nodeNumber) const {
        return levelOffset(level) + nodeNumber;
    }

    // �m�[�h�ɃI�u�W�F�N�g��ǉ�
    void addObjectToNode(int index, OBJECT_FOR_TREE<int>* obj) {
        nodes_[index].push_back(*obj);
        if (!nodes_[index].empty()) {
            obj->m_pPre = &nodes_[index].back(); // ���X�g�̖����ɒǉ�
            if (nodes_[index].size() > 1) {
                obj->m_pPre->m_pNext = obj; // �O�̃I�u�W�F�N�g�̎���ݒ�
            }
        }
    }

    // �m�[�h����I�u�W�F�N�g���폜
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

        // ��ԃ��x���̐[���ɉ������m�[�h�����v�Z
        for (int i = 0; i <= levelDepth_ - 1; ++i) {
            numNodes += int(std::pow(4, i));  // 4^i �̃m�[�h
        }

        // ���`�z��̃T�C�Y��ݒ肵�A�����l�Ƃ��ċ�̃��X�g��ݒ�
        nodes_.resize(numNodes);
    }

    // �I�u�W�F�N�g�̑}��
    void insertSpatialData(const SpatialData& data, OBJECT_FOR_TREE<int>* obj) {
        int index = getIndex(data.level, data.index);
        if (index < nodes_.size()) {
            addObjectToNode(index, obj);
            obj->m_pCell = nullptr;  // ������ (�K�X�ݒ�)
        }
        else {
            std::cerr << "Error: Index out of bounds" << std::endl;
        }
    }

    // �I�u�W�F�N�g�̈ړ�
    void moveObject(int oldLevel, int oldIndex, int newLevel, int newIndex, OBJECT_FOR_TREE<int>* obj) {
        int oldIndexInArray = getIndex(oldLevel, oldIndex);
        int newIndexInArray = getIndex(newLevel, newIndex);

        if (oldIndexInArray < nodes_.size() && newIndexInArray < nodes_.size()) {
            removeObjectFromNode(oldIndexInArray, obj);
            addObjectToNode(newIndexInArray, obj);
            obj->m_pCell = nullptr;  // ������ (�K�X�ݒ�)
        }
        else {
            std::cerr << "Error: Index out of bounds" << std::endl;
        }
    }

    // �I�u�W�F�N�g�̍폜
    void removeObject(int level, int index, OBJECT_FOR_TREE<int>* obj) {
        int indexInArray = getIndex(level, index);
        if (indexInArray < nodes_.size()) {
            removeObjectFromNode(indexInArray, obj);
        }
        else {
            std::cerr << "Error: Index out of bounds" << std::endl;
        }
    }

    // ���`�l���؂̏�Ԃ�\��
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

// �e�X�g�p�R�[�h
int main() {
    LinearQuadtree quadtree(3);  // �[��3�̎l���؂��쐬

    OBJECT_FOR_TREE<int> obj1, obj2, obj3;

    SpatialData data1(1, 2, 10);  // ���x��1�A�C���f�b�N�X2�̃f�[�^
    SpatialData data2(2, 1, 20);  // ���x��2�A�C���f�b�N�X1�̃f�[�^

    obj1.m_pObject = new int(data1.value);
    obj2.m_pObject = new int(data2.value);
    obj3.m_pObject = new int(30);  // �e�X�g�p�̒ǉ��I�u�W�F�N�g

    // �I�u�W�F�N�g�̑}��
    quadtree.insertSpatialData(data1, &obj1);
    quadtree.insertSpatialData(data2, &obj2);
    quadtree.insertSpatialData(SpatialData(1, 2, 30), &obj3);

    // ��ԕ\��
    std::cout << "Initial state:" << std::endl;
    quadtree.printTree();

    // �I�u�W�F�N�g�̈ړ�
    quadtree.moveObject(1, 2, 2, 1, &obj1);

    // ��ԕ\��
    std::cout << "After moving obj1:" << std::endl;
    quadtree.printTree();

    // �I�u�W�F�N�g�̍폜
    quadtree.removeObject(2, 1, &obj2);

    // ��ԕ\��
    std::cout << "After removing obj2:" << std::endl;
    quadtree.printTree();

    // ���������
    delete obj1.m_pObject;
    delete obj2.m_pObject;
    delete obj3.m_pObject;

    return 0;
}
