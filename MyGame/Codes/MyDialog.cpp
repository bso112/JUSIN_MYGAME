#include "stdafx.h"
#include "..\Headers\MyDialog.h"
#include "Image.h"

USING(MyGame)

CMyDialog::CMyDialog(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
}

CMyDialog::CMyDialog(CMyDialog & _rhs)
	: CGameObject(_rhs)
{
}

HRESULT CMyDialog::Initialize(void * _pArg)
{
	//플레이스홀더들을 만든다.

	_float fBaseCX = 400.f;
	_float fBaseCY = 250.f;
	_float fBaseX = 0;
	_float fBaseY = 70;

	_float fHolderCX = fBaseCX;
	_float fHolderCY = 20.f;

	_float fHolderX;
	_float fHolderY;

	for (int i = 0; i < MAX_SENTENCE; ++i)
	{
		fHolderX = fBaseCX * 0.5f;
		fHolderY = g_iWinCY - 70 - (fHolderCY * 0.5f) - (fHolderCY * i);
		m_pPlaceHolder[i] = Make_Rect(Vector2(fHolderX, fHolderY), Vector2(fHolderCX, fHolderCY));
	}


	return S_OK;
}

_int CMyDialog::LateUpate(_double _timeDelta)
{
	if (nullptr == m_pRenderer)
		return -1;

	m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI);

	return 0;
}

HRESULT CMyDialog::Render()
{
	if (m_senetencs.size() > MAX_SENTENCE)
		return E_FAIL;

	auto& iter = m_senetencs.begin();
	for (int i = 0; iter != m_senetencs.end(); ++iter)
	{
		g_pFont->DrawText(NULL, (*iter).first->c_str(), -1, &m_pPlaceHolder[i], DT_LEFT, (*iter).second);
		++i;
	}

	return S_OK;
}

void CMyDialog::Log(wstring* _pLog, D3DXCOLOR _pColor)
{
	//만약 꽉찼으면 맨뒤의 것을 삭제
	if (m_senetencs.size() >= MAX_SENTENCE)
	{
		wstring* back = m_senetencs.back().first;
		Safe_Delete(back);
		m_senetencs.pop_back();
	}
	
	m_senetencs.push_front(make_pair(_pLog, _pColor));
}


CMyDialog * CMyDialog::Create(PDIRECT3DDEVICE9 _pGrahic_Device)
{
	CMyDialog* pInstance = new CMyDialog(_pGrahic_Device);
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to create CMyDialog");
		Safe_Release(pInstance);

	}
	return pInstance;
}


void CMyDialog::Free()
{
	for (auto& sentence : m_senetencs)
	{
		Safe_Delete(sentence.first);
	}
	m_senetencs.clear();
}

CGameObject * CMyDialog::Clone(void * _pArg)
{
	return nullptr;
}
