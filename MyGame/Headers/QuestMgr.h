#pragma once
#include "Base.h"

BEGIN(MyGame)
class CHero;
class CItem;
class CQuestMgr : public CBase
{
	DECLARE_SINGLETON(CQuestMgr)
private:
	explicit CQuestMgr() {};
	virtual ~CQuestMgr() = default;

private:
	_bool	m_bQuestStart = false;
	_bool	m_bQuestEnd = false;

public:
	void	SetQuestStart() { m_bQuestStart = true; }
	void	SetQuestEnd() { m_bQuestEnd = true; }
	_bool	IsQuestStart() { return m_bQuestStart; }
	_bool	IsQuestEnd() { return m_bQuestEnd; }
	HRESULT	Reward(vector<CItem*>* _pItem);
	

	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
