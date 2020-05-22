#pragma once
#include "Seed.h"
BEGIN(MyGame)
class CIceFlower : public CSeed
{
protected:
	explicit CIceFlower(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CIceFlower(CIceFlower& _rhs);
	virtual ~CIceFlower() = default;

public:
	virtual HRESULT Initialize(void * _param = nullptr);


public:
	virtual void OnCollisionEnter(CGameObject* _pOther);



public:
	static CIceFlower * CIceFlower::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr)
	{
		CIceFlower* pInstance = new CIceFlower(_pGrahic_Device);
		if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
		{
			MSG_BOX("Fail to create CIceFlower");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



	CGameObject * CIceFlower::Clone(void * _param = nullptr)
	{
		CIceFlower* pInstance = new CIceFlower(*this);
		if (FAILED(pInstance->Initialize(_param)))
		{
			MSG_BOX("Fail to create CIceFlower");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
