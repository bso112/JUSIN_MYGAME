#pragma once
#include "Item.h"
BEGIN(MyGame)
class CKey : public CItem
{
protected:
	explicit CKey(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CKey(CKey& _rhs);
	virtual ~CKey() = default;

public:
	virtual HRESULT Initialize(void * _param = nullptr) override;

private:
	Vector2 m_vOriginalSize = Vector2(20.f, 20.f);

protected:
	virtual	void	OnPickUp(CHero*	_pHero, CInventory* _pInventory) override;

public:
	static CKey * CKey::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr)
	{
		CKey* pInstance = new CKey(_pGrahic_Device);
		if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
		{
			MSG_BOX("Fail to create CKey");
			Safe_Release(pInstance);

		}
		return pInstance;
	}



	CGameObject * CKey::Clone(void * _param = nullptr)
	{
		CKey* pInstance = new CKey(*this);
		if (FAILED(pInstance->Initialize(_param)))
		{
			MSG_BOX("Fail to create CKey");
			Safe_Release(pInstance);

		}
		return pInstance;
	}


	// CFood을(를) 통해 상속됨
	virtual Vector3 Get_OriginalSize() { return m_vOriginalSize; }

};
END
