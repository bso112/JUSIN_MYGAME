#include "stdafx.h"
#include "..\Headers\Cheese.h"

USING(MyGame)
HRESULT CCheese::Initialize(void * _param)
{
	m_vSize = Vector3(25.f, 20.f);
	m_tDesc.tBaseDesc.vSize = Vector3(25.f, 20.f);
	m_pDescription = L"�ż��ϰ� ������ ġ��!";
	m_iTextureID = 1;
	m_pItemName = L"ġ��";
	CFood::Initialize(_param);
	return S_OK;
}
