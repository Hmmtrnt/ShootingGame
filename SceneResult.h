#pragma once
#include "SceneBase.h"

class SceneResult : public SceneBase
{
public:
	SceneResult()
	{
		m_isEnd = false;
	}
	virtual ~SceneResult() {}

	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	bool m_isEnd;
};