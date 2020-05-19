#include "stdafx.h"
#include "..\Headers\Monster.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "Animator.h"
#include "Shader.h"

USING(MyGame)

CMonster::CMonster(CMonster & _rhs)
	:CCharacter(_rhs)
{
	SCENEID eSceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
	m_pFocus = (CCharacter*)CObjMgr::Get_Instance()->Get_Player(eSceneID);
}

_int CMonster::Update(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	m_pTransform->Update_Route(_timeDelta);

	return 0;
}

_int CMonster::LateUpate(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	m_pTransform->Update_Transform();

	if (nullptr == m_pRenderer)
		return E_FAIL;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT)))
		return E_FAIL;


	return 0;
}

HRESULT CMonster::Render()
{
	if (nullptr == m_pVIBuffer ||
		nullptr == m_pAnimator ||
		nullptr == m_pTransform ||
		nullptr == m_pShader)
		return E_FAIL;

	if (!m_bActive)
		return 0;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix())))
		return E_FAIL;

	ALPHABLEND;

	if (FAILED(m_pAnimator->Render(m_pShader)))
		return E_FAIL;


	if (FAILED(m_pShader->Begin()))
		return E_FAIL;

	if (FAILED(m_pShader->Begin_Pass(m_iPass)))
		return E_FAIL;

	//반짝거리는 거였으면 원상복귀
	if (m_iPass == 3)
		m_iPass = 0;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;


	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End()))
		return E_FAIL;


	ALPHABLEND_END;

	//콜라이더 렌더
	m_pTransform->Render_Collider();


	return S_OK;
}

_float CMonster::CalulateSpeed(_int movePerturn)
{
	if (nullptr == m_pFocus)
		return -1.f;

	CTransform*	pHeroTransform = (CTransform*)m_pFocus->Get_Module(L"Transform");
	if (nullptr == pHeroTransform) 
		return -1.f;

	return pHeroTransform->Get_Desc().speedPerSec;

}

HRESULT CMonster::OnRender()
{
	return S_OK;
}

void CMonster::Free()
{
	Safe_Release(m_pAnimator);
	CCharacter::Free();
}
