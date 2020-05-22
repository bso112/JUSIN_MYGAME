#pragma once
#include "Item.h"

BEGIN(MyGame)
class CTexture;
class CSeed abstract : public CItem
{
protected:
	explicit CSeed(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CSeed(CSeed& _rhs);
	virtual ~CSeed() = default;

protected:
	Vector2 m_vOriginalSize;
	//꽃이 되었는가
	_bool	m_bFlower = false;

public:
	virtual HRESULT Initialize(void * _param = nullptr);

protected:
	virtual	void OnThrow();
	virtual HRESULT	Render() override;

protected:
	//필드에 있을때의 사이즈를 가져온다.(자식의 멤버변수를 가져오기위함)
	virtual Vector3 Get_OriginalSize();

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
