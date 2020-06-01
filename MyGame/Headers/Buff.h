#pragma once
#include "Base.h"
#include "Stat.h"
BEGIN(MyGame)
class CCharacter;
class CBuff abstract : public CBase
{
public:
	enum TYPE
	{
		TYPE_POISION,
		TYPE_BURN,
		TYPE_FREEZE,
		TYPE_PARALIZE,
		TYPE_END
	};
public:
	typedef struct tagStats
	{
		float	m_fHP = 0.f;
		float	m_fArmor = 0.f;
		CStat*	m_fAtt = nullptr;

		void Free()
		{
			Safe_Release(m_fAtt);
		}

	}STATS;
	typedef struct tagStateDesc
	{
		//캐릭터 스텟에 영향을 주는 값들
		STATS	m_tStats = {};
		//지속 턴
		_int	m_iDuration = 1;
		TYPE	m_eType = TYPE_END;

	}STATEDESC;

protected:
	explicit CBuff() {};
	virtual ~CBuff() = default;

protected:
	STATEDESC	m_tStateDesc;
	//진행한 턴 수
	_int		m_iTurnCnt = 0;

public:
	virtual	HRESULT	Initialize(void* _pArg);
	//남은 턴 수를 리턴한다.
	virtual _int	Act(CCharacter* _pTarget);
	//버프를 끝낸다.
	virtual	HRESULT	End_Buff();

public:
	TYPE	Get_Type() { return m_tStateDesc.m_eType; }

protected:
	virtual void	OnAct(CCharacter* _pTarget) = 0;
public:
	_int	Get_Durarion() { return m_tStateDesc.m_iDuration; }
	void	Set_Duration(_int _iDuration) { m_tStateDesc.m_iDuration = _iDuration; }


public:
	virtual void Free();
};
END
