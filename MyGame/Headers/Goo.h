#pragma once
#include "Monster.h"

BEGIN(MyGame)
class CTexture;
class CAIStateCon;
class CGoo final : public CMonster
{
private:
	explicit CGoo(PDIRECT3DDEVICE9 _pGraphic_Device) :CMonster(_pGraphic_Device) {};
	explicit CGoo(CGoo& _rhs);
	virtual ~CGoo() = default;


private:
	//공격받은 수
	_int	m_iHitCnt = 0;
	_bool	m_bRage = false;
	_int	m_iRageCnt = 0;
public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);

public:
	static CGoo* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CMonster을(를) 통해 상속됨
	virtual CGameObject * Clone(void * _param = nullptr) override;

	
public:
	void OnDead() override;
	virtual void OnTakeDamage(float _fDamage) override;
	void OnAct() override;
	void OnAttack(CGameObject* _pObj) override;
public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
