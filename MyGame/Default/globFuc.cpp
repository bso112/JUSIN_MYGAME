#include "stdafx.h"


RECT Make_Rect(D3DXVECTOR4 _vPos, D3DXVECTOR4 _vSize)
{
	//다음 위치의 Rect를 구한다.
	RECT rc = {};
	float fX = _vPos.x;
	float fY = _vPos.y;
	int iCX = (int)_vSize.x;
	int iCY = (int)_vSize.y;

	rc.left = (LONG)fX - (iCX >> 1);
	rc.right = (LONG)fX + (iCX >> 1);
	rc.top = (LONG)fY - (iCY >> 1);
	rc.bottom = (LONG)fY + (iCY >> 1);
	return rc;
}