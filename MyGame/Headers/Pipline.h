#pragma once
#include "Base.h"

BEGIN(MyGame)
class CPipline :
	public CBase
{
	DECLARE_SINGLETON(CPipline)
private:
	explicit CPipline();
	virtual ~CPipline() = default;

private:
	_matrix	m_CameraStateMatrix;
	_matrix	m_CameraStateMatrix_Inverse;

public:
	_int	UpdateViewMatrix();
public:
	_matrix	Get_CameraMatrix() { return m_CameraStateMatrix; }
	_matrix Get_CameraMatrix_inverse() { return m_CameraStateMatrix_Inverse; }
	void	Set_CameraMatrix(_matrix _cameraStateMatrix) { m_CameraStateMatrix = _cameraStateMatrix; }

public:
	//오브젝트에 적용할 카메라 매트릭스
	_matrix Get_ViewMatrix() { return m_CameraStateMatrix; }


	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};

END