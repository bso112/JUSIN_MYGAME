#pragma once

#include "GameObject.h"
BEGIN(MyGame)

class CVIBuffer;
class CTexture;
class CTransform;
class CShader;
//�̹����� ��ư�� ������Ÿ���� ����� �ȴ�. ���� ��Ȱ����ϴϱ�.
class CParticle : public CGameObject
{
public:
	typedef struct tagStateDESC
	{
		BASEDESC		m_tBaseDesc = {};
		const _tchar*	m_pTextureTag = L"";
		SCENEID			m_eTextureSceneID = SCENE_END;
		_float			m_fSpeed = 1.f;
		_uint			m_iTextureID = 1;
	}STATEDESC;
protected:
	explicit CParticle(PDIRECT3DDEVICE9 _pGraphic_Device) : CGameObject(_pGraphic_Device) {};
	explicit CParticle(CParticle& _rhs);
	virtual ~CParticle() = default;

protected:
	CVIBuffer*	m_pVIBuffer = nullptr;
	CTexture*	m_pTextrue = nullptr;
	CTransform*	m_pTransform = nullptr;
	CShader*	m_pShader = nullptr;
	STATEDESC	m_tDesc;
	MYFONT		m_tFont;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);

	virtual _int Update(_double _timeDelta) override;
	virtual _int LateUpate(_double _timeDelta) override;
	virtual HRESULT Render() override;

protected:
	virtual HRESULT	OnRender();

public:
	void	Set_Font(MYFONT _tFont) { m_tFont = _tFont; }
	void	Replace_Texture(const _tchar* pTextureTag, _int _iTextureID, SCENEID _eTextureSceneID);
public:
	static CParticle* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual	CGameObject* Clone(void* _param = nullptr)override;
	virtual void Free() override;

};
END
