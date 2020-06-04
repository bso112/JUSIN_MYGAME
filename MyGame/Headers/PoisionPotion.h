#pragma once
#include "Potion.h"
BEGIN(MyGame)
class CPoisionPotion final : public CPotion
{
protected:
	explicit CPoisionPotion(PDIRECT3DDEVICE9 _pGrahic_Device) :CPotion(_pGrahic_Device) { };
	explicit CPoisionPotion(CPoisionPotion& _rhs) : CPotion(_rhs) {};
	virtual ~CPoisionPotion() = default;

protected:
	void OnDrink(CHero* _pHero) override;
	void OnShatter() override;

public:
	static CPoisionPotion* CPoisionPotion::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr)
	{
		CPoisionPotion* pInstance = new CPoisionPotion(_pGrahic_Device);
		if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
		{
			MSG_BOX("Fail to create CPoisionPotion");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



	CPoisionPotion * CPoisionPotion::Clone(void * _param)
	{
		CPoisionPotion* pInstance = new CPoisionPotion(*this);
		if (FAILED(pInstance->Initialize(_param)))
		{
			MSG_BOX("Fail to create CPoisionPotion");
			Safe_Release(pInstance);

		}
		return pInstance;
	}

};
END
