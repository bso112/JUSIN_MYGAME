#include "stdafx.h"
#include "Particle.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Clock.h"

USING(MyGame)


CParticle::CParticle(CParticle & _rhs)
	:CGameObject(_rhs)
{
	m_bActive = true;
	ZeroMemory(&m_tDesc, sizeof(STATEDESC));
	
}



HRESULT CParticle::Initialize(void * _pArg)
{
	if (nullptr != _pArg)
		memcpy(&m_tDesc, _pArg, sizeof(STATEDESC));

	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	m_pDeadClock = CClock_Delay::Create();

	CTransform::STATEDESC transformDesc;
	transformDesc.speedPerSec = m_tDesc.m_fSpeed;
	transformDesc.radianPerSec = m_tDesc.m_dRadianPerSec;

	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &transformDesc)))
		return E_FAIL;

	m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.m_tBaseDesc.vSize);


	return S_OK;
}

_int CParticle::Update(_double _timeDelta)
{
	if (nullptr == m_pDeadClock)
		return -1;

	if (m_bDead)
		return -1;

	if (!m_bActive)
		return 0;

	//라이프타임이 지나면 죽기
	if (m_pDeadClock->isThreashHoldReached(m_tDesc.m_dLifeTime))
		m_bDead = true;


	if (m_bFadeOut)
	{
		//알파값 점점 줄이기
		m_fAlpha -= (1 / m_tDesc.m_dLifeTime) * _timeDelta;
		if (m_fAlpha <= 0)
			m_fAlpha = 0;
	}


	//이동
	m_pTransform->Update_Normal(_timeDelta);

	return 0;
}

_int CParticle::LateUpate(_double _timeDelta)
{
	if (m_bDead)
		return -1;

	if (!m_bActive)
		return 0;

	//m_pTransform->Get_Matrix() 에서 UpdateTransform 하기 때문에 여기서 안함.
	return 0;
}

HRESULT CParticle::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTransform)
		return E_FAIL;

	_matrix tmp = m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix();
	//비긴셰이더는 파티클시스템에서 함
	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix())))
		return E_FAIL;
	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	//하위클래스의 렌더
	OnRender();

	return S_OK;
}

HRESULT CParticle::OnRender()
{
	return S_OK;
}



CParticle * CParticle::Create(PDIRECT3DDEVICE9 _pGraphic_Device, STATEDESC& _tDesc)
{
	CParticle* pInstance = new CParticle(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(&_tDesc)))
	{
		MSG_BOX("Fail to create CParicle");
		Safe_Release(pInstance);

	}
	return pInstance;
}



void CParticle::Free()
{
	Safe_Release(m_pDeadClock);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);

	CGameObject::Free();
}

CGameObject * CParticle::Clone(void * _pArg)
{
	return nullptr;
}

