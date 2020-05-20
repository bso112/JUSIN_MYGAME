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
}

CTrap::CTrap(CTrap & _rhs)
	: CTerrain(_rhs)
{

};

_int CTrap::Interact(CGameObject * _pOther)
{



	return _int();
}

void CTrap::OnCollisionEnterTerrain(CGameObject * _pOther)
{

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();

	//����� ���¸� ����
	if (m_eType >= TYPE_END ||
		m_pTransform == nullptr ||
		m_bUsed)
		return;

	CEffect*  pEffect = nullptr;
	BASEDESC desc = BASEDESC(m_pTransform->Get_Position(), m_pTransform->Get_Size());
	//����Ʈ ����
	switch (m_eType)
	{
	case TYPE_FIRE:
		pEffect = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
		break;
	}

	//����Ʈ ���
	if (pEffect)
		pEffect->Play();

	//�� �������� �ؽ��� �ٲٱ�
	m_iCurFrame = 0;
	//����ߴٰ� ǥ��
	m_bUsed = true;
}

HRESULT CTrap::OnLoadData()
{
	//Ÿ�� ���ϱ�
	if (TYPE_END <= (TYPE)m_iCurFrame)
		return E_FAIL;

	m_eType = (TYPE)m_iCurFrame;

	return S_OK;
}

