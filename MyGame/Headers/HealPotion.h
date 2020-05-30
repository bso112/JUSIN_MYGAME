#pragma once
#include "Potion.h"
BEGIN(MyGame)
class CHealPotion final : public CPotion
{
protected:
	explicit CHealPotion(PDIRECT3DDEVICE9 _pGrahic_Device) :CPotion(_pGrahic_Device) {};
	explicit CHealPotion(CHealPotion& _rhs) : CPotion(_rhs) {};
	virtual ~CHealPotion() = default;

protected:
	void OnDrink(CHero* _pHero) override;

public:
	static CHealPotion* CHealPotion::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr)
	{
		CHealPotion* pInstance = new CHealPotion(_pGrahic_Device);
		if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
		{
			MSG_BOX("Fail to create CHealPotion");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



	CHealPotion * CHealPotion::Clone(void * _param)
	{
		CHealPotion* pInstance = new CHealPotion(*this);
		if (FAILED(pInstance->Initialize(_param)))
		{
			MSG_BOX("Fail to create CHealPotion");
			Safe_Release(pInstance);

		}
		return pInstance;
	}

};
END
