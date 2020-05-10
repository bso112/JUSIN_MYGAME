#include "stdafx.h"
#include "Renderer.h"
#include "GameObject.h"

USING(MyGame)

IMPLEMENT_SINGLETON(CRenderer)
CRenderer::CRenderer()
{
}


CRenderer::~CRenderer()
{
}

HRESULT CRenderer::Add_To_RenderGrop(CGameObject * _obj, RENDER_GROUP _eGroup)
{
	if (nullptr == _obj ||
		RENDER_END <= _eGroup)
		return E_FAIL;

	m_listGO[_eGroup].push_back(_obj);
	Safe_AddRef(_obj);
	
	return S_OK;
}

HRESULT CRenderer::Render()
{
	if (FAILED(Render_Prior()))
		return E_FAIL;

	if (FAILED(Render_YSort()))
		return E_FAIL;

	if (FAILED(Render_UI()))
		return E_FAIL;



	return S_OK;
}



HRESULT CRenderer::Clear_RenderGroup()
{
	for (size_t i = 0; i < RENDER_END; i++)
	{
		for (CGameObject* pGameObject : m_listGO[i])
				Safe_Release(pGameObject);

		m_listGO[i].clear();
	}
	return S_OK;
}

HRESULT CRenderer::Render_Prior()
{
	for (auto& GO : m_listGO[RENDER_PRIOR])
	{
		if (nullptr != GO)
		{
			if (FAILED(GO->Render()))
				return E_FAIL;
		}

		Safe_Release(GO);
	}
	m_listGO[RENDER_PRIOR].clear();
	return S_OK;
}

HRESULT CRenderer::Render_YSort()
{
	for (auto& GO : m_listGO[RENDER_YSORT])
	{
		if (nullptr != GO)
		{
			if (FAILED(GO->Render()))
				return E_FAIL;
		}

		Safe_Release(GO);
	}
	m_listGO[RENDER_YSORT].clear();
	return S_OK;
}

HRESULT CRenderer::Render_UI()
{
	for (auto& GO : m_listGO[RENDER_UI])
	{
		if (nullptr != GO)
		{
			if (FAILED(GO->Render()))
				return E_FAIL;
		}

		if (0 == Safe_Release(GO))
			MSG_BOX("GameObject Removed on Renderer");
	}
	m_listGO[RENDER_UI].clear();
	return S_OK;
}

void CRenderer::Free()
{
	for (auto& list : m_listGO)
	{
		for (auto& GO : list)
			Safe_Release(GO);

		list.clear();
	}
}
