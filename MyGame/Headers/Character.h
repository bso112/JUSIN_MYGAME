#pragma once
#include "Actor.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "Animator.h"
#include "Stat.h"
BEGIN(MyGame)
class CStat;
class CClock_Single;
class CStateCon;
class CShader;
class CCharacter abstract : public CGameObject
{
protected:
	explicit CCharacter(PDIRECT3DDEVICE9 _pGraphic_Device) :CGameObject(_pGraphic_Device){};
	explicit CCharacter(CCharacter& _character);
	virtual ~CCharacter() = default;

protected:
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

	//����
	enum IMMUNE {IMMUNE_FIRE, IMMUNE_ICE, IMMUNE_END};

protected:
	CTransform*	m_pTransform = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
	CShader*	m_pShader = nullptr;
	//���̴����� �� pass
	_uint		m_iPass = 0;


	//��Ŀ���ϰ� �ִ� ���
	CCharacter*	m_pFocus = nullptr;
	//���¸ӽ�
	CStateCon*	m_pStateCon = nullptr;
	bool		m_bTurnEnd = false;


public:
	_int		StartAct();
	_int		UpdateAct();
	CCharacter*	Get_Focus() { return m_pFocus; }
	_bool		IsTurnEnd(){ return m_bTurnEnd; }
	void		SetTurnState(_bool _bTurnEnd) { m_bTurnEnd = _bTurnEnd; }

protected:
	_int	m_iCurFrame = 0;
	STATS	m_tStat = {};
	vector<IMMUNE> m_vecImmune;
	
	bool	m_bDead = false;
	bool	m_bInvisible = false;
	//�̵��� ��ǥ����
	Vector4			m_vDst = {};

	//���ݹ���
	_uint	m_iAttackRange = 0;
	//�νĹ���
	_uint	m_iRecogRange = 0;

public:
	virtual void TakeDamage(float _fDamage);
	void Heal(_float _healAmount);
	void SetInvisible(bool _bInvisible) { m_bInvisible = _bInvisible; }
	bool IsAlive();
	bool IsImmune(IMMUNE _eImmune);
	
public:
	//��� ������ ����ִ��� �ε����� �����Ѵ�.
	HRESULT	Get_TerrainIndex(pair<_int, _int>& _out);
	//Ÿ���� �� ��ü�� �߽����� �ش� ������ �ִ°�?
	bool	IsTargetInRange(CCharacter* pTarget, _int _iRange);
	const STATS&	Get_Stat() { return m_tStat; }

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);

protected:
	virtual void OnDead();
	virtual void OnTakeDamage();


public:
	virtual void Free() override;
};

END