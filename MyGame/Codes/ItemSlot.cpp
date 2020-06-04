#include "stdafx.h"
#include "ItemSlot.h"
#include "Item.h"
#include "KeyMgr.h"
#include "ItemInfoPanel.h"
#include "Food.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "Spawner.h"
#include "LevelMgr.h"
#include "Hero.h"
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

	//처음 먹으면 슬롯에 들어가니까 안보여야됨.
	_pItem->Set_Active(false);
	CTransform* pTransform = (CTransform*)_pItem->Get_Module(L"Transform");
	RETURN_FAIL_IF_NULL(pTransform);
	pTransform->Set_Position(m_pTransform->Get_Position());
	pTransform->Set_Size(Vector2(CONTENTX, CONTENTY));
	m_listItem.push_back(_pItem);
	Safe_AddRef(_pItem);

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

	//아이템 없애기
	CItem* pItem = m_listItem.back();
	pItem->Set_Dead();
	Safe_Release(pItem);
	m_listItem.pop_back();

	return S_OK;
}

HRESULT CItemSlot::Drop_Item()
{
	if (m_listItem.empty())
		return E_FAIL;

	CItem* pItem = m_listItem.back();

	CTransform* pItemTransform = (CTransform*)pItem->Get_Module(L"Transform");
	if (nullptr == pItemTransform) return E_FAIL;

	CGameObject* pPlayer = CObjMgr::Get_Instance()->Get_Player(SCENE_STAGE);
	if (nullptr == pPlayer)
		return E_FAIL;

	CTransform* pPlayerTransform = (CTransform*)pPlayer->Get_Module(L"Transform");
	if (nullptr == pPlayerTransform)
		return E_FAIL;

	//아이템을 플레이어 위치에 둔다.
	pItem->Drop(pPlayerTransform->Get_Position());
	//참조를 감소시킨다.
	Safe_Release(pItem);
	//리스트에서 없앤다.
	m_listItem.pop_back();
	return S_OK;
}

void CItemSlot::Equip(CItem* _pItem)
{
	//만약 아이템이 이미 있다면 해제
	UnEquip();
	//아이템 리스트를 비운다. (장비슬롯은 하나의 아이템만 가진다)
	Clear();
	//아이템을 추가한다.
	Add_Item(_pItem);
}

CItem * CItemSlot::UnEquip()
{
	if (m_listItem.size() <= 0)
		return nullptr;

	//클리어 하기 전에 가지고 있던 아이템을 반환한다.
	CItem* pItem = m_listItem.back();
	Clear();
	return pItem;
}

_bool CItemSlot::Has_Item(CItem * _pItem)
{
	if (nullptr == _pItem)
		return false;
	for (auto& item : m_listItem)
	{
		if (item == _pItem)
			return true;
	}
	return false;
}


HRESULT CItemSlot::Initialize(Vector4 _vPos, Vector2 _vSize, _tchar * _pTextureTag, SCENEID _eTextureSceneID, _uint _iTextureID)
{
	m_bActive = false;

	m_eSceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
	//키매니저에 옵저버로 등록한다.
	CKeyMgr::Get_Instance()->RegisterObserver(m_eSceneID, this);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader);

	m_iTextureID = _iTextureID;


	if (FAILED(Set_Module(_pTextureTag, SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_pTransform->Set_Position(_vPos);
	m_pTransform->Set_Size(_vSize);


	RECT rc = m_pTransform->Get_RECT();
	_float fHolderCX = 50.f;
	_float fHolderCY = 36.f;
	m_tItemCntPlaceHolder = Make_Rect(Vector2(rc.left + fHolderCX * 0.5f, rc.top + fHolderCY * 0.5f), Vector2(fHolderCX, fHolderCY));

	return S_OK;
}

_int CItemSlot::Update(_double _timeDelta)
{

	//아이템이 사용됬으면
	if (!m_listItem.empty() && m_listItem.back()->IsUsed())
	{
		//드롭됬으면 플레이어 위치에 떨어뜨림.
		if (m_listItem.back()->IsDrop())
		{
			Drop_Item();
		}
		else
			//소비됬으면 그냥 지워버림.
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

	if (FAILED(m_pTexture->Set_Texture(m_iTextureID)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	//if (m_listItem.size() > 0)
	//{
	//	if (FAILED(m_listItem.front()->Render()))
	//		return E_FAIL;
	//}

	//장비슬롯이 아니고, 아이템이 하나이상이며, stackable이면 갯수 출력
	if (!m_bEquipmentslot && m_listItem.size() > 0 && m_listItem.back()->IsStackable())
	{
		_tchar szBuff[MAX_PATH] = L"";
		wsprintf(szBuff, L"%d", (_int)m_listItem.size());
		g_pFontX2->DrawText(NULL, szBuff, -1, &m_tItemCntPlaceHolder, DT_LEFT, 0xffffffff);

	}

	ALPHABLEND_END;

	return S_OK;
}


void CItemSlot::Clear()
{
	for (auto& item : m_listItem)
		Safe_Release(item);
	m_listItem.clear();
}

void CItemSlot::OnSetActive(_bool _bActive)
{
	for (auto& item : m_listItem)
	{
		item->Set_Active(_bActive);
	}
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

CItemSlot * CItemSlot::Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID, _uint _iTextureID)
{
	CItemSlot* pInstance = new CItemSlot(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_vPos, _vSize, _pTextureTag, _eTextureSceneID, _iTextureID)))
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
