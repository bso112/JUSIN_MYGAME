#include "stdafx.h"
#include "..\Headers\Target.h"

USING(MyGame)

CTarget::CTarget(PDIRECT3DDEVICE9 _pGraphic_Device)
	:m_pGraphic_Device(_pGraphic_Device) 
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CTarget::Initialize(_int iCX, _int iCY, D3DFORMAT _eFormat)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	if(FAILED(D3DXCreateTexture(m_pGraphic_Device,iCX, iCY, 1, D3DUSAGE_RENDERTARGET, _eFormat, D3DPOOL_DEFAULT, &m_pTexture)))
		return E_FAIL;
	
	//렌더타겟을 얻어온다.
	m_pTexture->GetSurfaceLevel(0, &m_pSurface);

	return S_OK;
}

HRESULT CTarget::Set_RenderTarget(_uint _iIndex)
{
	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pSurface)
		return E_FAIL;

	//현재 장치의 _iIndex에 있는 렌더타겟을 가져오기.(임시대피)
	m_pGraphic_Device->GetRenderTarget(_iIndex, &m_pOldSurface);
	//장치의 _iIndex 슬롯에 렌더타겟 셋팅
	m_pGraphic_Device->SetRenderTarget(_iIndex, m_pSurface);
	//셋팅한 렌더타겟의 인덱스 저장
	m_iRenderTargetIndex = _iIndex;
	return S_OK;
}

HRESULT CTarget::Release_RederTarget()
{
	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pSurface)
		return E_FAIL;

	m_pGraphic_Device->SetRenderTarget(m_iRenderTargetIndex, m_pOldSurface);
	//임시대피시킬때 레퍼런스카운트 올라갔어서 여기서 낮춰준다.
	Safe_Release(m_pOldSurface);

	if (GetKeyState(VK_RETURN) < 0)
	{
		D3DXSaveTextureToFile(L"../Bin/Gara.jpg", D3DXIFF_PNG, m_pTexture, nullptr);
	}

	return S_OK;
}

HRESULT CTarget::Clear_RenderTarget()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	//렌더타겟을 모두 클리어한다.
	m_pGraphic_Device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 1.f, 0);
	return S_OK;
}

CTarget * CTarget::Create(PDIRECT3DDEVICE9 _pGraphic_Device, _int iCX, _int iCY, D3DFORMAT _eFormat)
{
	CTarget* pInstance = new CTarget(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(iCX, iCY, _eFormat)))
	{
		MSG_BOX("Fail to create CTarget");
		Safe_Release(pInstance);

	}
	return pInstance;
}
void CTarget::Free()
{
	Safe_Release(m_pOldSurface);
	Safe_Release(m_pSurface);
	Safe_Release(m_pTexture);
	Safe_Release(m_pGraphic_Device);
}
