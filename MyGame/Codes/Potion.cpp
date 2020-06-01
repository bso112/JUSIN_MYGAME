#include "stdafx.h"
#include "..\Headers\Potion.h"
#include "ParticleSystem.h"
#include "ObjMgr.h"
#include "TimerMgr.h"
#include "Character.h"
#include "Hero.h"
#include "DialogMgr.h"
USING(MyGame)

CPotion::CPotion(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CItem(_pGrahic_Device)
{
}

CPotion::CPotion(CPotion & _rhs)
	:CItem(_rhs)
{
}

HRESULT CPotion::Initialize(void * _param)
{
	CItem::Initialize(_param);
	m_vecActions.push_back(AC_DRINK);

	Set_Module(L"potion", SCENE_STAGE, (CModule**)&m_pTexture);
	m_pTextureTag = L"potion";
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &CTransform::STATEDESC(300.0, 300.0));
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);


	if (nullptr != _param)
		memcpy(&m_tDesc, _param, sizeof(STATEDESC));

	m_vOriginalSize = Vector2(30.f, 25.f);
	m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);
	m_pTransform->Set_Size(m_vOriginalSize);
	m_pTransform->Set_ColliderSize(COLLIDER_SIZE);


	m_pDescription = m_tDesc.m_pDescription;
	m_iTextureID = m_tDesc.m_iTextureID;
	m_pItemName = m_tDesc.m_pItemName;


	return S_OK;
}

HRESULT CPotion::Use(CHero * _pHero, const _tchar ** _pAction)
{
	if (nullptr == _pHero)
		return E_FAIL;
	CItem::Use(_pHero, _pAction);
	if (0 == lstrcmp(*_pAction, AC_DRINK))
	{
		//사용됨
		m_bUsed = true;
		m_bDead = true;
		OnDrink(_pHero);
	}
	return S_OK;
}

void CPotion::OnThrowEnd()
{
	if (nullptr == m_pTransform)
		return;

#pragma region 깨지는 파티클
	//피 파티클 생성
	Vector3 vPos = m_pTransform->Get_Position();
	CParticleSystem::STATEDESC desc;
	desc.m_tBaseDesc.vPos = m_pTransform->Get_Position();
	desc.m_pTextureTag = L"empty";
	desc.m_eTextureSceneID = SCENE_STATIC;
	desc.m_iTextureID = 1;
	//컬러로 조정하는 패스
	desc.m_iShaderPass = 8;
	desc.m_Color = m_tDesc.m_Color;
	desc.m_dDuration = 0.2;
	desc.m_dLifeTime = 0.2;
	desc.m_fSpeed = 300.f;
	desc.m_vParticleSize = Vector2(10.f, 10.f);
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	CParticleSystem* pParticleSystem = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STATIC, L"ParticleSystem", SCENE_STAGE, &desc));

	//피가 튀긴다.
	pParticleSystem->Spread(Vector3(0.f,-1.f,0.f), CTimerMgr::Get_Instance()->Get_TimeDelta(), 5);
#pragma endregion

	m_bDead = true;

	//포션마다의 효과
	OnShatter();

}


void CPotion::OnDrink(CHero * _pHero)
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션을 마셨지만, 아무일도 일어나지 않았다."));
}

void CPotion::OnShatter()
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션은 날카로운 소리를 내며 깨졌다. 그러나 아무일도 일어나지 않았다."));
}

Vector3 CPotion::Get_OriginalSize()
{
	return m_vOriginalSize;
}

void CPotion::OnCollisionEnter(CGameObject * _pOther)
{
	//데미지를 줄 수 있는 상태여야만 됨(던지는 중)
	if (!m_bThrown)
		return;

	if (nullptr == _pOther)
		return;
	
	CCharacter* pCharacter = dynamic_cast<CCharacter*>(_pOther);

	if (nullptr == pCharacter)
		return;
	//깨져서 사라짐
	OnThrowEnd();
}


void CPotion::Free()
{
	CItem::Free();
}
