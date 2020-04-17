#include "stdafx.h"
#include "..\Headers\MyButton.h"

USING(MyGame)

CMyButton::CMyButton(CMyButton & _rhs)
	: CGameObject(_rhs)
{

	m_listOnClick = _rhs.m_listOnClick;
}

HRESULT CMyButton::Initialize_Prototype(INFO _tInfo)
{

	return S_OK;
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

	m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_TEST);
	return 0;
}



CMyButton * CMyButton::Create(PDIRECT3DDEVICE9 _pGraphic_Device, INFO _tInfo)
{
	CMyButton* pInstance = new CMyButton(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_tInfo)))
	{
		MSG_BOX("Fail to create VIBuffer");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
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

