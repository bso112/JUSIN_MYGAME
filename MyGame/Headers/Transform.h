#pragma once
#include "Module.h"

BEGIN(MyGame)
class CTransform final : public CModule
{
public:
	typedef struct tagStateDesc
	{
		_double speedPerSec;
		_double	radianPerSec;
	}STATEDESC;
private:
	explicit CTransform(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CTransform(CTransform& _module);
	virtual ~CTransform() = default;


private:
	STATEDESC	m_tStateDesc;
	_matrix		m_StateMatrix;
	
	Vector3		m_vPosition;
	Vector3		m_vSize;
	Vector3		m_vRotation;


public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);
	virtual _int	Update();

public:
	HRESULT	Set_Position(Vector3 _vPosition);
	HRESULT	Set_Size(Vector3 _vSize);
	HRESULT	Set_Roation(Vector3 _vRotation);
	_matrix	Get_Matrix() { return m_StateMatrix; }
	Vector3	Get_Position() { return m_vPosition; }
	Vector3	Get_Size() { return m_vSize; }
	Vector3 Get_Rotation() { return m_vRotation; }
	RECT	Get_Rect();

public:
	HRESULT	MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _fStopDistance);
	HRESULT	MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _fStopDistance, _double _speed);
	HRESULT MoveToDir(Vector3 _vDir, _double _timeDelta);
	HRESULT MoveToDir(Vector3 _vDir, _double _timeDelta, _double _speed);


		

public:
	static CTransform*	Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	// CModule을(를) 통해 상속됨
	virtual CModule * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};

END
