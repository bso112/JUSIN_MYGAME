#pragma once
#include "Module.h"

BEGIN(MyGame)
class CTerrain;
class CTexture;
class CVIBuffer;
class CTransform final : public CModule
{
public:
	typedef struct tagStateDesc
	{
		_double speedPerSec = 1.0;
		_double	radianPerSec = 0.0;
		//���Ͽ� �� Ÿ�� �����̴°�
		_uint	movePerTurn = 1;
		tagStateDesc() {}
		tagStateDesc
		(
			_double _speedPerSec,
			_double	_radianPerSec,
			_uint	_movePerTurn = 1
		)
		{
			speedPerSec = _speedPerSec;
			radianPerSec = _radianPerSec;
			movePerTurn = _movePerTurn;
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
	Vector3		m_vRevolveAngle;
	Vector3		m_vPivot;
	//ȸ���� �����̵� x�����
	Vector3		m_vLook;

	//�ݶ��̴� ������ ����
	CTexture*	m_pTexture = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;

	//for Update_Route
private:
	//��ǥ Ʈ������
	CTransform*			m_pTarget = nullptr;
	//�θ� Ʈ������
	CTransform*			m_pParent = nullptr;
	//��ǥ ��ġ
	Vector3				m_vDst;
	//�̵��� ����
	Vector3				m_vDir;
	//��ǥ������ ��Ʈ(����)
	vector<CTerrain*>	m_Route;
	_double				m_StopDistance;
	//���� �ֳ�?
	_bool				m_bStop = true;
	//�ݶ��̴� ������
	Vector3				m_vColliderSize;
	//�̵��¸�ŭ �̵��߳�?
	_bool				m_bTurnEnd = false;
	_bool				m_bPlayer = false;

	//for Update_Noaml(auto ���� �Լ��鿡�� ����)
private:
	//�̵��� ����
	Vector3				m_vDir_Normal;
	_float				m_fRotationZ_Noaml = 0.f;
	Vector3				m_dShrinkSpeed;
	Vector3				m_dExpandSpeed;


private:
	static _int m_iTurnCnt;


private:
	//���� �̵��� ����� �ε���
	_int				m_iCurrRouteIndex = 0;
	//�̵��¸�ŭ �̵��ߴ��� �˾ƺ��� ���� ī��Ʈ����
	_int				m_iCntForTurn = 0;
	//�� ��� Ÿ���� �̵��ߴ°�
	_int				m_iTotalMoveCnt = 0;
public:
	HRESULT Initialize_Prototype();
	HRESULT Initialize(void* _pArg);
	HRESULT Update_Route(_double _timeDelta);
	HRESULT Update_Normal(_double _timeDelta);
	//state martix�� ������Ʈ�Ѵ�.
	_int	Update_Transform();
	HRESULT	Render_Collider();


public:
	HRESULT	Go_Route(vector<CTerrain*> _route, _double _fStopDistance, _int _iTurnCnt);
	HRESULT	Go_Target(CTransform* _pTarget, _double _fStopDistance);

	

public:
	HRESULT	Set_Position(Vector3 _vPosition);
	HRESULT	Set_Pivot(Vector3 _vPivot);
	HRESULT	Set_Size(Vector3 _vSize);
	HRESULT	Set_ColliderSize(Vector3 _vSize) { m_vColliderSize = _vSize; return S_OK; }
	HRESULT	Set_Rotation(Vector3 _vRadian);
public:
	_matrix		Get_Matrix() { Update_Transform(); return m_StateMatrix; }
	Vector3		Get_Position() { return m_vPosition; }
	Vector3		Get_WorldPos();
	Vector3		Get_Size() { return m_vSize; }
	Vector3		Get_Rotation() { return m_vRotation; }
	RECT		Get_Collider();
	RECT		Get_RECT();
	STATEDESC	Get_Desc() { return m_tStateDesc; }
	Vector3		Get_Dir() { return m_vDir; }


public:
	//�̵��ϴ� ������ �ٶ󺻴�.
	void		FaceDir(Vector2 _vDir);

public:
	//������ �����̰� �ֳ�?
	_bool	Is_Auto() { return !m_bStop; }
	_bool	Is_Moving() { return !m_bStop; }
	_bool	Is_TurnEnd() { return m_bTurnEnd; }
	void	NextTurn() { m_bTurnEnd = false; }


public:
	HRESULT LookAt(CTransform* pTargetTransform);
	HRESULT	LookAt(Vector3 _vPos);
	void	Set_Parent(CTransform* pParent);
public:
	HRESULT MoveToDirAuto(Vector3 _vDir);
	HRESULT	MoveToDirAuto(Vector3 _vDir, _double _timeDelta, _double _Speed);
	//ũ�Ⱑ �۾�����.
	HRESULT	Shrink_Auto(Vector2 _vShrink);
	//ũ�Ⱑ Ŀ����.
	HRESULT	Expand_Auto(Vector2 _vExpand);
	//ȸ���Ѵ�.
	HRESULT	Rotate_Auto(_float	radianPerSec);


public:
	HRESULT MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance);
	HRESULT MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance, _double _Speed);
	HRESULT MoveToDir(Vector3 _vDir, _double _timeDelta);
	HRESULT MoveToDir(Vector3 _vDir, _double _timeDelta, _double _Speed);
	//�����ϸ� true����
	_bool	MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance);
	HRESULT	MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance, _double _Speed);

public:
	HRESULT Add_Froce(Vector3 _vDir, _float _fForce, _double _timeDelta);



public:
	RECT	Make_Rect(Vector3 _vPos, Vector2 _vSize);



public:
	void	Stop() { m_bStop = true; }


public:
	static CTransform*	Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	// CModule��(��) ���� ��ӵ�
	virtual CModule * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};

END
