#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CTransform;
class CTexture;
class CVIBuffer;
class CTerrain final : public CGameObject
{
private:
	explicit CTerrain() {};
	explicit CTerrain(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CTerrain(CTerrain& _rhs);
	virtual ~CTerrain() = default;

private:
	CTransform*	m_pTransform = nullptr;
	CTexture*	m_pTexture = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
	TERRAIN		m_tData = {};


public:
	virtual HRESULT	Initialize_Prototype(TERRAIN _tData, const _tchar* _pTextureTag, _tchar* _pFilePath = nullptr);
	virtual HRESULT	Render();

	
public:
	static CTerrain*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, _tchar* _pFilePath = nullptr);
	virtual CGameObject* Clone(void * _param = nullptr);
	virtual void Free() override;

private:
	HRESULT	Initalize_Module();

};
END
