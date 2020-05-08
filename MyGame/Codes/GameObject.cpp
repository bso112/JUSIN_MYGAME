#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ModuleMgr.h"

USING(MyGame)

CGameObject::CGameObject(PDIRECT3DDEVICE9 _pGrahic_Device)
	:m_pGraphic_Device(_pGrahic_Device), m_pRenderer(CRenderer::Get_Instance())
{
	Safe_AddRef(m_pRenderer);
	Safe_AddRef(m_pGraphic_Device);


};



CGameObject::CGameObject(CGameObject & _rhs)
	:m_pGraphic_Device(_rhs.m_pGraphic_Device), m_pRenderer(CRenderer::Get_Instance())
{
	Safe_AddRef(m_pRenderer);
	Safe_AddRef(m_pGraphic_Device);
}



HRESULT CGameObject::Initialize_Prototype(_tchar * _pFilePath)
{
	return S_OK;
}

HRESULT CGameObject::Initialize(void * _param)
{
	return S_OK;
}

_int CGameObject::Update(_double _timeDelta)
{
	return _int();
}

_int CGameObject::LateUpate(_double _timeDelta)
{
	return _int();
}

HRESULT CGameObject::Act(_int _iTurnCnt)
{
	return S_OK;
}

HRESULT CGameObject::Render()
{
	return S_OK;
}

void CGameObject::OnCollisionEnter(CGameObject * _pOther)
{
}

void CGameObject::OnCollisionStay(CGameObject * _pOther)
{
}

void CGameObject::OnCollisionExit(CGameObject * _pOther)
{
}


HRESULT CGameObject::Set_Module(const _tchar* _pPrototypeModuleTag, SCENEID _eSceneID, CModule** _ppOut, const _tchar* _pModuleTag, void* _pArg)
{
	//따로 모듈이름 지정안하면 프로토타입 태그와 같은 태그로 모듈을 저장한다.
	if (_pModuleTag == nullptr)
		_pModuleTag = _pPrototypeModuleTag;

	if (nullptr != Get_Module(_pModuleTag))
		return E_FAIL;

	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;

	Safe_AddRef(pModuleMgr);

	*_ppOut = pModuleMgr->Get_Module(_pPrototypeModuleTag, _eSceneID, _pArg);
	if (nullptr == *_ppOut)
		return E_FAIL;


	m_mapModule.emplace(_pModuleTag, *_ppOut);
	//map에 추가했으니까 AddRef
	Safe_AddRef(*_ppOut);

	Safe_Release(pModuleMgr);

	return S_OK;
}

CModule * CGameObject::Get_Module(const _tchar* _eModuleTag)
{
	auto& iter = find_if(m_mapModule.begin(), m_mapModule.end(), CFinder_Tag(_eModuleTag));
	if (iter == m_mapModule.end())
		return nullptr;
	
	return iter->second;
}

void CGameObject::Free()
{
	
	for (auto pair : m_mapModule)
	{
		Safe_Release(pair.second);
	}

	Safe_Release(m_pRenderer);
	Safe_Release(m_pGraphic_Device);

}
