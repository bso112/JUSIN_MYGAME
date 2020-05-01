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

		tagStateDesc() {}
		tagStateDesc
		(
		_double _speedPerSec,
		_double	_radianPerSec
		)
		{
			speedPerSec = _speedPerSec;
			radianPerSec = _radianPerSec;
		}
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

private:
	//목표 위치
	Vector3		m_vDst;
	_double		m_StopDistance;
	//멈춰 있냐?
	_bool		m_bStop = true;
	
public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);
	virtual _int	Update(_double _timeDelta);
	virtual _int	Late_Update();

public:
	HRESULT	Set_Position(Vector3 _vPosition);
	HRESULT	Set_Size(Vector3 _vSize);
	HRESULT	Set_Rotation(Vector3 _vRotation);
	_matrix	Get_Matrix() { return m_StateMatrix; }
	Vector3	Get_Position() { return m_vPosition; }
	Vector3	Get_Size() { return m_vSize; }
	Vector3 Get_Rotation() { return m_vRotation; }
	RECT	Get_Rect();
	//저절로 움직이고 있나?
	bool	Is_Auto() { return !m_bStop; }

public:
	HRESULT MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance);
	HRESULT MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance, _double _Speed);
	HRESULT MoveToDir(Vector3 _vDir, _double _timeDelta);
	HRESULT MoveToDir(Vector3 _vDir, _double _timeDelta, _double _Speed);
	HRESULT	MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance);
	HRESULT	MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance, _double _Speed);

	
public:
	//타깃을 따라간다.
	HRESULT	MoveToTarget_Auto(CTransform * _pTransform, _double _StopDistance);
	//해당 방향으로 간다.
	HRESULT MoveToDir_Auto(Vector3 _vDir);
	//해당 위치로 간다.
	HRESULT	MoveToDst_Auto(Vector3 _vDst, _double _fStopDistance);

public:
	void	Stop() { m_bStop = true; }
		

public:
	static CTransform*	Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	// CModule을(를) 통해 상속됨
	virtual CModule * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};

END
