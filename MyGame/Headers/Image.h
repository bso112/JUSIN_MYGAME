#pragma once

#include "GameObject.h"
BEGIN(MyGame)

class CVIBuffer;
class CTexture;
class CTransform;
class CImage final : public CGameObject
{
private:
	explicit CImage(PDIRECT3DDEVICE9 _pGraphic_Device) : CGameObject(_pGraphic_Device) {}
	explicit CImage(CImage& _rhs);
	virtual ~CImage() = default;

private:
	CVIBuffer*	m_pVIBuffer = nullptr;
	CTexture*	m_pTextrue = nullptr;
	CTransform*	m_pTransform = nullptr;


public:
	virtual HRESULT Initialize(_tchar* _pTextureTag, Vector4 _vPos, Vector2 _vSize);
	virtual _int Update(_double _timeDelta) override;
	virtual _int LateUpate(_double _timeDelta) override;
	virtual HRESULT Render() override;

public:
	static CImage* Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag);
	virtual	CGameObject* Clone(void* _param = nullptr)override;
	virtual void Free() override;

};
END
