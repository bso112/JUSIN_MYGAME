#include "stdafx.h"
#include "..\Headers\Tile.h"

USING(MyGame)


HRESULT CTile::Initalize(float _fX, float _fY)
{	

	return S_OK;
}

HRESULT CTile::Render()
{
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
