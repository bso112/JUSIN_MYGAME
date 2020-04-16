#include "stdafx.h"
#include "..\Headers\Tile.h"

USING(MyGame)


HRESULT CTile::Initalize(float _fX, float _fY)
{	
	m_tInfo.vPos.x = _fX;
	m_tInfo.vPos.y = _fY;
	m_tInfo.vPos.z = 0;
	m_tInfo.vPos.w = 1;

	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;

	Update_Rect();
	return S_OK;
}

HRESULT CTile::Render(HDC _DC)
{
	Update_Rect();
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	return S_OK;
}

CTile * CTile::Create(float _fX, float _fY)
{

	CTile* pInstance = new CTile;
	if (FAILED(pInstance->Initalize(_fX, _fY)))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}


CGameObject * CTile::Clone(void * _param)
{
	CGameObject* pInstance = new CTile(*this);
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}
