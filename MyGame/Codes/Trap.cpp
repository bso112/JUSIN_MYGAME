#include "stdafx.h"
#include "..\Headers\Trap.h"
#include "ParticleSystem.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Transform.h"

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
	if (m_bUsed)
	{
		//충돌시 발각
		m_bHidden = false;
		//모습을 드러낸다.
		m_iCurFrame = m_eType;

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

HRESULT CTrap::OnLoadData()
{
	//타입 정하기
	if (TYPE_END <= (TYPE)m_iCurFrame)
		return E_FAIL;

	m_eType = (TYPE)m_iCurFrame;

	return S_OK;
}

