#include "stdafx.h"
#include "..\Headers\MyButton.h"
#include "Renderer.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "KeyMgr.h"
#include "Texture.h"
#include "Shader.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

USING(MyGame)

CMyButton::CMyButton(CMyButton & _rhs)
	: CGameObject(_rhs)
{

}

HRESULT CMyButton::Initialize(Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID)
{
	//슬롯에서 CMyButton::Itialize 이렇게하면 두번등록되버림
	m_eSceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
	//키매니저에 옵저버로 등록한다.
	CKeyMgr::Get_Instance()->RegisterObserver(m_eSceneID, this);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader);

	if (nullptr != _pTextureTag)
		Set_Module(_pTextureTag, _eTextureSceneID, (CModule**)&m_pTexture);

	m_pTransform->Set_Position(_vPos);
	m_pTransform->Set_Size(_vSize);

	return S_OK;
}

HRESULT CMyButton::Initialize(Vector4 _vPos, Vector2 _vSize, CTexture * _pTexture)
{
	//슬롯에서 CMyButton::Itialize 이렇게하면 두번등록되버림
	m_eSceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
	//키매니저에 옵저버로 등록한다.
	CKeyMgr::Get_Instance()->RegisterObserver(m_eSceneID, this);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader);

	m_pTexture = _pTexture;

	m_pTransform->Set_Position(_vPos);
	m_pTransform->Set_Size(_vSize);
	return S_OK;
}




_int CMyButton::Update(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pGraphic_Device)
		return -1;

	m_pTransform->Update_Transform();

	m_tRect = m_pTransform->Get_RECT();

	return m_bClicked ? OBJ_CLICKED : 0;
}

_int CMyButton::LateUpate(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI)))
		return -1;

	return 0;
}

HRESULT CMyButton::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTransform)
		return E_FAIL;


	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	ALPHABLEND;

	if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShader->Begin()))
		return E_FAIL;
	if (FAILED(m_pShader->Begin_Pass(m_eRenderState)))
		return E_FAIL;



	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;


	g_pFont->DrawText(NULL, m_pText, -1, &m_pTransform->Get_RECT(), DT_CENTER | DT_VCENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End()))
		return E_FAIL;


	ALPHABLEND_END;

	return S_OK;
}



HRESULT CMyButton::Set_RenderState(RENDER_STATE _eRenderState)
{
	if (STATE_END <= _eRenderState)
		return E_FAIL;

	m_eRenderState = _eRenderState;

	return S_OK;
}

HRESULT CMyButton::OnKeyDown(_int KeyCode)
{
	if (!m_bActive)
	{
		m_bClicked = false;
		return 0;
	}

	if (KeyCode == VK_LBUTTON)
	{
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		ScreenToClient(g_hWnd, &cursorPos);

		if (PtInRect(&m_tRect, cursorPos))
		{
			CSoundMgr::Get_Instance()->PlaySound_Overwrite(L"snd_click.mp3", CSoundMgr::UI);

			//리스너 목록을 호출한다.
			for (auto& listener : m_vecOnListener)
			{
				if (listener)
					listener();
			}
			//싱글 리스너를 호출한다.
			if (m_Listener)
				m_Listener();

			m_bClicked = true;
			return OBJ_CLICKED;
		}
	}

	m_bClicked = false;
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

CMyButton * CMyButton::Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, CTexture * _pTexture)
{
	CMyButton* pInstance = new CMyButton(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_vPos, _vSize, _pTexture)))
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

	CKeyMgr::Get_Instance()->UnRegisterObserver(m_eSceneID, this);

	Safe_Release(m_pShader);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);

	CGameObject::Free();

}

