#pragma once
#include "Item.h"

BEGIN(MyGame)
class CScroll final : public CItem
{
private:
	explicit CScroll();
	virtual ~CScroll() = default;

public:
	virtual HRESULT Initialize();
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
public:
	CScroll Create();
	// CItem을(를) 통해 상속됨
	virtual CGameObject * Clone(void * _param = nullptr) override;
};
END
