#include "stdafx.h"
#include "..\Headers\Cheese.h"

USING(MyGame)
HRESULT CCheese::Initialize(void * _param)
{
	m_pDescription = L"�ż��ϰ� ������ ġ��!";
	m_tDesc.iTextureID = 1;
	CFood::Initialize(_param);
	return S_OK;
}
