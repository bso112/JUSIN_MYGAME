#include "stdafx.h"
#include "..\Headers\Warrior.h"
#include "Renderer.h"
#include "Texture.h"
#include "Transform.h"
#include "VIBuffer.h"
USING(MyGame)


CWarrior::CWarrior(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CHero(_pGraphic_Device) 
{
	ZeroMemory(m_pTexture, sizeof(m_pTexture));
};

CWarrior::CWarrior(CWarrior & _hero)
	: CHero(_hero)
{
	memcpy(m_pTexture, _hero.m_pTexture, sizeof(m_pTexture));
}

CWarrior * CWarrior::Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar * _pFilePath)
{
	CWarrior* pInstance = new CWarrior(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CWarrior");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CWarrior::Clone(void * _param)
{
	CWarrior* pInstance = new CWarrior(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CWarrior");
		Safe_Release(pInstance);

	}
	return pInstance;
}


HRESULT CWarrior::Initialize_Prototype(_tchar * _pFilePath)
{	

	return S_OK;
}

HRESULT CWarrior::Initialize(void * _param)
{


	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, &CTransform::STATEDESC(100.f, 100.f));


	Set_Module(L"warrior_naked_idle", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_NAKED][ANIM_IDLE]);
	Set_Module(L"warrior_naked_attack", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_NAKED][ANIM_ATTACK]);
	Set_Module(L"warrior_naked_eat", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_NAKED][ANIM_EAT]);
	Set_Module(L"warrior_naked_floating", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_NAKED][ANIM_FLOATING]);
	Set_Module(L"warrior_naked_use", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_NAKED][ANIM_USE]);
	Set_Module(L"warrior_naked_walk", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_NAKED][ANIM_WALK]);

	Set_Module(L"warrior_cloth_idle", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_BASIC][ANIM_IDLE]);
	Set_Module(L"warrior_cloth_attack", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_BASIC][ANIM_ATTACK]);
	Set_Module(L"warrior_cloth_eat", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_BASIC][ANIM_EAT]);
	Set_Module(L"warrior_cloth_floating", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_BASIC][ANIM_FLOATING]);
	Set_Module(L"warrior_cloth_use", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_BASIC][ANIM_USE]);
	Set_Module(L"warrior_cloth_walk", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_BASIC][ANIM_WALK]);

	Set_Module(L"warrior_leather_idle", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_LEATHER][ANIM_IDLE]);
	Set_Module(L"warrior_leather_attack", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_LEATHER][ANIM_ATTACK]);
	Set_Module(L"warrior_leather_eat", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_LEATHER][ANIM_EAT]);
	Set_Module(L"warrior_leather_floating", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_LEATHER][ANIM_FLOATING]);
	Set_Module(L"warrior_leather_use", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_LEATHER][ANIM_USE]);
	Set_Module(L"warrior_leather_walk", SCENE_STAGE, (CModule**)&m_pTexture[CLOTH_LEATHER][ANIM_WALK]);

	m_pTransform->Set_Position(Vector3((_float)(g_iWinCX >> 1), (_float)(g_iWinCY >> 1)));
	m_pTransform->Set_Size(Vector3(20.f, 25.f));

	return S_OK;
}

HRESULT CWarrior::KeyCheck(_double _timeDelta)
{
	CHero::KeyCheck(_timeDelta);

	return S_OK;
}

_int CWarrior::Update(_double _timeDelta)
{
	KeyCheck(_timeDelta);
	m_pTransform->Update(_timeDelta);
	return 0;
}

_int CWarrior::LateUpate(_double _timeDelta)
{	
	m_pTransform->Late_Update();

	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT)))
		return -1;

	return 0;
}

HRESULT CWarrior::Render()
{
	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTexture[m_eCurrCloth][m_eCurrAnim] ||
		nullptr == m_pTransform)
		return E_FAIL;


	ALPHABLEND;

	if (FAILED(m_pTexture[m_eCurrCloth][m_eCurrAnim]->Set_Texture(m_iCurFrame)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	ALPHABLEND_END;

	return S_OK;
}


void CWarrior::OnCollisionEnter(CGameObject * _pOther)
{

}

void CWarrior::Scene_Change()
{
}

void CWarrior::Process()
{
}

void CWarrior::Update_State()
{
}

void CWarrior::OnDead()
{
}

void CWarrior::OnTakeDamage()
{
}

void CWarrior::Free()
{

	for (int i = 0; i < CLOTH_END; ++i)
	{
		for (int j = 0; j < ANIM_END; ++j)
		{
			Safe_Release(m_pTexture[i][j]);
		}
	}

	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);

	CHero::Free();
}

