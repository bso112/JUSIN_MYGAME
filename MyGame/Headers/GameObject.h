#pragma once
#include "Base.h"
#include "Renderer.h"

BEGIN(MyGame)

class CRenderer;

class CGameObject abstract : public CBase
{
protected:
	explicit CGameObject(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CGameObject(CGameObject& _rhs);
	virtual ~CGameObject() = default;

protected:
	CRenderer* m_pRenderer = nullptr;
	PDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initalize(void * _param = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();
	virtual CGameObject* Clone(void * _param = nullptr) = 0;


	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};

END