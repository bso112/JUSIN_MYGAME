#include "stdafx.h"
#include "..\Headers\MyButton.h"
#include "Renderer.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "KeyMgr.h"
#include "Texture.h"
USING(MyGame)

CMyButton::CMyButton(CMyButton & _rhs)
	: CGameObject(_rhs)
{


}

HRESULT CMyButton::Initialize(Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID)
{
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);

	if (nullptr != _pTextureTag)
		Set_Module(_pTextureTag, _eTextureSceneID, (CModule**)&m_pTexture);

	m_pTransform->Set_Position(_vPos);
	m_pTransform->Set_Size(_vSize);

	return S_OK;
}



_int CMyButton::Update(_double _timeDelta)
{
	if (nullptr == m_pGraphic_Device)
		return -1;

	m_pTransform->Update();

	m_tRect = m_pTransform->Get_Rect();
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		ScreenToClient(g_hWnd, &cursorPos);

		if (PtInRect(&m_tRect, cursorPos))
		{
			for (auto& listener : m_vecOnListener)
			{
				listener();
			}
		}
	}

	return 0;
}

_int CMyButton::LateUpate(_double _timeDelta)
{
	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI)))
		return -1;

}

HRESULT CMyButton::Render()
{
	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTransform)
		return E_FAIL;

	if (nullptr != m_pTexture)
	{
		if (FAILED(m_pTexture->Set_Texture(0)))
			return E_FAIL;

	}


	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	g_pFont->DrawText(NULL, m_pText, -1, &m_pTransform->Get_Rect(), DT_CENTER | DT_VCENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

HRESULT CMyButton::Add_Listener(function<void()> _listener)
{
	m_vecOnListener.push_back(_listener);
	return S_OK;
}

CMyButton * CMyButton::Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID)
{
	CMyButton* pInstance = new CMyButton(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_vPos, _vSize, _pTextureTag, _eTextureSceneID)))
	{
		MSG_BOX("Fail to create CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
}


CGameObject * CMyButton::Clone(void * _arg)
{
	return nullptr;
}

void CMyButton::Free()
{
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);

	CGameObject::Free();

}

