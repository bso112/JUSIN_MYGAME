#include "stdafx.h"
#include "..\Headers\Pipline.h"
#include "SceneMgr.h"

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

_matrix CPipline::Get_ViewMatrix()
{
	SCENEID currScene = CSceneMgr::Get_Instance()->Get_CurrScene();
	if (currScene == SCENE_EDITOR)
		return m_CameraStateMatrix_Inverse;
	return m_CameraStateMatrix;

}

void CPipline::Free()
{
}
