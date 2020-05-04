#pragma once

#include "Module.h"
#include "Animation.h"

BEGIN(MyGame)

class CAnimator : public CModule
{
private:
	explicit CAnimator(PDIRECT3DDEVICE9 _pGraphic_Device) : CModule(_pGraphic_Device) {};
	explicit CAnimator(CAnimator& _rhs);
	virtual ~CAnimator() = default;

private:
	map<const _tchar*, CAnimation*> m_mapAnim;
	CAnimation*						m_pCurrAnim = nullptr;
public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);

public:
	HRESULT	Add_Animation(const _tchar* _pTag, CAnimation* _pAnimation);
	_int	Render();
	HRESULT	Play(const _tchar* _pTag);
public:
	static CAnimator* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CModule* Clone(void * _pArg = nullptr) override;
	virtual void Free();
};
END
