#include "stdafx.h"
#include "wand.h"
#include "Laser.h"
#include "Hero.h"
USING(MyGame)
CWand::CWand(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CItem(_pGrahic_Device)
{
}

CWand::CWand(CWand & _rhs)
	: CItem(_rhs)
{
}

HRESULT CWand::Initialize(void * _param)
{
	CItem::Initialize(_param);
	m_vecActions.push_back(AC_ZAP);

	if (FAILED(Set_Module(L"wand", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_pTextureTag = L"wand";

	return S_OK;
}

HRESULT CWand::Use(CHero * _pHero, const _tchar ** _pAction)
{
	CItem::Use(_pHero, _pAction);
	if (nullptr == _pHero)
		return E_FAIL;

	CTransform* pHeroTransform = (CTransform*)_pHero->Get_Module(L"Transform");
	if (nullptr == pHeroTransform)
		return E_FAIL;

	if (0 == lstrcmp(*_pAction, AC_ZAP))
	{
		if (nullptr == m_pTransform)
			return E_FAIL;

		//사용됨
		m_bUsed = true;
		m_bDrop = true;
		_pHero->Zap();
	}
	else if (0 == lstrcmp(*_pAction, AC_THROW))
	{
		//사용됨
		m_bUsed = true;
		m_bDrop = true;
		//주인에게 던져달라고 함.
		_pHero->Shoot_Item(this);

	}
	return S_OK;
}

HRESULT CWand::Zap(TYPE _eType, Vector2 _vOrigin, POINT _pt)
{
	switch (_eType)
	{
	case MyGame::CWand::TYPE_IGHTING:
		Zap_Lighting(_vOrigin, _pt);
		break;
	}
	return E_NOTIMPL;
}

HRESULT CWand::Zap_Lighting(Vector2 _vOrigin, POINT _pt)
{
	return E_NOTIMPL;
}

CWand * CWand::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CWand* pInstance = new CWand(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create wand");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject * CWand::Clone(void * _param)
{
	CWand* pInstance = new CWand(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create wand");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CWand::Free()
{
	CItem::Free();
}

Vector3 CWand::Get_OriginalSize()
{
	return ;
}

