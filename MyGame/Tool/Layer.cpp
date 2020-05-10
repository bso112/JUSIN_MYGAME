#include "stdafx.h"
#include "Layer.h"
#include "GameObject.h"
USING(MyGame)

HRESULT CLayer::Initialize()
{
	return S_OK;
}



_int CLayer::Update(_double _timeDelta)
{
	for (auto& obj : m_listGO)
	{
		if (nullptr != obj)
		{
			if(0x80000000 & obj->Update(_timeDelta))
				return -1;
		}
	}

	return 0;
}

_int CLayer::Late_Update(_double _timeDelta)
{
	for (auto& obj : m_listGO)
	{
		if (nullptr != obj)
		{
			if (0x80000000 & obj->LateUpate(_timeDelta))
				return -1;
		}
	}

	return 0;
}

HRESULT CLayer::Add_GameObject(CGameObject * _pGO)
{
	if (nullptr == _pGO)
		return E_FAIL;

	m_listGO.push_back(_pGO);
	return S_OK;
}

CLayer * CLayer::Create()
{
	CLayer* pInstance = new CLayer;
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to create Layer");
		Safe_Release(pInstance);
	}
	
	return pInstance;
}

void CLayer::Free()
{
	for (CGameObject* GO : m_listGO)
	{
		Safe_Release(GO);
	}
	m_listGO.clear();

}
