#pragma once

#include "Base.h"

BEGIN(MyGame)
class CGraphic_Device final : public CBase
{
public:
	enum WINMODE { TYPE_FULL, TYPE_WIN, TYPE_END };
public:
	DECLARE_SINGLETON(CGraphic_Device)
private:
	explicit CGraphic_Device();
	virtual ~CGraphic_Device() = default;
public:
	PDIRECT3DDEVICE9 Get_GraphicDevice() { return m_pGraphic_Device; }
	HRESULT Ready_Graphic_Device(HWND hWnd, WINMODE eMode, PDIRECT3DDEVICE9* ppGraphic_Device);
private:
	PDIRECT3D9			m_pSDK = nullptr;
	PDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
public:
	virtual void Free();
};

END
