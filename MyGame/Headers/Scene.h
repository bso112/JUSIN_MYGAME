#pragma once
#include "Base.h"
#include "ObjMgr.h"

BEGIN(MyGame)
class CRenderer;

class CScene abstract: public CBase
{
protected:
	explicit CScene(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CScene() = default;

protected:
	PDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	CRenderer*			m_pRenderer = nullptr;
	CObjMgr*			m_pObjMgr = nullptr;

public:
	virtual HRESULT Initalize();
	virtual _int	Update(_double _timeDelta);
	virtual HRESULT	Render();
	virtual	HRESULT	Render(HDC _DC);



protected:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};

END