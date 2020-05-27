#include "stdafx.h"
#include "..\Headers\Cheese.h"

USING(MyGame)
HRESULT CCheese::Initialize(void * _param)
{
	CFood::Initialize(_param);

	

	if (nullptr != _param)
		memcpy(&m_tDesc, _param, sizeof(STATEDESC));

	m_pTransform->Set_Position(m_tDesc.tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.tBaseDesc.vSize);
	m_pTransform->Set_ColliderSize(COLLIDER_SIZE);

	m_pDescription = L"�ż��ϰ� ������ ġ��!";
	m_iTextureID = 1;
	m_pItemName = L"ġ��";
	return S_OK;
}

Vector3 CCheese::Get_OriginalSize()
{
	return m_tDesc.tBaseDesc.vSize;
}
