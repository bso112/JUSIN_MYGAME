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
	if (!m_bUsed && m_bHidden)
	{
		//�浹�� �߰�
		m_bHidden = false;
		//����� �巯����.
		m_iCurFrame = (_int)m_eType;
		CDialogMgr* pDialogMgr = CDialogMgr::Get_Instance();
		if (nullptr != pDialogMgr)
			pDialogMgr->Log_Main(new wstring(L"������ �ִ� ������ ����� �巯�´�."), COLOR_YELLOW);

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

void CTrap::OnReveal()
{
	//Ÿ�� ���ϱ�
	if (TYPE_END <= m_eType)
		return;

	//���� ������� 
	m_iCurFrame = (_int)m_eType;
	//����ó��
	if (m_pTexture->Get_TextureSize() <= m_iCurFrame)
		m_iCurFrame = m_pTexture->Get_TextureSize() - 1;

	//��¦��¦
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
	//�ǰ� Ƣ���.
	pParticleSystem->SmokeUp(m_pTransform->Get_RECT(), 5);

}

HRESULT CTrap::OnLoadData()
{
	//Ÿ�� ���ϱ�
	if (TYPE_END <= (TYPE)m_iCurFrame)
		return E_FAIL;

	m_eType = (TYPE)m_iCurFrame;

	return S_OK;
}

