#include "stdafx.h"
#include "..\Headers\Monster.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "Animator.h"
#include "Shader.h"
#include "Clock.h"
#include "DialogMgr.h"
#include "HpBar.h"
USING(MyGame)

CMonster::CMonster(CMonster & _rhs)
	:CCharacter(_rhs)
{
	SCENEID eSceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
	m_pFocus = (CCharacter*)CObjMgr::Get_Instance()->Get_Player(eSceneID);

	//멤버변수 셋팅
	m_iRecogRange = 15;
	m_iAttackRange = 1;
	

}

HRESULT CMonster::Initialize(void * _param)
{
	if (nullptr == m_pTransform)
		return E_FAIL;

	

	//Hp바 셋팅
	m_pHpBar = CHpBar::Create(m_pGraphic_Device, m_pTransform->Get_Position(), Vector2(30.f, 5.f), L"hp_bar_monster", SCENE_STAGE);
	m_pHpBar->Set_UI(false);
	m_pHpBar->Set_Owner(this);
	CTransform* pTransform = (CTransform*)m_pHpBar->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return E_FAIL;
	pTransform->Set_Parent(m_pTransform);
	pTransform->Set_Position(Vector2(0.f, -15.f));
	CObjMgr::Get_Instance()->Add_GO_To_Layer(L"UI", SCENE_STAGE, m_pHpBar);

	//이거 하면 릭남
	//Safe_AddRef(m_pHpBar);
	return S_OK;
}

_int CMonster::Update(_double _timeDelta)
{

	if (m_bDying)
	{
		if (nullptr == m_pDeadClock)
			m_bDead = true;

		if (m_pDeadClock->isThreashHoldReached(3.0))
			m_bDead = true;

		return 0;
	}
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

#ifdef MYDEBUG
	//콜라이더 렌더
	m_pTransform->Render_Collider();
#endif // MYDEBUG


	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End()))
		return E_FAIL;


	ALPHABLEND_END;



	return S_OK;
}

_float CMonster::CalulateSpeed(_int movePerturn)
{
	if (nullptr == m_pFocus)
		return -1.f;

	CTransform*	pHeroTransform = (CTransform*)m_pFocus->Get_Module(L"Transform");
	if (nullptr == pHeroTransform)
		return -1.f;

	return (_float)pHeroTransform->Get_Desc().speedPerSec;

}

HRESULT CMonster::OnRender()
{
	return S_OK;
}

void CMonster::OnDead()
{
	CDialogMgr::Get_Instance()->Log_Main(MSG_WIN(m_pName));
}

void CMonster::OnAttack(CGameObject * _pOther)
{
	if (nullptr == _pOther ||
		nullptr == m_pAnimator)
		return;

	//m_pAnimator->Play(L"attack");
}

void CMonster::Free()
{
	//Safe_Release(m_pHpBar);
	Safe_Release(m_pAnimator);
	CCharacter::Free();
}
