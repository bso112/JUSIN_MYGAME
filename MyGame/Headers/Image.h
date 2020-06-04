#pragma once

#include "GameObject.h"
BEGIN(MyGame)

class CVIBuffer;
class CTexture;
class CTransform;
class CShader;
class CClock_Delay;
//이미지와 버튼은 프로토타입을 만들기 싫다. 딱히 재활용안하니까.
class CImage : public CGameObject
{
public:
	typedef struct tagStateDESC
	{
		BASEDESC		m_tBaseDesc = {};
		const _tchar*	m_pTextureTag = L"";
		SCENEID			m_eTextureSceneID = SCENE_END;
		_int			m_iTextureID = 1;
		_float			m_fSpeed = 1.f;
		_double			m_dLifeTime = FLT_MAX;
	}STATEDESC;
protected:
	explicit CImage(PDIRECT3DDEVICE9 _pGraphic_Device) : CGameObject(_pGraphic_Device) {};
	explicit CImage(CImage& _rhs);
	virtual ~CImage() = default;

protected:
	CVIBuffer*	m_pVIBuffer = nullptr;
	CTexture*	m_pTextrue = nullptr;
	CTransform*	m_pTransform = nullptr;
	CShader*	m_pShader = nullptr;
	const _tchar*	m_pTextureTag = L"";
	_int			m_iTextureID = 1;
	MYFONT			m_tFont;
	//UI인가
	_bool			m_bUI = true;
	_double			m_dLifeTime = FLT_MAX;

	STATEDESC		m_tDesc;
	_bool			m_bFadeOut = false;
	_float			m_fAlpha = 1;
	_uint			m_iShaderPass = 0;

	CRenderer::RENDER_GROUP m_eRenderGroup = CRenderer::RENDER_UI;

private:
	CClock_Delay* m_pDeadClock = nullptr;

public:
	virtual HRESULT Initialize_Prototype(const _tchar* _pTextureTag, Vector4 _vPos, Vector2 _vSize, SCENEID _eTextureSceneID);
	virtual HRESULT Initialize_Prototype(void* _desc);
	virtual HRESULT Initialize(void* _pArg);

	virtual _int Update(_double _timeDelta) override;
	virtual _int LateUpate(_double _timeDelta) override;
	virtual HRESULT Render() override;

protected:
	virtual HRESULT	OnRender();

public:
	void	Set_Font(MYFONT _tFont) { m_tFont = _tFont; }
	void	Set_UI(_bool _bUI) { m_bUI = _bUI; }
	void	Set_ShaderPass(_uint _iPass) { m_iShaderPass = _iPass; }
	void	Replace_Texture(const _tchar* pTextureTag, _int _iTextureID, SCENEID _eTextureSceneID);
	void	Set_TextureID(_uint _iTextureID) { m_iTextureID = _iTextureID; m_tDesc.m_iTextureID = _iTextureID; }
	STATEDESC	Get_DESC() { return m_tDesc; }
	void	Set_FadeOut() { m_bFadeOut = true; m_iShaderPass = 4; }
	void	Set_RenderGroup(CRenderer::RENDER_GROUP _eRenderGroup) { m_eRenderGroup = _eRenderGroup; }
public:
	static CImage* Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, const _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	static CImage* Create(PDIRECT3DDEVICE9 _pGraphic_Device, void* _desc);
	virtual	CGameObject* Clone(void* _param = nullptr)override;
	virtual void Free() override;

};
END
