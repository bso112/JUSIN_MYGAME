#pragma once

#include "GameObject.h"
BEGIN(MyGame)

#define LASER_SIZEY 10.f
class CVIBuffer;
class CTexture;
class CTransform;
class CShader;
class CClock_Delay;

class CLaser : public CGameObject
{
public:
	typedef struct tagStateDESC
	{
		BASEDESC		m_tBaseDesc = {};
		const _tchar*	m_pTextureTag = L"";
		SCENEID			m_eTextureSceneID = SCENE_END;
		_double			m_dLifeTime = 10.f;
		_float			m_fSpeed = 1.f;
		_double			m_dRadianPerSec = 1.f;
		_uint			m_iTextureID = 1;
		_uint			m_iShaderPass = 0;
	}STATEDESC;
protected:
	explicit CLaser(PDIRECT3DDEVICE9 _pGraphic_Device) : CGameObject(_pGraphic_Device) {};
	explicit CLaser(CLaser& _rhs);
	virtual ~CLaser() = default;

protected:
	CVIBuffer*		m_pVIBuffer = nullptr;
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CShader*		m_pShader = nullptr;
	STATEDESC		m_tDesc;
	//파티클은 턴이 아닌 시간에 영향을 받음.
	CClock_Delay*	m_pDeadClock = nullptr;

private:
	//알파값
	_float			m_fAlpha = 1;
	_bool			m_bFadeOut = false;
public:
	virtual HRESULT Initialize(void* _pArg);
	virtual _int Update(_double _timeDelta) override;
	virtual _int LateUpate(_double _timeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT Beam(Vector2 _vOrigin, POINT _Pt);
	HRESULT	Beam(Vector2 _vOrigin, Vector2 _vDst);

public:
	void	Set_FadeOut() { m_bFadeOut = true; }
public:
	_float	Get_Alpha() { return m_fAlpha; }



public:
	static CLaser* Create(PDIRECT3DDEVICE9 _pGraphic_Device, STATEDESC& _tDesc);
	virtual void Free() override;

	// CGameObject을(를) 통해 상속됨
	virtual CGameObject * Clone(void * _pArg = nullptr) override;

};
END
