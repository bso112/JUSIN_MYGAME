#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CTexture;
class CVIBuffer;
class CTransform;
class CShader;
class CLight final : public CGameObject
{
protected:
	explicit CLight(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CLight(CGameObject& _rhs);
	virtual ~CLight() = default;

private:
	CTexture*	m_pTexture = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
	CTransform*	m_pTransform = nullptr;
	CShader*	m_pShader = nullptr;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _pArg = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();

public:
	HRESULT	Set_Parent(CTransform* _pTransform);

public:
	static CLight* Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath = nullptr);
	virtual CGameObject * Clone(void * _param = nullptr) override;

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;


};
END
