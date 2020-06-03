#pragma once
#include "GameObject.h"
BEGIN(MyGame)
#define CAMERA_MOVE_SPEED 5.f
#define CAMERA_SCAILING_SPEED 0.1f
#define CAMERA_ORIGINAL_SCALE Vector3(1.7f,1.7f,1.f);
#define	CAMERA_SHAKE_INTENCITY 2
class CClock_Delay;
class CTransform;
class CCamera final : public CGameObject
{
private:
	explicit CCamera(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CCamera(CCamera& _rhs);
	virtual ~CCamera() = default;


private:
	CTransform*	m_pTransform = nullptr;
	//따라다닐 타겟
	CTransform*	m_pTarget = nullptr;
	Vector3		m_vTranslation;
	//기본 스케일
	Vector3		m_vScale = CAMERA_ORIGINAL_SCALE;
	//카메라 흔들기에 쓸 타이머
	CClock_Delay* m_pShakeTimer = nullptr;
	//카메라 흔들기 지속시간
	_double		m_dShakeDuration = 0.0;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _pArg = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);

public:
	void	Set_Target(CTransform* _pTargetTransform) { m_pTarget = _pTargetTransform; }
	void	Shake_Camera(_double _dTime);
public:
	virtual HRESULT OnKeyPressing(_int KeyCode);
public:
	static CCamera* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject* Clone(void * _pArg = nullptr);

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
