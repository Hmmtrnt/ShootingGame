#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneFail.h"
#include "SceneTitle.h"

namespace
{
	// 敵のジャンプ力
	constexpr float kJumpEnemy = -15.0f;
	// 敵の重力
	constexpr float kGravity = 1.0f;
}

SceneFail::SceneFail()
{
	m_fieldHandle = 0;	// 背景
	m_enemyHandle = 0;	// 敵
	m_fontHandle = 0;	// 文字
	m_pos.x = 0;		// 表示位置
	m_pos.y = 0;
	m_vec.x = 0;		// 移動速度
	m_vec.y = 0;
	m_size.x = 0;		// サイズ
	m_size.y = 0;
	m_fieldY = 400;		// 地面の高さ
}


void SceneFail::init()
{
	m_enemyHandle = LoadGraph("data/enemy2.png");		// 敵
	m_fieldHandle = LoadGraph("data/field2.jpg");		// 背景
	m_fontHandle = CreateFontToHandle(NULL, 40, 3);		// 文字
	GetGraphSizeF(m_enemyHandle, &m_size.x, &m_size.y);	// 敵のサイズ

	m_pos.x = 80;		// 敵のX座標
	m_pos.y = m_fieldY;	// 敵のY座標
}
// 終了
void SceneFail::end()
{
	// グラフィックメモリの消去
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_fieldHandle);
}
// 毎フレームの処理
SceneBase* SceneFail::update()
{
	m_pos += m_vec;
	// 地面判定
	bool isField = false;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}
	// ジャンプ処理
	if (isField)
	{
		// ジャンプ
		m_vec.y = kJumpEnemy;
	}
	// 重力
	m_vec.y += kGravity;

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		// タイトル
		return (new SceneTitle);
	}
	if (padState & PAD_INPUT_2)
	{
		// メイン
		return (new SceneMain);
	}
	return this;
}

void SceneFail::draw()
{
	// 背景
	DrawGraphF(0, 0, m_fieldHandle, true);
	// テキスト
	DrawFormatString(Game::kScreenWidth / 2 - 120, Game::kScreenHeight / 2 + 120, GetColor(0, 0, 0), "やつ「オレは生き残ったぞ！」");
	DrawStringToHandle(Game::kScreenWidth / 2 - 160, Game::kScreenHeight / 2 - 100, "ＧＡＭＥＯＶＥＲ", GetColor(255, 0, 0), m_fontHandle);
	DrawGraphF(m_pos.x, m_pos.y, m_enemyHandle, true);
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2, "１ボタン:　タイトル画面", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2 + 20, "２ボタン:リスタート画面", GetColor(0, 0, 0));
}