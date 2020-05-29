#include "stdafx.h"
#include "..\Headers\TargetMgr.h"


USING(MyGame)
IMPLEMENT_SINGLETON(CTargetMgr)
CTargetMgr::CTargetMgr()
{
}


HRESULT CTargetMgr::Set_RenderTarget(const _tchar * _pTag, _uint _iIndex)
{
	CTarget* pTarget = Find_Target(_pTag);
	if (nullptr == pTarget)
		return E_FAIL;

	return pTarget->Set_RenderTarget(_iIndex);
}

HRESULT CTargetMgr::Release_RenderTarget(const _tchar * _pTag)
{
	CTarget* pTarget = Find_Target(_pTag);
	if (nullptr == pTarget)
		return E_FAIL;

	return pTarget->Release_RederTarget();
}

HRESULT CTargetMgr::Add_RenderTarget(PDIRECT3DDEVICE9 pGraphic_Device, const _tchar * _pTag, _int iCX, _int iCY, D3DFORMAT _eFormat)
{
	if (nullptr != Find_Target(_pTag))
		return E_FAIL;

	CTarget* pTarget = CTarget::Create(pGraphic_Device, iCX, iCY, _eFormat);
	if (nullptr == pTarget)
		return E_FAIL;
	m_mapTarget.emplace(_pTag,pTarget);

	return S_OK;
}

HRESULT CTargetMgr::Clear_RenderTarget(const _tchar * _pTag)
{
	CTarget* pTarget = Find_Target(_pTag);
	if (nullptr == pTarget)
		return E_FAIL;

	return pTarget->Clear_RenderTarget();
}

CTarget* CTargetMgr::Find_Target(const _tchar * _pTag)
{
	auto& iter = find_if(m_mapTarget.begin(), m_mapTarget.end(), CFinder_Tag(_pTag));
	if (iter == m_mapTarget.end())
		return nullptr;

	return (*iter).second;
}

LPDIRECT3DTEXTURE9 CTargetMgr::Get_Texture(const _tchar * _pTag)
{
	CTarget* pTarget = Find_Target(_pTag);
	if (nullptr == pTarget)
		return nullptr;

	return 	pTarget->Get_Texture();
}

void CTargetMgr::Free()
{
	for (auto& pair : m_mapTarget)
	{
		Safe_Release(pair.second);
	}
	m_mapTarget.clear();
}

