#pragma once

// �R���g���[���[����̓��͏�Ԏ擾
namespace Pad
{
	// �p�b�h�̓��͏�Ԏ擾
	void update();
	// ������������
	bool isPress(int button);
	// �g���K�[����
	bool isTrigger(int button);
	// ����������
	bool isRelase(int button);
}