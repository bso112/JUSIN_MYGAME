#include "stdafx.h"
#include "ItemSlot.h"
#include "Item.h"
#include "KeyMgr.h"
#include "ItemInfoPanel.h"
#include "Food.h"
#include "SceneMgr.h"
USING(MyGame)

CItemSlot::CItemSlot(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CMyButton(_pGraphic_Device)
{
}

CItemSlot::CItemSlot(CItemSlot & _rhs)
	: CMyButton(_rhs)
{
}



HRESULT CItemSlot::Add_Item(CItem * _pItem)
{
	if (nullptr == _pItem ||
		m_pTransform == nullptr)
		return E_FAIL;

	_pItem->Set_Dead();
	CItem* clone = (CItem*)_pItem->Clone(&CFood::STATEDESC(BASEDESC(m_pTransform->Get_Position(), m_pTransform->Get_Size()), 10.f));
	m_listItem.push_back(clone);

	return S_OK;
}

HRESULT CItemSlot::Set_Listener(function<void(CItem*)> _listener)
{
	m_pSlotListener = _listener;
	return S_OK;
}

HRESULT CItemSlot::Remove_Item()
{
	if (m_listItem.empty())
		return E_FAIL;

	m_listItem.pop_back();

	return S_OK;
}

HRESULT CItemSlot::Initialize(Vector4 _vPos, Vector2 _vSize, _tchar * _pTextureTag, SCENEID _eTextureSceneID)
{
	m_bActive = false;

	m_eSceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
	//키매니저에 옵저버로 등록한다.
	CKeyMgr::Get_Instance()->RegisterObserver(m_eSceneID, this);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader);


	if (FAILED(Set_Module(L"slot", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_pTransform->Set_Position(_vPos);
	m_pTransform->Set_Size(_vSize);
	return S_OK;
}

_int CItemSlot::Update(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	//사용한 아이템을 체크해서 리스트에서 없앤다.
	if (!m_listItem.empty() && m_listItem.back()->IsUsed())
	{
		Remove_Item();
	}

	return 0;
}

_int CItemSlot::LateUpate(_double _timeDelta)
{
	if (!m_bActive)
		return 0;
	if (nullptr == m_pRenderer)
		return -1;

	m_pTransform->Update_Transform();
	
	
	if (!m_listItem.empty())
		m_listItem.front()->LateUpate(_timeDelta);

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI)))
		return -1;

	return S_OK;
}

HRESULT CItemSlot::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTransform)
		return E_FAIL;


	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	ALPHABLEND;

	if (FAILED(m_pTexture->Set_Texture(0)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	if (m_listItem.size() > 0)
		m_listItem.front()->Render();

	ALPHABLEND_END;

	return S_OK;
}

HRESULT CItemSlot::OnKeyDown(_int KeyCode)
{
	if (!m_bActive)
		return 0;

	if (KeyCode == VK_LBUTTON)
	{
		m_tRect = m_pTransform->Get_RECT();

		POINT cursorPos;
		GetCursorPos(&cursorPos);
		ScreenToClient(g_hWnd, &cursorPos);

		if (PtInRect(&m_tRect, cursorPos))
		{
			if (!m_listItem.empty())
			{
				//버튼에 연결된 리스너를 호출한다.
				for (auto& listener : m_vecOnListener)
				{
					//callable이면
					if (listener)
						listener();
				}


				//callable이면 아이템의 정보를 창에 띄워준다.
				if (m_pSlotListener)
					m_pSlotListener(m_listItem.back());
			}
			return OBJ_CLICKED;
		}
	}
	return S_OK;
}

CItemSlot * CItemSlot::Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID)
{
	CItemSlot* pInstance = new CItemSlot(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_vPos, _vSize, _pTextureTag, _eTextureSceneID)))
	{
		MSG_BOX("Fail to create CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
}



void CItemSlot::Free()
{
	if (FAILED(CKeyMgr::Get_Instance()->UnRegisterObserver(m_eSceneID, this)))
		MSG_BOX("Fail to Unregister slot");

	for (auto& pItem : m_listItem)
	{
		Safe_Release(pItem);
	}

	CMyButton::Free();
}
