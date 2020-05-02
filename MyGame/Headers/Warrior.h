#pragma once
#include "Hero.h"

BEGIN(MyGame)
class CTexture;
class CWarrior final : public CHero
{
private:
	explicit CWarrior(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CWarrior(CWarrior& _hero);
	virtual ~CWarrior() = default;

private:
	CTexture*	m_pTexture[CLOTH_END][ANIM_END];
	CLOTH		m_eCurrCloth = CLOTH_BASIC;
	ANIM		m_eCurrAnim = ANIM_IDLE;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr) override;
	virtual HRESULT Initialize(void * _param = nullptr) override;
	virtual _int	Update(_double _timeDelta) override;
	virtual _int	LateUpate(_double _timeDelta) override;
	virtual HRESULT	Render() override;
	virtual	HRESULT KeyCheck(_double _timeDelta) override;

public:
	void Set_Destination(Vector4 _vDst) { m_vDst = _vDst; }

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);

private:
	virtual void Scene_Change() override;
	virtual void Process() override;
	virtual void Update_State() override;
	virtual void OnDead() override;
	virtual void OnTakeDamage() override;

public:
	static CWarrior* Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath = nullptr);
	virtual CGameObject * Clone(void * _param = nullptr) override;

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;





};
END
