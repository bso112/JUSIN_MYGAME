#include "stdafx.h"
#include "..\Headers\Hero.h"
#include "KeyMgr.h"

USING(MyGame)



CHero::CHero(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CCharacter(_pGraphic_Device), m_pKeyMgr(CKeyMgr::Get_Instance())
{
	Safe_AddRef(m_pKeyMgr);
}

HRESULT CHero::KeyCheck()
{
	if (m_pKeyMgr == nullptr)
		return E_FAIL;
	if (m_pKeyMgr->Key_Down(VK_LBUTTON))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		m_vDst = Vector4((float)pt.x, (float)pt.y);

	}

	return S_OK;
}

void CHero::Free()
{
	Safe_Release(m_pKeyMgr);
	CCharacter::Free();
}


