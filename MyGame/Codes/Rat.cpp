#include "stdafx.h"
#include "..\Headers\Rat.h"


USING(MyGame)

HRESULT CRat::Initialize_Prototype(_tchar * _pFilePath)
{
	return S_OK;
}

HRESULT CRat::Initialize(void * _param)
{
	return S_OK;
}

_int CRat::Update(_double _timeDelta)
{
	return _int();
}

_int CRat::LateUpate(_double _timeDelta)
{
	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT)))
		return -1;

	return 0;
}

HRESULT CRat::Render()
{

	return S_OK;
}

CRat * CRat::Create()
{
	return nullptr;
}

CGameObject * CRat::Clone(void * _param)
{
	CRat* pInstance = new CRat(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create Background");
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
