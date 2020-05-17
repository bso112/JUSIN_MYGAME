#include "stdafx.h"
#include "ParticleSystem.h"
#include "Transform.h"
#include "Image.h"
#include "ObjMgr.h"
USING(MyGame)

CParticleSystem::CParticleSystem(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
}
CParticleSystem::CParticleSystem(CParticleSystem & _rhs)
	:CGameObject(_rhs)
{
}

HRESULT CParticleSystem::Play(_double _timeDelta, _uint _iParticleCnt)
{
	Spread(_timeDelta, _iParticleCnt);
	return S_OK;
}

HRESULT CParticleSystem::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CParticleSystem::Initialize(void * _pArg)
{
	if (nullptr != _pArg)
		m_tDesc = *((STATEDESC*)_pArg);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform);

	m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.m_tBaseDesc.vSize);

	
	return S_OK;
}
_int CParticleSystem::Update(_double _timeDelta)
{
	//��ƼŬ�ý��� �������� ��ƼŬ���� �̵�, ������Ų��.
	for (auto& particle : m_listParticle)
	{
		if (nullptr == particle) return 0;
		CTransform* pTransform = (CTransform*)particle->Get_Module(L"Transform");
		if (nullptr == pTransform) return 0;

		pTransform->RevolveAround(m_pTransform);
	}

	return 0;
}

_int CParticleSystem::LateUpdate(_double _timeDelta)
{
	m_pTransform->Update_Transform();
	
	return 0;
}

HRESULT CParticleSystem::Render()
{

	return S_OK;
}


void CParticleSystem::Spread(_double _timeDelta,  _uint _iParticleCnt)
{
	/*
	1.�������� ������ ���Ѵ�.
	2.��ƼŬ ������ ���� �� ������ ������ ���� ������ ���Ѵ�.
	3.��ä���� ������ ��ġ�� ���Ѵ�.
	4.������ ���ذ��� ��ƼŬ�� �����Ѵ�.
	5.��ƼŬ�� ������ �������� �����̰��Ѵ�.
	6.�θ��� ��ƼŬ �ý����� ���ϴ� �������� ȸ���Ѵ�.
	*/

	//��ä���� �߰��� �Ǵ� ��
	_float middle = 90.f;
	//������ ��
	_float spreadAngle = 60.f;
	_float gap = spreadAngle / (float)_iParticleCnt;
	_float startAngle = middle + (gap * (float)_iParticleCnt / 2);
	
	_float currAngle;

	Vector3 vPos = m_pTransform->Get_Position();
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return;

	//��ƼŬ�� �����Ѵ�.
	for (int i = 0; i < _iParticleCnt; ++i)
	{
		//�ӵ��� �־���ϴµ�..
		CImage::STATEDESC stateDesc;
		stateDesc.m_eTextureSceneID = m_tDesc.m_eTextureSceneID;
		stateDesc.m_fSpeed = m_tDesc.m_fSpeed;
		stateDesc.m_pTextureTag = m_tDesc.m_pTextureTag;
		stateDesc.m_tBaseDesc.vPos = m_tDesc.m_tBaseDesc.vPos;
		stateDesc.m_tBaseDesc.vSize = m_tDesc.m_vParticleSize;
		CImage* pImage = CImage::Create(m_pGraphic_Device, &stateDesc);
		m_listParticle.push_back((CImage*)pObjMgr->Add_GO_To_Layer(L"Particle", SCENE_STAGE, pImage));
		Safe_AddRef(pImage);
		//������ ���� ��ƼŬ�� �̵��ؾ��� ������ ������ �̵�
		currAngle = startAngle - gap;
		Vector2 vDir = Vector2(cosf(currAngle), sinf(currAngle));
		CTransform* pParicleTransform = (CTransform*)m_listParticle.back()->Get_Module(L"Transform");
		if (nullptr == pParicleTransform)
			return;
		pParicleTransform->MoveToDir(vDir, _timeDelta);

	}
	
}


CParticleSystem * CParticleSystem::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CParticleSystem* pInstance = new CParticleSystem(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CImage");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CParticleSystem::Clone(void * _pArg)
{
	CParticleSystem* pInstance = new CParticleSystem(*this);
	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to create CImage");
		Safe_Release(pInstance);

	}

	return pInstance;
}

void CParticleSystem::Free()
{
	for (auto& particle : m_listParticle)
	{
		Safe_Release(particle);
	}
}
