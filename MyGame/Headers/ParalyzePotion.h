#pragma once
#include "Potion.h"
BEGIN(MyGame)
class CParalyzePotion final : public CPotion
{
protected:
	explicit CParalyzePotion(PDIRECT3DDEVICE9 _pGrahic_Device) :CPotion(_pGrahic_Device) {};
	explicit CParalyzePotion(CParalyzePotion& _rhs) : CPotion(_rhs) {};
	virtual ~CParalyzePotion() = default;

protected:
	void OnDrink(CHero* _pHero) override;
	void OnShatter() override;

public:
	static CParalyzePotion* CParalyzePotion::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr)
	{
		CParalyzePotion* pInstance = new CParalyzePotion(_pGrahic_Device);
		if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
		{
			MSG_BOX("Fail to create CParalyzePotion");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



	CParalyzePotion * CParalyzePotion::Clone(void * _param)
	{
		CParalyzePotion* pInstance = new CParalyzePotion(*this);
		if (FAILED(pInstance->Initialize(_param)))
		{
			MSG_BOX("Fail to create CParalyzePotion");
			Safe_Release(pInstance);

		}
		return pInstance;
	}

};
END
