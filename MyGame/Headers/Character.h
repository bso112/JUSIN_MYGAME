#pragma once
#include "Actor.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "Animator.h"
#include "Stat.h"
#include "Effect.h"
BEGIN(MyGame)
class CStat;
class CClock_Delay;
class CStateCon;
class CShader;
class CBuffController;
class CBuff;
class CCharacter abstract : public CGameObject
{
protected:
	explicit CCharacter(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CCharacter(CCharacter& _character);
	virtual ~CCharacter() = default;

public:
	typedef struct tagStats
	{
		float	m_fHP		= 0.f;
		CStat*	m_fMaxHp	= nullptr;

		CStat*	m_fArmor	= nullptr;
		CStat*	m_fAtt		= nullptr;
		int		m_iGold		= 0;
		float	m_fExp		= 0.f;
		float	m_fMaxExp	= 0.f;

		void Free()
		{
			Safe_Release(m_fMaxHp);
			Safe_Release(m_fArmor);
			Safe_Release(m_fAtt);
		}
	}STATS;

	//저항
	enum IMMUNE {IMMUNE_FIRE, IMMUNE_ICE, IMMUNE_END};

protected:
	//모듈
	CTransform*	m_pTransform = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
	CShader*	m_pShader = nullptr;
	//쉐이더에서 쓸 pass
	_uint		m_iPass = 0;


	//포커스하고 있는 대상
	CCharacter*	m_pFocus = nullptr;
	//상태머신
	CStateCon*	m_pStateCon = nullptr;
	//버프매니저
	CBuffController*	m_pBuffCon = nullptr;
	//턴이 끝났는지
	bool		m_bTurnEnd = false;

	//현재 활성화된 이펙트
	CEffect*	m_pEffect = nullptr;

	CClock_Delay*	m_pDeadClock = nullptr;

protected:
	STATS	m_tStat = {};
	vector<IMMUNE> m_vecImmune;
	
	_bool	m_bInvisible = false;
	_bool	m_bParalyze = false;
	//이동할 목표지점
	Vector4			m_vDst = {};

	//공격범위
	_uint	m_iAttackRange = 0;
	//인식범위
	_uint	m_iRecogRange = 0;

	const _tchar* m_pName = L"";


public:
	_int		StartAct();
	_int		UpdateAct();
	CCharacter*	Get_Focus() { return m_pFocus; }
	_bool		IsTurnEnd(){ return m_bTurnEnd; }
	//턴 상태를 가져온다.
	void		SetTurnState(_bool _bTurnEnd) { m_bTurnEnd = _bTurnEnd; }
	void		PlayEffect(CEffect* _pEffect);

public:
	virtual void TakeDamage(float _fDamage);
	void	Heal(_float _healAmount);
	void	SetInvisible(bool _bInvisible) { m_bInvisible = _bInvisible; }
	void	Set_Paralyze(bool _bParalyze) { m_bParalyze = _bParalyze; }
	_bool	IsParalyzed() { return m_bParalyze; }
	_bool	IsAlive();
	_bool	IsImmune(IMMUNE _eImmune);
	const _tchar*	Get_Name() { return m_pName; }
	void	Add_Buff(CBuff* pBuff);

public:
	virtual	_int	Interact(CGameObject* _pOther);

public:
	//어느 지형을 밟고있는지 인덱스를 리턴한다.
	HRESULT	Get_TerrainIndex(pair<_int, _int>& _out);
	//타겟이 이 객체를 중심으로 해당 범위에 있는가?
	bool	IsTargetInRange(CCharacter* pTarget, _int _iRange);
	const STATS&	Get_Stat() { return m_tStat; }

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);

protected:
	virtual void OnDead();
	virtual void OnTakeDamage();
	virtual	void OnAttack(CGameObject * _pOther);


public:
	virtual void Free() override;
};

END