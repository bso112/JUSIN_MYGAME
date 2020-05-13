#include "stdafx.h"
#include "ItemSlot.h"
#include "Item.h"
#include "KeyMgr.h"
#include "ItemInfoPanel.h"
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
	if (nullptr == _pItem)
		return E_FAIL;
	m_listItem.push_back(_pItem);
	return S_OK;
}

HRESULT CItemSlot::Set_Listener(function<void(CItemInfoPanel&, CItem*)> _listener, CItemInfoPanel* _pPanel)
{
	m_pSlotListener = _listener;
	m_pInfoPanel = _pPanel;
	Safe_AddRef(m_pInfoPanel);
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
	return CMyButton::Initialize(_vPos, _vSize, _pTextureTag, _eTextureSceneID);
}

_int CItemSlot::Update(_double _timeDelta)
{
	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pInfoPanel		||
		m_listItem.empty())
		return -1;

	m_pTransform->Late_Update();

	m_tRect = m_pTransform->Get_RECT();


	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		ScreenToClient(g_hWnd, &cursorPos);

		if (PtInRect(&m_tRect, cursorPos))
		{
			//버튼에 연결된 리스너를 호출한다.
			for (auto& listener : m_vecOnListener)
			{
				listener();
			}

			//아이템의 정보를 창에 띄워준다.
			m_pSlotListener(*m_pInfoPanel, m_listItem.back());

			return OBJ_CLICKED;
		}
	}


	//사용한 아이템을 체크해서 리스트에서 없앤다.
	if (m_listItem.back()->IsUsed())
	{
		Remove_Item();
	}

	return 0;
}

_int CItemSlot::LateUpate(_double _timeDelta)
{
	return CMyButton::LateUpate(_timeDelta);
}

HRESULT CItemSlot::Render()
{
	return CMyButton::Render();
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
	Safe_Release(m_pInfoPanel);
	for (auto& pItem : m_listItem)
	{
		Safe_Release(pItem);
	}

	CMyButton::Free();
}
