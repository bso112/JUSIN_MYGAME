#include "stdafx.h"
#include "IceFlower.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Terrain.h"
USING(MyGame)
CIceFlower::CIceFlower(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CSeed(_pGrahic_Device)
{
}

CIceFlower::CIceFlower(CIceFlower & _rhs)
	: CSeed(_rhs)
{
}

HRESULT CIceFlower::Initialize(void * _param)
{
	CSeed::Initialize(_param);


	if (nullptr != _param)
		m_pTransform->Set_Position((*(Vector3*)_param));


	m_pDescription = L"�������� �����̴�. ������ ����� ��������.";
	m_iTextureID = 7;
	m_pItemName = L"�������� ����";

	return S_OK;
}


void CIceFlower::OnCollisionEnter(CGameObject * _pOther)
{
	//������ �ε�ģ�� �ƴϰ�, �� ���¶��
	if (nullptr == dynamic_cast<CTerrain*>(_pOther) && m_bFlower)
	{
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();

		if (m_pTransform == nullptr)
			return;

		CEffect*  pEffect = nullptr;
		BASEDESC desc = BASEDESC(m_pTransform->Get_Position(), m_pTransform->Get_Size());
		//����Ʈ ����
		pEffect = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));

		//����Ʈ ���
		if (pEffect)
			pEffect->Play();

		//����
		m_bDead = true;

	}
}

void CIceFlower::Free()
{
	CSeed::Free();
}
