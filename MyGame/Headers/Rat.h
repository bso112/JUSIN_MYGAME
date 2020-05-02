#pragma once
#include "Monster.h"

BEGIN(MyGame)
class CTexture;
class CRat final : public CMonster
{
public:
	enum ANIM { ANIM_IDLE, ANIM_ATTACK, ANIM_JUMP, ANIM_DEAD, ANIM_END };
private:
	explicit CRat(PDIRECT3DDEVICE9 _pGraphic_Device) :CMonster(_pGraphic_Device) {};
	explicit CRat(CRat& _rhs);
	virtual ~CRat() = default;
	
private:
	CTexture*	m_pTexture[ANIM_END];
	ANIM		m_eCurrAnim = ANIM_IDLE;


public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();

public:
	static CRat* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CMonster��(��) ���� ��ӵ�
	virtual CGameObject * Clone(void * _param = nullptr) override;

private:
	virtual void Process() override;
	virtual void Update_State() override;
	virtual void OnDead() override;
	virtual void OnTakeDamage() override;
	virtual void Scene_Change() override;


public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
