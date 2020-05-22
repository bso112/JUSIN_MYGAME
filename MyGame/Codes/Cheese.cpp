#include "stdafx.h"
#include "..\Headers\Cheese.h"

USING(MyGame)
HRESULT CCheese::Initialize(void * _param)
{
	CFood::Initialize(_param);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &CTransform::STATEDESC(300.0, 300.0));
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);


	if (nullptr != _param)
		memcpy(&m_tDesc, _param, sizeof(STATEDESC));

	m_pTransform->Set_Position(m_tDesc.tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.tBaseDesc.vSize);
	m_pTransform->Set_ColliderSize(m_tDesc.tBaseDesc.vSize);

	m_pDescription = L"�ż��ϰ� ������ ġ��!";
	m_iTextureID = 1;
	m_pItemName = L"ġ��";
	return S_OK;
}

Vector3 CCheese::Get_OriginalSize()
{
	return m_tDesc.tBaseDesc.vSize;
}
