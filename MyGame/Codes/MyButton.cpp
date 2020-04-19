#include "stdafx.h"
#include "..\Headers\MyButton.h"
#include "Renderer.h"
USING(MyGame)

CMyButton::CMyButton(CMyButton & _rhs)
	: CGameObject(_rhs)
{

	m_listOnClick = _rhs.m_listOnClick;
}


HRESULT CMyButton::Initialize(void * _arg)
{
	return S_OK;
}

HRESULT CMyButton::AddListener(void(*OnClick)())
{
	if (nullptr == OnClick)
		return E_FAIL;

	m_listOnClick.push_back(OnClick);

	return S_OK;
}

_int CMyButton::Update(_double _timeDelta)
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(g_hWnd, &cursorPos);

	//만약 클릭되면 온클릭 이벤트 실행
	//if (PtInRect(&m_tRect, cursorPos))
	//{
	//	for (auto& func : m_listOnClick)
	//	{
	//		if (nullptr != func)
	//			func();
	//	}

	//}

	return 0;
}




CGameObject * CMyButton::Clone(void * _arg)
{
	CMyButton* pInstance = new CMyButton(*this);
	if (FAILED(pInstance->Initialize(_arg)))
	{
		MSG_BOX("Fail to create Background");
		Safe_Release(pInstance);

	}
	return pInstance;
}

