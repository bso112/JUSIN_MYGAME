#include "stdafx.h"
#include "Fire.h"
#include "ObjMgr.h"
#include "Character.h"

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
	CParticleSystem::STATEDESC tPsDesc;
	tPsDesc.m_dDuration = m_fDuration;
	tPsDesc.m_dLifeTime = 1.f;
	tPsDesc.m_eTextureSceneID = SCENE_STAGE;
	tPsDesc.m_fSpeed = 1.f;
	tPsDesc.m_pTextureTag = L"Fire";
	tPsDesc.m_tBaseDesc.vPos = m_tBaseDesc.vPos;
	tPsDesc.m_tBaseDesc.vSize = m_tBaseDesc.vSize;
	tPsDesc.m_vParticleSize = Vector2(5.f, 5.f);

	m_pParticleSystem = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STATIC, L"ParticleSystem", SCENE_STAGE, &tPsDesc));
	RETURN_FAIL_IF_NULL(m_pParticleSystem);
	//����? ���̾�� �ְ� ����������� �����ϱ�.
	Safe_AddRef(m_pParticleSystem);


	//��ƼŬ �ý����� �θ� fire�� ����
	CTransform* pPsTransform = dynamic_cast<CTransform*>(m_pParticleSystem->Get_Module(L"Transform"));
	if (nullptr != pPsTransform)
	{
		pPsTransform->Set_Parent(m_pTransform);
	}

	return S_OK;
}

void CFire::Play()
{
	if (nullptr == m_pParticleSystem ||
		nullptr == m_pTransform)
		return;

	//Fire�� ��ġ�� ��ƼŬ �ý��� ���
	m_pParticleSystem->RollUp(m_pTransform->Get_RECT(), PARTICLE_CNT_FIRE);
}


_int CFire::Update(_double _timeDelta)
{
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

	return _int();
}

_int CFire::LateUpate(_double _timeDelta)
{
	m_pTransform->Update_Transform();

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_EFFECT)))
		return -1;

	return 0;
}

HRESULT CFire::Render()
{
	m_pTransform->Render_Collider();
	return S_OK;
}




void CFire::OnCollisionEnter(CGameObject * _pOther)
{
	//�����ӵ��
	//CCharacter* pCharacter = dynamic_cast<CCharacter*>(_pOther);
	//if (nullptr != pCharacter)
	//{
	//	//�Һٴ´�.
	//	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	//	//Ŭ���̳� ��������
	//	CEffect* pClone = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STATIC, &m_tBaseDesc));
	//	//ĳ���͸� Ÿ������ �Ѵ�.
	//	if (nullptr != pClone)
	//	{
	//		pClone->Set_Target(dynamic_cast<CTransform*>(pCharacter->Get_Module(L"Transform")));
	//		pClone->Play();
	//	}
	//}

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
	CEffect::Free();
}


