#include "stdafx.h"
#include "..\Headers\KeyMgr.h"
#include "SceneMgr.h"

USING(MyGame)

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));

	for (int i = 0; i < SCENE_END;++i)
		m_listObservers[i].clear();
}


bool CKeyMgr::Key_Pressing(int _Key)
{
	if ((GetAsyncKeyState(_Key) & 0x8000))
	{
		SCENEID sceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
		if (sceneID >= SCENE_END)
			MSG_BOX("유효하지 않은 씬입니다.");
		for (auto& observer : m_listObservers[sceneID])
		{
			observer->OnKeyPressing(_Key);
		}
		return true;
	}
	return false;
}

bool CKeyMgr::Key_Down(int _Key)
{
	if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];

		SCENEID sceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
		if (sceneID >= SCENE_END)
			MSG_BOX("유효하지 않은 씬입니다.");
		for (auto& observer : m_listObservers[sceneID])
		{
			observer->OnKeyDown(_Key);
		}
		return true;
	}
	return false;
}

bool CKeyMgr::Key_Up(int _Key)
{
	if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];
		
		SCENEID sceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
		if (sceneID >= SCENE_END)
			MSG_BOX("유효하지 않은 씬입니다.");

		for (auto& observer : m_listObservers[sceneID])
		{
			observer->OnKeyUp(_Key);
		}
		return true;
	}
	return false;
}

void CKeyMgr::Key_Update()
{
	// Key 상태 복원 함수
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];

		if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}
}

HRESULT CKeyMgr::RegisterObserver(SCENEID _eSceneID, CBase * _pObserver)
{
	if (nullptr == _pObserver)
		return E_FAIL;
	
	m_listObservers[_eSceneID].push_back(_pObserver);
	
	return S_OK;
}

HRESULT CKeyMgr::UnRegisterObserver(SCENEID _eSceneID, CBase * _pObserver)
{
	if (nullptr == _pObserver)
		return E_FAIL;

	auto& iter = m_listObservers[_eSceneID].begin();
	for (;iter != m_listObservers[_eSceneID].end(); ++iter)
	{
		if (*iter == _pObserver)
		{
			m_listObservers[_eSceneID].erase(iter);
			return S_OK;
		}
	}

	return E_FAIL;
}

HRESULT CKeyMgr::ClearObservers(SCENEID _eSceneID)
{
	if (_eSceneID >= SCENE_END)
		return E_FAIL;


	m_listObservers[_eSceneID].clear();
	return S_OK;
}

void CKeyMgr::Free()
{
	for (auto& arr : m_listObservers)
	{
		arr.clear();
	}

}
