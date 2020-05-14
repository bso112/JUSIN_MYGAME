#include "stdafx.h"
#include "..\Headers\Layer.h"
#include "GameObject.h"
USING(MyGame)

HRESULT CLayer::Initialize()
{
	return S_OK;
}



_int CLayer::Update(_double _timeDelta)
{
	//이거 리스트가 비어도 괜찮은 건가?
	auto& iter = m_listGO.begin();
	while (iter != m_listGO.end())
	{
		if (0x80000000 & (*iter)->Update(_timeDelta))
		{
			Safe_Release(*iter);
			iter = m_listGO.erase(iter);
		}
		else
			++iter;
	}

	return 0;
}

_int CLayer::Late_Update(_double _timeDelta)
{
	auto& iter = m_listGO.begin();
	while (iter != m_listGO.end())
	{
		if (0x80000000 & (*iter)->LateUpate(_timeDelta))
		{
			Safe_Release(*iter);
			iter = m_listGO.erase(iter);
		}
		else
			++iter;
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
