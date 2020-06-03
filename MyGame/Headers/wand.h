#pragma once
#include "Item.h"
BEGIN(MyGame)
class CWand final : public CItem
{
public:
	enum TYPE {TYPE_IGHTING, TYPE_END};
protected:
	explicit CWand(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CWand(CWand& _rhs);
	virtual ~CWand() = default;

public:
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT	Use(CHero* _pHero, const _tchar** _pAction) override;
public:
	HRESULT	Zap(TYPE _eType, Vector2 _vOrigin, POINT _pt);

private:
	HRESULT Zap_Lighting(Vector2 _vOrigin, POINT _pt);


public:
	static CWand * Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr);
	CGameObject * Clone(void * _param = nullptr);
	virtual void Free() override;

	// CItem을(를) 통해 상속됨
	virtual Vector3 Get_OriginalSize() override;
};

END