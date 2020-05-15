#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CCamera :
	public CGameObject
{
public:
	CCamera();
	virtual ~CCamera();

	//포지션 벡터, 회전, 스케일, 스테이트 행렬
	//화면 중간상수
};
END
