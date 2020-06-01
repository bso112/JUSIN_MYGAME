#include "stdafx.h"
#include "ParticleSystem.h"
#include "Transform.h"
#include "Particle.h"
#include "ObjMgr.h"
#include "Clock.h"
#include "Texture.h"
#include "Shader.h"
#include "TimerMgr.h"
USING(MyGame)

CParticleSystem::CParticleSystem(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device),
	m_pObjMgr(CObjMgr::Get_Instance())
{
	Safe_AddRef(m_pObjMgr);
	ZeroMemory(&m_tDesc, sizeof(STATEDESC));

}
CParticleSystem::CParticleSystem(CParticleSystem & _rhs)
	: CGameObject(_rhs),
	m_pObjMgr(CObjMgr::Get_Instance())
{
	Safe_AddRef(m_pObjMgr);
	ZeroMemory(&m_tDesc, sizeof(STATEDESC));

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
	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;
	if (FAILED(Set_Module(m_tDesc.m_pTextureTag, m_tDesc.m_eTextureSceneID, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);
	//절대 사이즈
	m_pTransform->Set_Size(Vector2(100.f, 100.f));


	m_pDeadClock = CClock_Delay::Create();

	return S_OK;
}
_int CParticleSystem::Update(_double _timeDelta)
{
	if (m_bDead)
		return -1;

	if (nullptr == m_pDeadClock)
		return -1;


	//피 파티클의 경우, 턴에 영향을 받는게 아니라 시간에 영향을 받기 때문에 해야한다.
	if (m_pDeadClock->isThreashHoldReached(m_tDesc.m_dDuration))
	{
		m_bDead = true;
		for (auto& particle : m_listParticle)
		{
			particle->Set_Dead();
		}
		return -1;
	}

	//매니저에 등록안하니 업데이트 불러줘야함
	auto& iter = m_listParticle.begin();
	while (iter != m_listParticle.end())
	{
		if (0x80000000 & (*iter)->Update(_timeDelta))
		{
			Safe_Release(*iter);
			iter = m_listParticle.erase(iter);

		}
		else
			++iter;
	}


	return 0;
}

_int CParticleSystem::LateUpate(_double _timeDelta)
{
	if (m_bDead)
		return -1;

	//부모인 Effect가 움직이면 같이 움직여야됨. 
	m_pTransform->Update_Transform();

	if (nullptr == m_pRenderer)
		return -1;

	//딱히 하는건 없지만 부르자.
	for (auto& particle : m_listParticle)
	{
		particle->LateUpate(_timeDelta);
	}

	m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_PARTICLE);


	return 0;
}

HRESULT CParticleSystem::Render()
{
	if (m_bDead)
		return -1;


	ALPHABLEND;

	_int textureID = m_tDesc.m_iTextureID - 1;
	if (m_tDesc.m_iTextureID - 1 < 0)
		textureID = 0;
	if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", textureID)))
		return E_FAIL;


	if (FAILED(m_pShader->Set_Value("g_vColor", &m_tDesc.m_Color, sizeof(D3DXCOLOR))))
		return E_FAIL;



	if (FAILED(m_pShader->Begin()))
		return E_FAIL;
	if (FAILED(m_pShader->Begin_Pass(m_tDesc.m_iShaderPass)))
		return E_FAIL;

	for (auto& particle : m_listParticle)
	{

		_float alpha = ((CParticle*)particle)->Get_Alpha();
		if (FAILED(m_pShader->Set_Value("g_Alpha", &alpha, sizeof(_float))))
			return E_FAIL;

		m_pShader->CommitChage();

		particle->Render();

	}

	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End()))
		return E_FAIL;


	ALPHABLEND_END;

	_float OriginalAlpha = 1.f;
	//원래대로 돌려놓기
	if (FAILED(m_pShader->Set_Value("g_Alpha", &OriginalAlpha, sizeof(_float))))
		return E_FAIL;

	D3DXCOLOR color = 0xffffffff;
	if (FAILED(m_pShader->Set_Value("g_vColor", &color, sizeof(D3DXCOLOR))))
		return E_FAIL;


	return S_OK;
}


void CParticleSystem::Spread(Vector2 _vDir, _double _timeDelta, _uint _iParticleCnt)
{
	if (m_bDead)
		return;


	/*
	1.퍼져나갈 각도를 정한다.
	2.파티클 갯수에 따라 그 각도로 퍼지기 위한 간격을 구한다.
	3.부채꼴이 시작할 위치를 구한다.
	4.간격을 더해가며 파티클을 생성한다.
	5.파티클을 각자의 방향으로 움직이게한다.
	6.부모인 파티클 시스템을 원하는 방향으로 회전한다.
	*/


	//부채꼴의 중간이 되는 각 구하기

	//x축
	Vector2 vFix = Vector3(1.f, 0.f, 0.f);

	_float cosTheta = D3DXVec4Dot(&vFix, &_vDir.Nomalize());

	//x축과 방향벡터의 사이각 == 부채꼴의 중간이 되는 각
	_float middle = 0.f;

	if (_vDir.y >= 0.f)
		middle = D3DXToDegree(acosf(cosTheta));
	else
		middle = D3DXToDegree(D3DX_PI * 2 - acosf(cosTheta));

	//퍼지는 각
	_float spreadAngle = 90.f;
	//총 퍼지는 각을 _iParticleCnt -1로 나눈 값 = 파티클 사이의 갭
	_float gap = _iParticleCnt > 1 ? spreadAngle / (float)(_iParticleCnt - 1) : 1;
	//시작하는 각
	_float startAngle = middle - (spreadAngle / 2);

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return;

	for (_uint i = 0; i < _iParticleCnt; ++i)
	{
		//파티클 생성
		CParticle::STATEDESC stateDesc;
		stateDesc.m_eTextureSceneID = m_tDesc.m_eTextureSceneID;
		stateDesc.m_fSpeed = m_tDesc.m_fSpeed;
		stateDesc.m_pTextureTag = m_tDesc.m_pTextureTag;
		stateDesc.m_tBaseDesc.vPos = m_tDesc.m_tBaseDesc.vPos;

		//0으로 나누면 안되니까
		m_tDesc.m_vParticleSize.x = m_tDesc.m_vParticleSize.x == 0 ? 1 : m_tDesc.m_vParticleSize.x;
		m_tDesc.m_vParticleSize.y = m_tDesc.m_vParticleSize.y == 0 ? 1 : m_tDesc.m_vParticleSize.y;
		//랜덤사이즈
		stateDesc.m_tBaseDesc.vSize = Vector2(_float(rand() % (_int)m_tDesc.m_vParticleSize.x), _float(rand() % (_int)m_tDesc.m_vParticleSize.y));


		m_listParticle.push_back(CParticle::Create(m_pGraphic_Device, stateDesc));

		//혹시나 0이 될 수 있으니까
		gap = gap == 0 ? 1 : gap;
		//랜덤갭
		_float currGap = _float(rand() % (_int)gap);
		//각도를 통해 파티클이 이동해야할 방향을 구한후 이동
		_float currAngle = startAngle + currGap * (float)i;
		Vector2 vDir = Vector2(cosf(D3DXToRadian(currAngle)), sinf(D3DXToRadian(currAngle)));
		CTransform* pParicleTransform = (CTransform*)m_listParticle.back()->Get_Module(L"Transform");
		if (nullptr == pParicleTransform)
			return;
		pParicleTransform->MoveToDirAuto(vDir);

	}

}

//_rc안의 랜덤한 장소에 파티클을 스폰한다.
void CParticleSystem::RollUp(RECT& _rc, _uint _iParticleCnt)
{
	if (m_bDead)
		return;


	if (nullptr == m_pObjMgr)
		return;

	//해당 범위 내에서 랜덤한 위치에 스폰한다. 파티클은 lifetime이 지나면 죽는다. 
	LONG SizeX = _rc.right - _rc.left;
	LONG SizeY = _rc.bottom - _rc.top;
	if (SizeX <= 0 || SizeY <= 0)
		return;


	for (_uint i = 0; i < _iParticleCnt; ++i)
	{

		_float randX = (_float)_rc.left + (rand() % SizeX);
		_float randY = (_float)_rc.top + (rand() % SizeY);
		CParticle::STATEDESC tParticleDesc = CreateParticleDesc();
		tParticleDesc.m_tBaseDesc.vPos = Vector2(randX, randY);
		tParticleDesc.m_dLifeTime = rand() / (_double)RAND_MAX * m_tDesc.m_dLifeTime;

		m_listParticle.push_back(CParticle::Create(m_pGraphic_Device, tParticleDesc));
	}

	////파티클의 부모를 파티클시스템으로 한다.
	for (auto& particle : m_listParticle)
	{
		if (nullptr == particle) return;
		CTransform* pParticleTransform = (CTransform*)particle->Get_Module(L"Transform");
		if (nullptr == pParticleTransform) return;

		pParticleTransform->Set_Parent(m_pTransform);
		pParticleTransform->MoveToDirAuto(Vector3(0.f, -1.f));
		pParticleTransform->Shrink_Auto(m_tDesc.m_vParticleSize);
		((CParticle*)particle)->Set_FadeOut();
	}

}


CParticleSystem * CParticleSystem::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CParticleSystem* pInstance = new CParticleSystem(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CParticleSystem");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CParticleSystem::Clone(void * _pArg)
{
	CParticleSystem* pInstance = new CParticleSystem(*this);
	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to create CParticleSystem");
		Safe_Release(pInstance);

	}

	return pInstance;
}

void CParticleSystem::OnDead()
{
	//파티클도 죽는다.
	for (auto& particle : m_listParticle)
	{
		particle->Set_Dead();
	}
}

CParticle::STATEDESC CParticleSystem::CreateParticleDesc()
{
	CParticle::STATEDESC tParticleDesc;
	tParticleDesc.m_eTextureSceneID = m_tDesc.m_eTextureSceneID;
	tParticleDesc.m_fSpeed = m_tDesc.m_fSpeed;
	tParticleDesc.m_pTextureTag = m_tDesc.m_pTextureTag;
	tParticleDesc.m_tBaseDesc.vPos = m_tDesc.m_tBaseDesc.vPos;
	tParticleDesc.m_tBaseDesc.vSize = m_tDesc.m_vParticleSize;
	tParticleDesc.m_dLifeTime = m_tDesc.m_dLifeTime;

	//트랩 타입에 따라 달라지게
	tParticleDesc.m_iTextureID = 1;
	return tParticleDesc;
}

void CParticleSystem::Free()
{
	Safe_Release(m_pShader);
	Safe_Release(m_pTexture);
	Safe_Release(m_pTransform);
	Safe_Release(m_pDeadClock);
	Safe_Release(m_pObjMgr);
	for (auto& particle : m_listParticle)
	{
		Safe_Release(particle);
	}

	CGameObject::Free();
}
