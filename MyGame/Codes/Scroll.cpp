#include "stdafx.h"
#include "..\Headers\Scroll.h"

USING(MyGame)
HRESULT CScroll::Initialize()
{
	CItem::Initialize();
	m_vecActions.push_back(AC_READ);
	return S_OK;
}
