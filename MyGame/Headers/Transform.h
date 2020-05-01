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
	//��ǥ ��ġ
	Vector3		m_vDst;
	_double		m_StopDistance;
	//���� �ֳ�?
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
	//������ �����̰� �ֳ�?
	bool	Is_Auto() { return !m_bStop; }

public:
	HRESULT MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance);
	HRESULT MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance, _double _Speed);
	HRESULT MoveToDir(Vector3 _vDir, _double _timeDelta);
	HRESULT MoveToDir(Vector3 _vDir, _double _timeDelta, _double _Speed);
	HRESULT	MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance);
	HRESULT	MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance, _double _Speed);

	
public:
	//Ÿ���� ���󰣴�.
	HRESULT	MoveToTarget_Auto(CTransform * _pTransform, _double _StopDistance);
	//�ش� �������� ����.
	HRESULT MoveToDir_Auto(Vector3 _vDir);
	//�ش� ��ġ�� ����.
	HRESULT	MoveToDst_Auto(Vector3 _vDst, _double _fStopDistance);

public:
	void	Stop() { m_bStop = true; }
		

public:
	static CTransform*	Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	// CModule��(��) ���� ��ӵ�
	virtual CModule * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};

END
