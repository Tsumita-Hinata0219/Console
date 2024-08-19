#include <stdio.h>
#include <iostream>
#include <type_traits>
#include <vector>
#include <bitset>
#include <string>


static uint32_t BitSeparate32(uint32_t n)
{
	n = (n | (n << 8)) & 0x00ff00ff;
	n = (n | (n << 4)) & 0x0f0f0f0f;
	n = (n | (n << 2)) & 0x33333333;
	return (n | (n << 1)) & 0x55555555;
}
static uint32_t Get2DMortonNumber(uint32_t x, uint32_t y)
{
	return (BitSeparate32(x) | (BitSeparate32(y) << 1));
}
// �r�b�g�񂩂�ŏ�ʃr�b�g�̈ʒu���擾����֐�
static int findHighestBitPosition(int bitmask) {
	int position = 0;
	while (bitmask != 0) {
		bitmask >>= 1;
		++position;
	}
	return position;
}


int continueLoop = 1;

int main(void) {

	// ���[�g��Ԃ̕�
	int ROOT_EDGE_LENGTH = 100;
	// ����Ԃ̈��
	float U = float(ROOT_EDGE_LENGTH / std::pow(2, 3));

	// �o��
	std::cout << "���[�g��Ԃ̈�� : " << ROOT_EDGE_LENGTH << std::endl;
	std::cout << "����Ԃ̈�Ӂ@�@ : " << U << std::endl;


	// ���[�v����
	while (continueLoop == 1) {
		std::cout << std::endl << std::endl << std::endl << std::endl; // ���s

		// ������Ԃ���ԃ��x�������߂�
		int number;
		std::cout << "������� -> 1  ��ԃ��x�� -> 2 " << std::endl;
		std::cout << "Enter a number : ";
		std::cin >> number;
		std::cout << std::endl << std::endl << std::endl;

		if (number == 1) {

			std::cout << "/* ========== ���W���珊����Ԃ����߂� ========== */" << std::endl << std::endl;

			// ���W���珊����Ԃ����߂�
			std::cout << "���W����͂��Ă��������B0 ~ 100" << std::endl;

			// �_�̍��W�̓��͂��󂯕t����
			int pos_x = 0, pos_y = 0;
			std::cout << "  X���W : ";
			std::cin >> pos_x;
			std::cout << "  Y���W : ";
			std::cin >> pos_y;
			// ���͂��ꂽ���W��\������
			std::cout << "���͂��ꂽ���W : (" << pos_x << ", " << pos_y << ")" << std::endl;
			std::cout << std::endl;


			// ���W��U(����Ԃ̈��)�Ŋ���������
			float x_div_u = float(pos_x / U);
			float y_div_u = float(pos_y / U);
			// int�^�ŃL���X�g
			int x_casted = static_cast<int>(x_div_u);
			int y_casted = static_cast<int>(y_div_u);
			// �L���X�g�������̂�bit�ŕ\��������
			std::bitset<4> x_bit(x_casted);
			std::bitset<4> y_bit(y_casted);
			// �������
			int spaceID = Get2DMortonNumber(x_casted, y_casted);

			// �o��
			std::cout << "U(����Ԃ̈��)�ŏ��Z�@�@ : (" << x_div_u << ", " << y_div_u << ")" << std::endl;
			std::cout << "int�^�ŃL���X�g�@�@�@�@�@ : (" << x_casted << ", " << y_casted << ")" << std::endl;
			std::cout << "�L���X�g�������̂�bit�\�� : (" << x_bit << ", " << y_bit << ")" << std::endl;
			std::cout << std::endl;
			std::cout << "������� : " << spaceID << std::endl;
			std::cout << std::endl;
			std::cout << "/* ========== ���������������������������������������� ========== */" << std::endl << std::endl;

			std::cout << std::endl << std::endl << std::endl << std::endl;
		}
		else if (number == 2) {

			std::cout << "/* ========== ������Ԃ����ԃ��x�������߂� ========== */" << std::endl << std::endl;

			// ������Ԃ����ԃ��x�������߂�
			std::cout << "������Ԃ���͂��Ă��������B0 ~ 63" << std::endl;

			// ������Ԃ̓��͂��󂯕t����
			int LT = 0, RD = 0;
			std::cout << "  ���� : ";
			std::cin >> LT;
			std::cout << "  �E�� : ";
			std::cin >> RD;
			// ���͂��ꂽ������Ԃ�\������
			std::cout << "���͂��ꂽ������� : (" << LT << ", " << RD << ")" << std::endl;
			std::cout << std::endl;


			// ������ԃ��x��
			int LTxorRD = LT ^ RD;
			// �ŏ�ʃr�b�g�ʒu�����߂�
			int highestBitPosition = findHighestBitPosition(LTxorRD);
			// �ǂ̋�Ԃ̂ǂ̔ԍ��ɏ������Ă��邩
			int spaceIndex = LT >> highestBitPosition;

			// �o��
			std::cout << "XOR              : " << LTxorRD << std::endl;
			std::cout << "��ԃ��x��       : " << std::bitset<6>(LTxorRD) << std::endl;
			std::cout << "�ŏ�ʃr�b�g�ʒu : " << highestBitPosition << std::endl;
			std::cout << "�������Bit      : " << std::bitset<6>(spaceIndex) << std::endl;
			std::cout << "�������         : " << spaceIndex << std::endl;
			std::cout << std::endl;
			std::cout << "/* ========== �������������������������������������������������� ========== */" << std::endl << std::endl;
			std::cout << std::endl << std::endl << std::endl << std::endl;
		}

		std::cout << "������񋁂߂܂����H 1: ������  2: �I��" << std::endl;
		std::cout << "Enter a number : ";
		std::cin >> continueLoop;
	}



	return 0;
}