#include "stdafx.h"
#include "..\Headers\Scroll.h"

USING(MyGame)
HRESULT CScroll::Initialize()
{
	CItem::Initialize();
	m_vecActions.push_back(ACT_USE);
	return S_OK;
}
