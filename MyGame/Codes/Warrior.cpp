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
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"warrior_naked_attack", SCENE_STAGE, (CModule**)&m_pTexture[ANIM_ATTACK]);
	Set_Module(L"warrior_naked_eat", SCENE_STAGE, (CModule**)&m_pTexture[ANIM_EAT]);
	Set_Module(L"warrior_naked_floating", SCENE_STAGE, (CModule**)&m_pTexture[ANIM_FLOATING]);
	Set_Module(L"warrior_naked_idle", SCENE_STAGE, (CModule**)&m_pTexture[ANIM_IDLE]);
	Set_Module(L"warrior_naked_use", SCENE_STAGE, (CModule**)&m_pTexture[ANIM_USE]);
	Set_Module(L"warrior_naked_walk", SCENE_STAGE, (CModule**)&m_pTexture[ANIM_WALK]);

	m_pTransform->Set_Position(Vector3((_float)(g_iWinCX >> 1), (_float)(g_iWinCY >> 1)));
	m_pTransform->Set_Size(Vector3(100.f, 100.f));

	return S_OK;
}

HRESULT CWarrior::KeyCheck()
{
	CHero::KeyCheck();

	return S_OK;
}

_int CWarrior::Update(_double _timeDelta)
{
	//목적지가 있을 경우 목적지로 이동
	MoveToDst(m_vDst, _timeDelta);

	return 0;
}

_int CWarrior::LateUpate(_double _timeDelta)
{
	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT)))
		return -1;

	return 0;
}

HRESULT CWarrior::Render()
{
	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTexture[m_eCurrAnim] ||
		nullptr == m_pTransform)
		return E_FAIL;


	ALPHABLEND;

	if (FAILED(m_pTexture[m_eCurrAnim]->Set_Texture(0)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	return S_OK;
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
	for (auto& texture : m_pTexture)
	{
		Safe_Release(texture);
	}
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);

	CHero::Free();
}

