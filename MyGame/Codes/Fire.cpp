#include "stdafx.h"
#include "Fire.h"
#include "ObjMgr.h"
#include "Character.h"
#include "Clock.h"

USING(MyGame)
CFire::CFire(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CEffect(_pGraphic_Device)
{
	ZeroMemory(&m_tBaseDesc, sizeof(BASEDESC));
}

CFire::CFire(CFire & _rhs)
	: CEffect(_rhs)
{
	ZeroMemory(&m_tBaseDesc, sizeof(BASEDESC));

}


//�������̶�� �����غ���.
HRESULT CFire::Initialize_Prototype(_tchar * _pFilePath)
{

	return S_OK;
}

HRESULT CFire::Initialize(void * _pArg)
{


	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pObjMgr);

	//Fire�� ��ġ ����.
	if (nullptr != _pArg)
	{
		m_tBaseDesc = *((BASEDESC*)_pArg);
		Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform");
		m_pTransform->Set_Position(m_tBaseDesc.vPos);
		m_pTransform->Set_Size(m_tBaseDesc.vSize);
		m_pTransform->Set_ColliderSize(m_tBaseDesc.vSize);
	}

	//����Ʈ ���ӽð� ����
	m_fDuration = DURATION_FIRE;
	//�� ��ƼŬ�ý��� ����
	m_tParticleDesc.m_dDuration = m_fDuration;
	m_tParticleDesc.m_dLifeTime = 0.5f;
	m_tParticleDesc.m_eTextureSceneID = SCENE_STAGE;
	m_tParticleDesc.m_fSpeed = 50.f;
	m_tParticleDesc.m_pTextureTag = L"Fire";
	m_tParticleDesc.m_tBaseDesc.vPos = m_tBaseDesc.vPos;
	m_tParticleDesc.m_tBaseDesc.vSize = m_tBaseDesc.vSize;
	m_tParticleDesc.m_vParticleSize = Vector2(5.f, 5.f);

	m_pParticleSystem = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STATIC, L"ParticleSystem", SCENE_STAGE, &m_tParticleDesc));
	RETURN_FAIL_IF_NULL(m_pParticleSystem);
	//����? ���̾�� �ְ� ����������� �����ϱ�.
	Safe_AddRef(m_pParticleSystem);
	m_pParticleSystem->Set_ShaderPass(4);
	m_pParticleSystem->Set_FadeOut();

	//��ƼŬ �ý����� �θ� fire�� ����
	CTransform* pPsTransform = dynamic_cast<CTransform*>(m_pParticleSystem->Get_Module(L"Transform"));
	if (nullptr != pPsTransform)
	{
		pPsTransform->Set_Parent(m_pTransform);
	}

	m_pSpawnTimer = CClock_Trigger::Create();

	return S_OK;
}

void CFire::Play()
{
	if (nullptr == m_pParticleSystem ||
		nullptr == m_pTransform)
		return;

	m_bPlaying = true;
}


_int CFire::Update(_double _timeDelta)
{	
	if (nullptr == m_pSpawnTimer)
		return -1;

	if (!m_bPlaying)
		return 0;

	//���ӽð��� �ٵǸ� ����
	if (0x80000000 & CEffect::Update(_timeDelta))
		return -1;

	if (nullptr == m_pParticleSystem)
		return -1;

	//Ÿ���� ���ذ���.
	if (nullptr != m_pTarget)
	{
		m_pTransform->Set_Position(m_pTarget->Get_WorldPos());
	}

	//0.5�ʸ��� ����
	if(m_pSpawnTimer->isThreashHoldReached(0.2))
		m_pParticleSystem->RollUp(m_pTransform->Get_RECT(), 5);

	return 0;
}

_int CFire::LateUpate(_double _timeDelta)
{
	m_pTransform->Update_Transform();

	//if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_EFFECT)))
	//	return -1;

	return 0;
}

HRESULT CFire::Render()
{
#ifndef MYDEBUG
	//m_pTransform->Render_Collider();

#endif // !MYDEBUG

	return S_OK;
}




void CFire::OnCollisionEnter(CGameObject * _pOther)
{
	CCharacter* pCharacter = dynamic_cast<CCharacter*>(_pOther);
	if (nullptr != pCharacter)
	{
		//�Һٴ´�.
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();
		//Ŭ���̳� ��������
		CEffect* pClone = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STATIC, &m_tBaseDesc));
		//ĳ���Ϳ� ����Ʈ�� �����Ѵ�.
		if (nullptr != pClone)
		{
			pCharacter->PlayEffect(pClone);
		}
	}

}

CFire * CFire::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CFire* pInstance = new CFire(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CFire");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CFire::Clone(void * _param)
{
	CFire* pInstance = new CFire(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CFire");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CFire::Free()
{
	Safe_Release(m_pSpawnTimer);
	CEffect::Free();
}


