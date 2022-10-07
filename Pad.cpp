#include "DxLib.h"
#include "Pad.h"

namespace
{
	constexpr int kLogNum = 16;
	// 入力ログ 0が最新の状態
	int padLog[kLogNum];
}

namespace Pad
{
	// パッドの入力状態取得
	void update()
	{
		// 現在のパッドの状態を取得
		int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		// ログの更新
		for (int i = kLogNum - 1; i >= 1; i--)
		{
			padLog[i] = padLog[i - 1];
		}
		// 最新の状態
		padLog[0] = padState;
	}

	bool isPress(int button)
	{
		return (padLog[0] & button);
	}

	bool isTrigger(int button)
	{
		bool isNow = (padLog[0] & button);	// 現在の状態
		bool isLast = (padLog[1] & button);	// １フレーム前の状態
		return (isNow && !isLast);
	}

	bool isRelase(int button)
	{
		bool isNow = (padLog[0] & button);	// 現在の状態
		bool isLast = (padLog[1] & button);	// １フレーム前の状態
		return (!isNow && isLast);
	}
}