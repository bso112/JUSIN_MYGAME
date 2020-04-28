#pragma once
#include "GameObject.h"

BEGIN(MyGame)


class CVIBuffer;
class CTransform;
class CTexture;
class CShader;
class CMyButton final : public CGameObject
{

public:
	enum RENDER_STATE { STATE_ENABLE = 0, STATE_DISABLE = 1, STATE_END};
private:
	explicit CMyButton(PDIRECT3DDEVICE9 _pGraphic_Device) :CGameObject(_pGraphic_Device) {};
	explicit CMyButton(CMyButton& _rhs);
	virtual ~CMyButton() = default;


private:
	CVIBuffer*		m_pVIBuffer = nullptr;
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CShader*		m_pShader = nullptr;
	RECT			m_tRect = {};
	const _tchar*	m_pText = L"";
	RENDER_STATE	m_eRenderState = STATE_ENABLE;

	int			m_iInstanceID = 0;



private:
	vector<function<void()>> m_vecOnListener;


public:
	HRESULT Initialize(Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	_int	Update(_double _timeDelta)	override;
	virtual _int	LateUpate(_double _timeDelta);
	HRESULT	Render();

public:
	HRESULT	Add_Listener (function<void()> _listener);
	void	Set_Text(const _tchar* pText) { m_pText = pText; }
	HRESULT	Set_RenderState(RENDER_STATE _eRenderState);
	

	void	Set_InstanceID(int _iID) { m_iInstanceID = _iID; }


public:
	static CMyButton*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
public:
	virtual CGameObject * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};

END