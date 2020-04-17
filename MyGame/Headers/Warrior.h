#pragma once
#include "Hero.h"

BEGIN(MyGame)
class CWarrior final : public CHero
{
private:
	explicit CWarrior(PDIRECT3DDEVICE9 _pGraphic_Device) : CHero(_pGraphic_Device) {};
	explicit CWarrior(CWarrior& _hero) : CHero(_hero) {}
	virtual ~CWarrior() = default;

public:
	static CWarrior* Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath = nullptr);
	virtual CGameObject * Clone(void * _param = nullptr) override;


public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr) override;
	virtual HRESULT Initialize(void * _param = nullptr) override;
	virtual _int	Update(_double _timeDelta) override;
	virtual _int	LateUpate(_double _timeDelta) override;
	virtual HRESULT	Render() override;
	virtual	HRESULT KeyCheck() override;


public:
	void Set_Destination(Vector2 _vDst) { m_vDst = _vDst; }


private:
	virtual void Scene_Change() override;
	virtual void Process() override;
	virtual void Update_State() override;
	virtual void OnDead() override;
	virtual void OnTakeDamage() override;





};
END
