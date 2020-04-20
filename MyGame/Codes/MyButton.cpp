#include "stdafx.h"
#include "..\Headers\MyButton.h"
#include "Renderer.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Texture.h"
USING(MyGame)

CMyButton::CMyButton(CMyButton & _rhs)
	: CGameObject(_rhs)
{


}

HRESULT CMyButton::Initialize(Vector4 _vPos, Vector2 _vSize, CMyButton::TAG _eTag, _tchar* _pTextureTag)
{
	Set_Module(L"Transform", SCENEID::SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENEID::SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(_pTextureTag, SCENEID::SCENE_STATIC, (CModule**)&m_pTexture);

	m_pTransform->Set_Position(_vPos);
	m_pTransform->Set_Size(_vSize);
	m_tRect = m_pTransform->Get_Rect();

	m_eBtnTag = _eTag;

	return S_OK;
}



_int CMyButton::Update(_double _timeDelta)
{
	if (nullptr == m_pGraphic_Device)
		return -1;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		ScreenToClient(g_hWnd, &cursorPos);

		if (PtInRect(&m_tRect, cursorPos))
		{
			CSceneMgr* pSceneMgr = CSceneMgr::Get_Instance();
			if (nullptr == pSceneMgr)
				return -1;

			switch (m_eBtnTag)
			{
			case MyGame::CMyButton::BTN_CHARACTER_SELECT:
			{
				pSceneMgr->Scene_Change(SCENEID::SCENE_CHARACTER_SELECT, m_pGraphic_Device);
				break;
			}
			case MyGame::CMyButton::BTN_GAMESATART:
			{
				pSceneMgr->Scene_Change(SCENEID::SCENE_STAGE, m_pGraphic_Device);
				break;
			}
			}
		}

	}
	return 0;
}

HRESULT CMyButton::Render()
{
	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTexture ||
		nullptr == m_pTransform)
		return E_FAIL;

	if (FAILED(m_pTexture->Set_Texture(0)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;
	return S_OK;
}

CMyButton * CMyButton::Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, CMyButton::TAG _eTag, _tchar* _pTextureTag)
{
	CMyButton* pInstance = new CMyButton(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_vPos, _vSize, _eTag, _pTextureTag)))
	{
		MSG_BOX("Fail to create Background");
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

