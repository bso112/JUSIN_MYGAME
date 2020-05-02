#include "stdafx.h"
#include "..\Headers\Rat.h"
#include "TextureLoader.h"
#include "Texture.h"


USING(MyGame)

CRat::CRat(CRat & _rhs)
	:CMonster(_rhs)
{
	memcpy(m_pTexture, _rhs.m_pTexture, sizeof(m_pTexture));
}

HRESULT CRat::Initialize_Prototype(_tchar * _pFilePath)
{
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Rat/");
	Set_Module(L"rat_att", SCENE_STAGE, (CModule**)&m_pTexture[ANIM_ATTACK]);
	Set_Module(L"rat_idle", SCENE_STAGE, (CModule**)&m_pTexture[ANIM_IDLE]);
	Set_Module(L"rat_dead", SCENE_STAGE, (CModule**)&m_pTexture[ANIM_DEAD]);
	Set_Module(L"rat_jump", SCENE_STAGE, (CModule**)&m_pTexture[ANIM_JUMP]);

	return S_OK;
}

HRESULT CRat::Initialize(void * _param)
{
		
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, &CTransform::STATEDESC(100.0, 100.0));
	
	if (nullptr != _param)
		m_pTransform->Set_Position(*((Vector3*)_param));

	m_pTransform->Set_Size(Vector2(20.f, 20.f));

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
		nullptr == m_pTexture[m_eCurrAnim] ||
		nullptr == m_pTransform)
		return E_FAIL;


	ALPHABLEND;

	if (FAILED(m_pTexture[m_eCurrAnim]->Set_Texture(m_iCurFrame)))
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
	for (auto& texture : m_pTexture)
	{
		Safe_Release(texture);
	}
	CMonster::Free();
}
