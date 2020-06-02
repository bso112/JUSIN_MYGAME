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
class CImage;
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

	//����
	enum IMMUNE {IMMUNE_FIRE, IMMUNE_ICE, IMMUNE_END};

protected:
	//���
	CTransform*	m_pTransform = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
	CShader*	m_pShader = nullptr;
	//���̴����� �� pass
	_uint		m_iPass = 0;


	//��Ŀ���ϰ� �ִ� ���
	CCharacter*	m_pFocus = nullptr;
	//���¸ӽ�
	CStateCon*	m_pStateCon = nullptr;
	//�����Ŵ���
	CBuffController*	m_pBuffCon = nullptr;


	//���� Ȱ��ȭ�� ����Ʈ
	CEffect*	m_pEffect = nullptr;

	CClock_Delay*	m_pDeadClock = nullptr;
	
protected:
	STATS	m_tStat = {};
	vector<IMMUNE> m_vecImmune;
	
	_bool	m_bInvisible = false;
	//�̵��� ��ǥ����
	Vector4			m_vDst = {};

	//���ݹ���
	_uint	m_iAttackRange = 0;
	//�νĹ���
	_uint	m_iRecogRange = 0;

	const _tchar* m_pName = L"";
	
public:
	_int		StartAct() override;
	_int		UpdateAct() override;
	CCharacter*	Get_Focus() { return m_pFocus; }
	//�� ���¸� �����´�.
	void		SetTurnState(_bool _bTurnEnd) override { m_bTurnEnd = _bTurnEnd; }
	void		PlayEffect(CEffect* _pEffect);
	//ĳ���� ���� �ؽ�Ʈ�� ����.
	HRESULT		ShowText(const _tchar* _pText);
	//ĳ���� ���� �̹����� ����.
	HRESULT		ShowBuffImg(CImage* _pImage);

public:
	virtual void TakeDamage(float _fDamage);
	void	Heal(_float _healAmount);
	void	SetInvisible(bool _bInvisible) { m_bInvisible = _bInvisible; }
	void	Set_Paralyze(bool _bParalyze) { m_bParalyze = _bParalyze; }
	_bool	IsTurnEnd()		override { return m_bTurnEnd; }
	_bool	IsParalyzed()	override { return m_bParalyze; }
	_bool	IsAlive();
	_bool	IsImmune(IMMUNE _eImmune);
	const _tchar*	Get_Name() { return m_pName; }
	void	Add_Buff(CBuff* pBuff);

public:
	virtual	_int	Interact(CGameObject* _pOther);

public:
	//��� ������ ����ִ��� �ε����� �����Ѵ�.
	HRESULT	Get_TerrainIndex(pair<_int, _int>& _out);
	//Ÿ���� �� ��ü�� �߽����� �ش� ������ �ִ°�?
	bool	IsTargetInRange(CCharacter* pTarget, _int _iRange);
	const STATS&	Get_Stat() { return m_tStat; }
	_bool	Get_Dying() { return m_bDying; }
public:
	virtual void OnCollisionEnter(CGameObject* _pOther);

protected:
	virtual void OnTakeDamage();
	virtual	void OnAttack(CGameObject * _pOther);


public:
	virtual void Free() override;
};

END