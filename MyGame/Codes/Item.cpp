#include "stdafx.h"
#include "..\Headers\Item.h"
#include "Inventory.h"


USING(MyGame)
CItem::CItem(CItem & _rhs)
	: CGameObject(_rhs),
	m_pDescription(_rhs.m_pDescription)
{
};
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
	if (nullptr == _pHero)
		return E_FAIL;
	
	if (0 == lstrcmp(_pAction, AC_DROP))
	{
		m_bUsed = true;
		//아이템 버리기
		//트랜스폼을 플레이어쪽으로 이동
	}
	else if (0 == lstrcmp(_pAction, AC_THROW))
	{
		m_bUsed = true;
		//아이템 던지기
		//목적지로 트랜스폼 이동
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
