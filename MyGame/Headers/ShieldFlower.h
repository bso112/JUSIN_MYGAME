#pragma once
#include "Seed.h"
BEGIN(MyGame)
class CShieldFlower : public CSeed
{
protected:
	explicit CShieldFlower(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CShieldFlower(CShieldFlower& _rhs);
	virtual ~CShieldFlower() = default;

public:
	virtual HRESULT Initialize(void * _param = nullptr);


public:
	virtual void OnCollisionEnter(CGameObject* _pOther);



public:
	static CShieldFlower * CShieldFlower::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr)
	{
		CShieldFlower* pInstance = new CShieldFlower(_pGrahic_Device);
		if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
		{
			MSG_BOX("Fail to create CShieldFlower");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



	CGameObject * CShieldFlower::Clone(void * _param = nullptr)
	{
		CShieldFlower* pInstance = new CShieldFlower(*this);
		if (FAILED(pInstance->Initialize(_param)))
		{
			MSG_BOX("Fail to create CShieldFlower");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
