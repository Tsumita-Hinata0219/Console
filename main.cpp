#include <iostream>
#include <vector>
using namespace std;
int main(void) {

	// ���z�A�|�C���g�A��ԉ�
	int amount = 0, point = 0, takeCount = 0;
	
	// �������z�Ə�ԉ񐔂̓���
	cin >> amount; cin >> takeCount;

	// �^��
	vector<int> fares(takeCount);
	for (auto& fare : fares) {
		cin >> fare;
	}

	// �v�Z
	for (auto& fare : fares) {

		// �^���̂ق���������΋��z�Ŏx����
		if (point <= fare) {
			amount -= fare;
			point += int(float(fare) * 0.1f); // �^����10%�����Z
		}
		else { // �|�C���g�̂ق���������΃|�C���g�Ŏx����
			point -= fare;
		}
		// ���݂̋��z�ƃ|�C���g�̏o��
		cout << amount << " " << point << endl;
	}

	return 0;
}