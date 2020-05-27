#include "stdafx.h"
#include "..\Headers\Key.h"
#include "Inventory.h"

USING(MyGame)

CKey::CKey(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CItem(_pGrahic_Device)
{
}

CKey::CKey(CKey & _rhs)
	: CItem(_rhs)
{
}

HRESULT CKey::Initialize(void * _param)
{
	//�� �� �ִ� �ൿ�� ���Ѵ�.
	CItem::Initialize(_param);

	Set_Module(L"key", SCENE_STAGE, (CModule**)&m_pTexture);
	m_pTextureTag = L"key";

	//�ϴ� �׳� Ű ������ �ϳ��� �ִٰ� �����ϰ� �� �����Ѵ�

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &CTransform::STATEDESC(300.0, 300.0));
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);


	if (nullptr != _param)
		m_pTransform->Set_Position(*(Vector3*)_param);

	m_pTransform->Set_Size(m_vOriginalSize);
	m_pTransform->Set_ColliderSize(COLLIDER_SIZE);

	m_pItemName = L"����";
	m_pDescription = L"��� ���� �� �� �ִ�.";
	m_iTextureID = 1;

	return S_OK;
}

void CKey::OnPickUp(CHero * _pHero, CInventory * _pInventory)
{
	_pInventory->Put_Key(this);
}
