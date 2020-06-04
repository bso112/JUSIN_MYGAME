#include "stdafx.h"
#include "..\Headers\Food.h"
#include "Hero.h"
#include "InventoryUIMgr.h"
#include "DialogMgr.h"
#include "ObjMgr.h"
#include "Image.h"
USING(MyGame)


CFood::CFood(CFood & _rhs)
	:CItem(_rhs)
{
	ZeroMemory(&m_tDesc, sizeof(STATEDESC));

}



HRESULT CFood::Initialize(void * _param)
{
	//할 수 있는 행동을 정한다.
	CItem::Initialize(_param);
	m_vecActions.push_back(AC_EAT);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &CTransform::STATEDESC(300.0, 300.0));
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Texture_Food", SCENE_STAGE, (CModule**)&m_pTexture);
	m_pTextureTag = L"Texture_Food";

	m_pTransform->Set_ColliderSize(COLLIDER_SIZE);

	m_bStackable = true;
	return S_OK;
}



HRESULT CFood::Use(CHero * _pHero, const _tchar ** _pAction)
{
	//이거 하면 인벤토리 닫힐때 액티브 false되서 작동안함
	//if (!m_bActive)
	//	return 0;

	if (0 == lstrcmp(*_pAction, AC_EAT))
	{
		//먹기
		//_pHero->Heal(m_tDesc.fHealAmount);

		//음식 파티클 생성
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();
		if (nullptr == pObjMgr) return E_FAIL;
		if (nullptr == m_pTransform)return E_FAIL;
		CTransform* pHeroTransform = (CTransform*)_pHero->Get_Module(L"Transform");
		Vector3 vPos = pHeroTransform->Get_Position();
		CImage::STATEDESC desc;
		desc.m_dLifeTime = 0.5f;
		desc.m_eTextureSceneID = SCENE_STAGE;
		desc.m_fSpeed = 70.f;
		desc.m_pTextureTag = L"specks";
		desc.m_tBaseDesc = BASEDESC(vPos, Vector2(20.f, 20.f));
		desc.m_iTextureID = 5;

		CImage* pImage = (CImage*)pObjMgr->Add_GO_To_Layer(L"Particle", SCENE_STAGE, CImage::Create(m_pGraphic_Device, &desc));
		if (nullptr == pImage)
			return E_FAIL;

		_pHero->ShowBuffImg(pImage);

		m_bUsed = true;
		m_bDead = true;
		CDialogMgr::Get_Instance()->Log_Main(MSG_EAT(m_pItemName));
	
	
		_pHero->PlayAnimation(L"eat");
	}

	return CItem::Use(_pHero, _pAction);
}


void CFood::Free()
{
	CItem::Free();
}
