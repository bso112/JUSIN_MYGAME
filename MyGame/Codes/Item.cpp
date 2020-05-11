#include "stdafx.h"
#include "..\Headers\Item.h"


USING(MyGame)
HRESULT CItem::Initialize(void * _param)
{
	m_vecActions.push_back(AC_DROP);
	m_vecActions.push_back(AC_THROW);

	return S_OK;
}

HRESULT CItem::Initialize_Prototype(_tchar * _pFilePath)
{
	return S_OK;
}

HRESULT CItem::Use(CHero* _pHero, const _tchar * _pAction)
{
	if (0 == lstrcmp(_pAction, AC_DROP))
	{
		//아이템 버리기
	}
	else if (0 == lstrcmp(_pAction, AC_THROW))
	{
		//아이템 던지기
	}
	return S_OK;
}

void CItem::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	CGameObject::Free();
}
