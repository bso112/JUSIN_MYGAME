#include "stdafx.h"
#include "..\Headers\Trap.h"
#include "ParticleSystem.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Transform.h"
#include "DialogMgr.h"
#include "Texture.h"
#include "ParticleSystem.h"
USING(MyGame)

CTrap::CTrap(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CTerrain(_pGraphic_Device)
{
	m_bHidden = true;
}

CTrap::CTrap(CTrap & _rhs)
	: CTerrain(_rhs)
{
	//랜덤하게 숨기기
	int ranNum = rand() % 2;
	m_bHidden = ranNum;
};

_int CTrap::Interact(CGameObject * _pOther)
{



	return _int();
}

void CTrap::OnCollisionEnterTerrain(CGameObject * _pOther)
{
	if (!m_bActive)
		return;

	//이미 쓴 함정이 아닐때만 
	if (!m_bUsed && m_bHidden)
	{
		//충돌시 발각
		m_bHidden = false;
		//모습을 드러낸다.
		m_iCurFrame = (_int)m_eType;
		CDialogMgr* pDialogMgr = CDialogMgr::Get_Instance();
		if (nullptr != pDialogMgr)
			pDialogMgr->Log_Main(new wstring(L"숨겨져 있던 함정이 모습을 드러냈다."), COLOR_YELLOW);

	}

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();

	//사용한 상태면 무시
	if (m_eType >= TYPE_END ||
		m_pTransform == nullptr ||
		m_bUsed)
		return;

	CEffect*  pEffect = nullptr;
	BASEDESC tBsseDesc = BASEDESC(m_pTransform->Get_Position(), m_pTransform->Get_Size());
	CEffect::STATEDESC desc;
	desc.m_tBaseDesc = tBsseDesc;
	desc.m_tBuffType = CBuff::TYPE_BURN;
	//이펙트 생성
	switch (m_eType)
	{
	case TYPE_FIRE:
		pEffect = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
		break;
	}

	//이펙트 재생
	if (pEffect)
	{
		pEffect->Set_Collidable(true);
		pEffect->Play();
	}
	//빈 함정으로 텍스쳐 바꾸기
	m_iCurFrame = 0;
	//사용했다고 표시
	m_bUsed = true;
}

void CTrap::OnHidden()
{
	m_iCurFrame = 5;
}

void CTrap::OnReveal()
{
	//타입 정하기
	if (TYPE_END <= m_eType)
		return;

	//원래 모습으로 
	m_iCurFrame = (_int)m_eType;
	//예외처리
	if (m_pTexture->Get_TextureSize() <= m_iCurFrame)
		m_iCurFrame = m_pTexture->Get_TextureSize() - 1;

	//반짝반짝
	CParticleSystem::STATEDESC desc;
	desc.m_tBaseDesc.vPos = m_pTransform->Get_Position();
	desc.m_pTextureTag = L"shine";
	desc.m_eTextureSceneID = SCENE_STAGE;
	desc.m_dDuration = 0.5f;
	desc.m_dLifeTime = 0.5f;
	desc.m_fSpeed = 300.f;
	desc.m_vParticleSize = Vector2(20.f, 20.f);
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	CParticleSystem* pParticleSystem = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STATIC, L"ParticleSystem", SCENE_STAGE, &desc));
	//피가 튀긴다.
	pParticleSystem->SmokeUp(m_pTransform->Get_RECT(), 5);

}

HRESULT CTrap::OnLoadData()
{
	//타입 정하기
	if (TYPE_END <= (TYPE)m_iCurFrame)
		return E_FAIL;

	m_eType = (TYPE)m_iCurFrame;

	return S_OK;
}

