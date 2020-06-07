#pragma once
#include "Actor.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "Animator.h"
#include "Stat.h"
#include "Effect.h"
#include "Image.h"
#include "Buff.h"
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
		float	m_fAvoidability = 25.f;

		void Free()
		{
			Safe_Release(m_fMaxHp);
			Safe_Release(m_fArmor);
			Safe_Release(m_fAtt);
		}
	}STATS;


protected:
	//모듈
	CTransform*	m_pTransform = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
	CShader*	m_pShader = nullptr;
	//쉐이더에서 쓸 pass
	_uint		m_iPass = 0;
	_bool		m_bNPC = false;

	//포커스하고 있는 대상
	CCharacter*	m_pFocus = nullptr;
	//상태머신
	CStateCon*	m_pStateCon = nullptr;
	//버프매니저
	CBuffController*	m_pBuffCon = nullptr;

	CClock_Delay*	m_pDeadClock = nullptr;

	_bool			m_bInvincible = false;
	
protected:
	STATS	m_tStat = {};
	list<CBuff::TYPE> m_listImmune;
	
	_bool	m_bInvisible = false;
	//이동할 목표지점
	Vector4			m_vDst = {};

	//공격범위
	_uint	m_iAttackRange = 0;
	//인식범위
	_uint	m_iRecogRange = 0;

	const _tchar* m_pName = L"";

	
public:
	_int		StartAct() override;
	_int		UpdateAct() override;
	CCharacter*	Get_Focus() { return m_pFocus; }
	//턴 상태를 가져온다.
	void		SetTurnState(_bool _bTurnEnd) override { m_bTurnEnd = _bTurnEnd; }
	//캐릭터 위로 텍스트를 띄운다.
	HRESULT		ShowText(const _tchar* _pText, D3DXCOLOR _Color = 0xFFF6F258, ID3DXFont* _pFont = g_pFontX2);
	//캐릭터 위로 이미지를 띄운다.
	HRESULT		ShowBuffImg(CImage* _pImage);
	HRESULT		ShowBuffImg(SCENEID _eTextureSceneID, const _tchar* _pTextureTag, _uint _iTextureID, BASEDESC _tBaseDesc);
	HRESULT		ShowStateIcon(SCENEID _eTextureSceneID, const _tchar* _pTextureTag, _uint _iTextureID, BASEDESC _tBaseDesc);


public:
	virtual _bool TakeDamage(float _fDamage, _bool _bDodgable = false);
	HRESULT	Attack(CCharacter* _pOther);
	void	Heal(_float _healAmount);
	void	SetInvisible(bool _bInvisible) { m_bInvisible = _bInvisible; }
	void	Set_Paralyze(bool _bParalyze);
	_bool	IsTurnEnd()		override { return m_bTurnEnd; }
	_bool	IsParalyzed()	override { return m_bParalyze; }
	_bool	IsAlive();
	_bool	IsImmune(CBuff::TYPE _eType);
	const _tchar*	Get_Name() { return m_pName; }
	void	Add_Buff(CBuff* pBuff);
	HRESULT	Add_Immune(CBuff::TYPE _eType);
public:
	virtual	_int	Interact(CGameObject* _pOther);

public:
	//어느 지형을 밟고있는지 인덱스를 리턴한다.
	HRESULT	Get_TerrainIndex(pair<_int, _int>& _out);
	//타겟이 이 객체를 중심으로 해당 범위에 있는가?
	bool	IsTargetInRange(CCharacter* pTarget, _int _iRange);
	const STATS&	Get_Stat() { return m_tStat; }
	_bool	Get_Dying() { return m_bDying; }
	_bool	Is_NPC() { return m_bNPC; }
public:
	virtual void OnCollisionEnter(CGameObject* _pOther);

protected:
	virtual void OnTakeDamage(float _fDamage);
	virtual	void OnAttack(CGameObject * _pOther);


public:
	virtual void Free() override;
};

END