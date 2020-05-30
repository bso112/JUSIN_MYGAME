#pragma once
#include "Potion.h"
BEGIN(MyGame)
class CFirePotion final : public CPotion
{
protected:
	explicit CFirePotion(PDIRECT3DDEVICE9 _pGrahic_Device) :CPotion(_pGrahic_Device) {};
	explicit CFirePotion(CFirePotion& _rhs) : CPotion(_rhs) {};
	virtual ~CFirePotion() = default;

protected:
	void OnDrink(CHero* _pHero) override;
	void OnShatter() override;

public:
	static CFirePotion* CFirePotion::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr)
	{
		CFirePotion* pInstance = new CFirePotion(_pGrahic_Device);
		if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
		{
			MSG_BOX("Fail to create CFirePotion");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



	CFirePotion * CFirePotion::Clone(void * _param)
	{
		CFirePotion* pInstance = new CFirePotion(*this);
		if (FAILED(pInstance->Initialize(_param)))
		{
			MSG_BOX("Fail to create CFirePotion");
			Safe_Release(pInstance);

		}
		return pInstance;
	}

};
END
