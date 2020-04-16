#pragma once
#include "Base.h"
#include "Renderer.h"

BEGIN(MyGame)

class CRenderer;

class CGameObject abstract : public CBase
{
protected:
	explicit CGameObject() {};
	explicit CGameObject(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CGameObject(CGameObject& _rhs);
	virtual ~CGameObject() = default;

protected:
	CRenderer*			m_pRenderer = nullptr;
	PDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	INFO				m_tInfo = {};
	RECT				m_tRect = {};
public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();
	virtual HRESULT	Render(HDC _DC);
	virtual CGameObject* Clone(void * _param = nullptr) = 0;

protected:
	void Update_Rect();

	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};

END