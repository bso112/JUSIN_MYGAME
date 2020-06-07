#pragma once
#include "Image.h"
BEGIN(MyGame)
class CCharacter;
class CHpBar :public CImage
{
protected:
	explicit CHpBar(PDIRECT3DDEVICE9 _pGraphic_Device) : CImage(_pGraphic_Device) { };
	explicit CHpBar(CHpBar& _rhs) : CImage(_rhs) {};
	virtual ~CHpBar() = default;

private:
	_float m_fMaxHp = 0.f;
	_float m_fHp = 0.f;

public:
	virtual HRESULT Render() override;
public:
	void	Set_State(_float _fMaxHp, _float _fHp) { m_fMaxHp = _fMaxHp; m_fHp = _fHp; }

public:
	static CHpBar* Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, const _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	static CHpBar* Create(PDIRECT3DDEVICE9 _pGraphic_Device, void* _desc);
	virtual	CGameObject* Clone(void* _param = nullptr)override;
	virtual void Free() override;

};

END