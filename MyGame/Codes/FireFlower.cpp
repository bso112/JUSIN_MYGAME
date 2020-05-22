#include "stdafx.h"
#include "FireFlower.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Terrain.h"
USING(MyGame)
CFireFlower::CFireFlower(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CSeed(_pGrahic_Device)
{
}

CFireFlower::CFireFlower(CFireFlower & _rhs)
	: CSeed(_rhs)
{
}

HRESULT CFireFlower::Initialize(void * _param)
{
	CSeed::Initialize(_param);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &CTransform::STATEDESC(300.0, 300.0));
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);

	if (nullptr != _param)
		m_pTransform->Set_Position((*(Vector3*)_param));

	m_vOriginalSize = Vector2(30.f, 25.f);
	m_pTransform->Set_Size(m_vOriginalSize);
	m_pTransform->Set_ColliderSize(m_vOriginalSize);


	m_pDescription = L"화염꽃의 씨앗이다. 뜨거운 기운이 느껴진다.";
	m_iTextureID = 1;
	m_pItemName = L"화염꽃의 씨앗";

	return S_OK;
}


void CFireFlower::OnCollisionEnter(CGameObject * _pOther)
{
	//지형과 부딪친게 아니고, 꽃 상태라면
	if (nullptr == dynamic_cast<CTerrain*>(_pOther) && m_bFlower)
	{
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();

		if (m_pTransform == nullptr)
			return;

		CEffect*  pEffect = nullptr;
		BASEDESC desc = BASEDESC(m_pTransform->Get_Position(), m_pTransform->Get_Size());
		//이펙트 생성
		pEffect = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));

		//이펙트 재생
		if (pEffect)
			pEffect->Play();

		//죽음
		m_bDead = true;

	}
}

void CFireFlower::Free()
{
	CSeed::Free();
}
