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
		//ĳ���� ���ݿ� ������ �ִ� ����
		STATS	m_tStats = {};
		//���� ��
		_int	m_iDuration = 1;
		TYPE	m_eType = TYPE_END;

	}STATEDESC;

protected:
	explicit CBuff() {};
	virtual ~CBuff() = default;

protected:
	STATEDESC	m_tStateDesc;
	//������ �� ��
	_int		m_iTurnCnt = 0;

public:
	virtual	HRESULT	Initialize(void* _pArg);
	//���� �� ���� �����Ѵ�.
	virtual _int	Act(CCharacter* _pTarget);
	//������ ������.
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
