#pragma once
#include "Food.h"

BEGIN(MyGame)
class CCheese final :public CFood
{
private:
	explicit CCheese(PDIRECT3DDEVICE9 _pGrahic_Device) : CFood(_pGrahic_Device) {};
	explicit CCheese(CCheese& _rhs) : CFood(_rhs) {}
	virtual ~CCheese() = default;

public:
	virtual HRESULT Initialize(void * _param = nullptr) override;


public:
	static CCheese * CCheese::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr)
	{
		CCheese* pInstance = new CCheese(_pGrahic_Device);
		if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
		{
			MSG_BOX("Fail to create CFood");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



	CGameObject * CCheese::Clone(void * _param = nullptr)
	{
		CCheese* pInstance = new CCheese(*this);
		if (FAILED(pInstance->Initialize(_param)))
		{
			MSG_BOX("Fail to create CFood");
			Safe_Release(pInstance);

		}
		return pInstance;
	}


	// CFood을(를) 통해 상속됨
	virtual Vector3 Get_OriginalSize() override;

};
END
