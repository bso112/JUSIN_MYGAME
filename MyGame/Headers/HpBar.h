#pragma once
#include "Image.h"
BEGIN(MyGame)
class CCharacter;
class CHpBar :public CImage
{
protected:
	explicit CHpBar(PDIRECT3DDEVICE9 _pGraphic_Device) : CImage(_pGraphic_Device) { m_pOwner = nullptr; };
	explicit CHpBar(CHpBar& _rhs) : CImage(_rhs) { m_pOwner = nullptr; };
	virtual ~CHpBar() = default;

private:
	CCharacter* m_pOwner = nullptr;

public:
	virtual HRESULT Render() override;
public:
	void	Set_Owner(CCharacter* _pOwner) { m_pOwner = _pOwner; Safe_AddRef(_pOwner); }

public:
	static CHpBar* Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, const _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	static CHpBar* Create(PDIRECT3DDEVICE9 _pGraphic_Device, void* _desc);
	virtual	CGameObject* Clone(void* _param = nullptr)override;
	virtual void Free() override;

};

END