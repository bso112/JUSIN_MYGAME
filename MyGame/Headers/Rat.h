#pragma once
#include "Monster.h"

BEGIN(MyGame)
class CTexture;
class CRat final : public CMonster
{
private:
	explicit CRat(PDIRECT3DDEVICE9 _pGraphic_Device) :CMonster(_pGraphic_Device) {};
	explicit CRat(CRat& _rhs);
	virtual ~CRat() = default;
	
private:
	CAnimator*	m_pAnimator = nullptr;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT Act(_int _iTurnCnt) override;
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();

public:
	static CRat* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CMonster을(를) 통해 상속됨
	virtual CGameObject * Clone(void * _param = nullptr) override;

private:
	virtual void Process() override;
	virtual void Update_State() override;
	virtual void OnDead() override;
	virtual void OnTakeDamage() override;
	virtual void Scene_Change() override;


public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
