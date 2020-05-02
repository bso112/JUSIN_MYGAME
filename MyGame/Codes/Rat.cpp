#include "stdafx.h"
#include "..\Headers\Rat.h"
#include "TextureLoader.h"
#include "Texture.h"

USING(MyGame)

CRat::CRat(CRat & _rhs)
	:CMonster(_rhs)
{

}

HRESULT CRat::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Rat/");

	return S_OK;
}

HRESULT CRat::Initialize(void * _param)
{
		
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, &CTransform::STATEDESC(100.0, 100.0));

	if (nullptr != _param)
		m_pTransform->Set_Position(*((Vector3*)_param));

	m_pTransform->Set_Size(Vector2(20.f, 20.f));


	Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator);

	CTexture* pTexture = nullptr;
	Set_Module(L"rat_att", SCENE_STAGE, (CModule**)&pTexture);
	m_pAnimator->Add_Animation(L"attack", CAnimation::Create(pTexture, 0.2, false));
	Set_Module(L"rat_idle", SCENE_STAGE, (CModule**)&pTexture);
	m_pAnimator->Add_Animation(L"idle", CAnimation::Create(pTexture, 0.2, true));
	Set_Module(L"rat_dead", SCENE_STAGE, (CModule**)&pTexture);
	m_pAnimator->Add_Animation(L"dead", CAnimation::Create(pTexture, 0.2, false));
	Set_Module(L"rat_jump", SCENE_STAGE, (CModule**)&pTexture);
	m_pAnimator->Add_Animation(L"jump", CAnimation::Create(pTexture, 0.2, true));
	return S_OK;
}

_int CRat::Update(_double _timeDelta)
{
	
	m_pTransform->Update(_timeDelta);
	return _int();
}

_int CRat::LateUpate(_double _timeDelta)
{
	m_pTransform->Late_Update();
	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT)))
		return -1;

	return 0;
}

HRESULT CRat::Render()
{
	if (nullptr == m_pVIBuffer ||
		nullptr == m_pAnimator ||
		nullptr == m_pTransform)
		return E_FAIL;


	ALPHABLEND;

	if (FAILED(m_pAnimator->Play(L"idle")))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	ALPHABLEND_END;

	return S_OK;
}

CRat * CRat::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CRat* pInstance = new CRat(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CRat");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CRat::Clone(void * _param)
{
	CRat* pInstance = new CRat(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CRat");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CRat::Process()
{
}

void CRat::Update_State()
{
}

void CRat::OnDead()
{
}

void CRat::OnTakeDamage()
{
}

void CRat::Scene_Change()
{
}

void CRat::Free()
{
	Safe_Release(m_pAnimator);
	CMonster::Free();
}
