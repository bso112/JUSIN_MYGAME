#pragma once
#include "Item.h"
BEGIN(MyGame)
class CTransform;
class CVIBuffer;
class CTexture;
class CShader;
//생각해보니까 모든 아이템은 던질 수 있잖아>>??`	
class CProjectile abstract : public CItem 
{

private:
	explicit CProjectile(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CProjectile(CProjectile& _rhs);
	virtual ~CProjectile() = default;

protected:
	BASEDESC	m_tDesc;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual _int	Update(_double _timeDelta) override;
	virtual _int	LateUpate(_double _timeDelta) override;
	virtual HRESULT	Render() override;

public:
	virtual HRESULT	Use(CHero* _pHero, const _tchar* _pAction) override;

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);

public:
	virtual	void Free() override;


};
END
