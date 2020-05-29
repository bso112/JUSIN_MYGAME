#pragma once
#include "Base.h"

BEGIN(MyGame)
class CTarget : public CBase
{
protected:
	explicit CTarget(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CTarget() = default;

private:
	PDIRECT3DDEVICE9			m_pGraphic_Device;
	LPDIRECT3DTEXTURE9			m_pTexture = nullptr;
	LPDIRECT3DSURFACE9			m_pOldSurface = nullptr;
	LPDIRECT3DSURFACE9			m_pSurface = nullptr;
	_uint						m_iRenderTargetIndex = 0;
public:
	HRESULT	Initialize(_int iCX, _int iCY, D3DFORMAT _eFormat);
	HRESULT	Set_RenderTarget(_uint _iIndex);
	HRESULT	Release_RederTarget();
	HRESULT	Clear_RenderTarget();

public:
	LPDIRECT3DTEXTURE9 Get_Texture() { return m_pTexture; }
	
public:
	static	CTarget* Create(PDIRECT3DDEVICE9 _pGraphic_Device, _int iCX, _int iCY, D3DFORMAT _eFormat);
	void	Free() override;


};
END
