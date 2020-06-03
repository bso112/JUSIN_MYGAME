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
	//�����ϰ� �����
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
	
	//�̹� �� ������ �ƴҶ��� 
	if (m_bUsed)
	{
		//�浹�� �߰�
		m_bHidden = false;
		//����� �巯����.
		m_iCurFrame = m_eType;

	}

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();

	//����� ���¸� ����
	if (m_eType >= TYPE_END ||
		m_pTransform == nullptr ||
		m_bUsed)
		return;

	CEffect*  pEffect = nullptr;
	BASEDESC tBsseDesc = BASEDESC(m_pTransform->Get_Position(), m_pTransform->Get_Size());
	CEffect::STATEDESC desc;
	desc.m_tBaseDesc = tBsseDesc;
	desc.m_tBuffType = CBuff::TYPE_BURN;
	//����Ʈ ����
	switch (m_eType)
	{
	case TYPE_FIRE:
		pEffect = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
		break;
	}

	//����Ʈ ���
	if (pEffect)
	{
		pEffect->Set_Collidable(true);
		pEffect->Play();
	}
	//�� �������� �ؽ��� �ٲٱ�
	m_iCurFrame = 0;
	//����ߴٰ� ǥ��
	m_bUsed = true;
}

void CTrap::OnHidden()
{
	m_iCurFrame = 5;
}

HRESULT CTrap::OnLoadData()
{
	//Ÿ�� ���ϱ�
	if (TYPE_END <= (TYPE)m_iCurFrame)
		return E_FAIL;

	m_eType = (TYPE)m_iCurFrame;

	return S_OK;
}

