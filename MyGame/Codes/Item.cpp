#include "stdafx.h"
#include "..\Headers\Item.h"


USING(MyGame)
HRESULT CItem::Initialize(void * _param)
{
	m_vecActions.push_back(ACT_DROP);
	m_vecActions.push_back(ACT_THROW);

	return S_OK;
}

HRESULT CItem::Initialize_Prototype(_tchar * _pFilePath)
{
	return E_NOTIMPL;
}
