#pragma once
#include "SceneBase.h"

class SceneFail : public SceneBase
{
public:
	SceneFail()
	{
		m_isEnd = false;
	}
	virtual ~SceneFail() {}

	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	bool m_isEnd;
};