#pragma once
#include "Seed.h"
BEGIN(MyGame)
class CFireFlower : public CSeed
{
protected:
	explicit CFireFlower(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CFireFlower(CFireFlower& _rhs);
	virtual ~CFireFlower() = default;

public:
	virtual HRESULT Initialize(void * _param = nullptr);


public:
	virtual void OnCollisionEnter(CGameObject* _pOther);



public:
	static CFireFlower * CFireFlower::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr)
	{
		CFireFlower* pInstance = new CFireFlower(_pGrahic_Device);
		if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
		{
			MSG_BOX("Fail to create CFireFlower");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



	CGameObject * CFireFlower::Clone(void * _param = nullptr)
	{
		CFireFlower* pInstance = new CFireFlower(*this);
		if (FAILED(pInstance->Initialize(_param)))
		{
			MSG_BOX("Fail to create CFireFlower");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};
END
