#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CTransform;
class CCamera final : public CGameObject
{
private:
	explicit CCamera(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CCamera(CCamera& _rhs);
	virtual ~CCamera() = default;


private:
	CTransform*	m_pTransform = nullptr;
	//µ˚∂Û¥Ÿ¥“ ≈∏∞Ÿ
	CTransform*	m_pTarget = nullptr;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _pArg = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);

public:
	void	Set_Target(CTransform* _pTargetTransform) { m_pTarget = _pTargetTransform; }

public:
	static CCamera* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject* Clone(void * _pArg = nullptr);

public:
	// CBase¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	virtual void Free() override;

};
END
