#include "stdafx.h"
#include "..\Headers\Food.h"
USING(MyGame)


CFood::CFood(CFood & _rhs)
	:CItem(_rhs)
{
	ZeroMemory(&m_tDesc, sizeof(STATEDESC));

}

HRESULT CFood::Initialize_Prototype(_tchar* _pFilePath)
{

	return S_OK;
}

HRESULT CFood::Initialize(void * _param)
{
	if (nullptr != _param)
		memcpy(&m_tDesc, _param, sizeof(STATEDESC));

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Texture_Food", SCENE_STAGE, (CModule**)&m_pTexture);

	m_pTransform->Set_Position(m_tDesc.tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.tBaseDesc.vSize);

	return S_OK;
}

_int CFood::Update(_double _timeDelta)
{
	if (nullptr == m_pTransform)
		return -1;

	m_pTransform->Update(_timeDelta);
	return _int();
}

_int CFood::LateUpate(_double _timeDelta)
{
	if (nullptr == m_pTransform)
		return -1;

	m_pTransform->Late_Update();
	m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT);
	return 0;
}

HRESULT CFood::Render()
{
	if (nullptr == m_pTexture ||
		nullptr == m_pVIBuffer ||
		nullptr == m_pTransform)
		return E_FAIL;
	
	ALPHABLEND;

	if (FAILED(m_pTexture->Set_Texture(m_tDesc.iTextureID  -1)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	ALPHABLEND_END;

	return S_OK;
}

CFood * CFood::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CFood* pInstance = new CFood(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CFood");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject * CFood::Clone(void * _param)
{
	CFood* pInstance = new CFood(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CFood");
		Safe_Release(pInstance);

	}
	return pInstance;
}

vector<const _tchar*>* CFood::Get_Actions()
{
	vector<const _tchar*>* actions = CItem::Get_Actions();
	actions->push_back(AC_EAT);
	return actions;
}

HRESULT CFood::Use(CHero * _pHero, const _tchar * _pAction)
{
	if (FAILED(CItem::Use(_pHero, _pAction)))
		return E_FAIL;

	if (0 == lstrcmp(_pAction, AC_EAT))
	{
		//¸Ô±â

	}

	return S_OK;
}

void CFood::Free()
{
	CItem::Free();
}
