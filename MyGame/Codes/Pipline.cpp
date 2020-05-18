#include "stdafx.h"
#include "..\Headers\Pipline.h"

USING(MyGame)
IMPLEMENT_SINGLETON(CPipline)
CPipline::CPipline()
{
	D3DXMatrixIdentity(&m_CameraStateMatrix);
	D3DXMatrixIdentity(&m_CameraStateMatrix_Inverse);
}

_int CPipline::UpdateViewMatrix()
{
	D3DXMatrixInverse(&m_CameraStateMatrix_Inverse, nullptr, &m_CameraStateMatrix);
	return 0;
}

void CPipline::Free()
{
}
