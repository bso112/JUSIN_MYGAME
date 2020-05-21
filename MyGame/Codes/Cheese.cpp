#include "stdafx.h"
#include "..\Headers\Cheese.h"

USING(MyGame)
HRESULT CCheese::Initialize(void * _param)
{
	m_vSize = Vector3(25.f, 20.f);
	m_tDesc.tBaseDesc.vSize = Vector3(25.f, 20.f);
	m_pDescription = L"신선하고 맛좋은 치즈!";
	m_iTextureID = 1;
	m_pItemName = L"치즈";
	CFood::Initialize(_param);
	return S_OK;
}
