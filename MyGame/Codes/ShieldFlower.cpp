#include "stdafx.h"
#include "ShieldFlower.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Terrain.h"
USING(MyGame)
CShieldFlower::CShieldFlower(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CSeed(_pGrahic_Device)
{
}

CShieldFlower::CShieldFlower(CShieldFlower & _rhs)
	: CSeed(_rhs)
{
}

HRESULT CShieldFlower::Initialize(void * _param)
{
	CSeed::Initialize(_param);


	if (nullptr != _param)
		m_pTransform->Set_Position((*(Vector3*)_param));



	m_pDescription = L"방패꽃의 씨앗이다. 단단해보인다.";
	m_iTextureID = 5;
	m_pItemName = L"방패꽃의 씨앗";

	return S_OK;
}


void CShieldFlower::OnCollisionEnter(CGameObject * _pOther)
{
	//지형과 부딪친게 아니고, 꽃 상태라면
	if (nullptr == dynamic_cast<CTerrain*>(_pOther) && m_bFlower)
	{
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();

		if (m_pTransform == nullptr)
			return;

		CEffect*  pEffect = nullptr;
		BASEDESC tBsseDesc = BASEDESC(m_pTransform->Get_Position(), m_pTransform->Get_Size());
		CEffect::STATEDESC desc;
		desc.m_tBaseDesc = tBsseDesc;
		desc.m_tBuffType = CBuff::TYPE_BURN;
		
		//이펙트 생성
		pEffect = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));

		//이펙트 재생
		if (pEffect)
			pEffect->Play();

		//죽음
		m_bDead = true;

	}
}

void CShieldFlower::Free()
{
	CSeed::Free();
}
