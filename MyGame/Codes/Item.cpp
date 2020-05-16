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
		//������ ������
		//Ʈ�������� �÷��̾������� �̵�
	}
	else if (0 == lstrcmp(_pAction, AC_THROW))
	{
		m_bUsed = true;
		//������ ������
		//�������� Ʈ������ �̵�
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
