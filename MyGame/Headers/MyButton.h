#pragma once
#include "GameObject.h"

BEGIN(MyGame)
class CVIBuffer;
class CTransform;
class CTexture;
//이미지와 버튼은 프로토타입을 만들기 싫다. 딱히 재활용안하니까.
class CMyButton final : public CGameObject
{
private:
	explicit CMyButton(PDIRECT3DDEVICE9 _pGraphic_Device) :CGameObject(_pGraphic_Device) {};
	explicit CMyButton(CMyButton& _rhs);
	virtual ~CMyButton() = default;


private:
	CVIBuffer*		m_pVIBuffer = nullptr;
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	RECT			m_tRect = {};
	const _tchar*	m_pText = L"";


	int			m_iInstanceID = 0;



private:
	vector<function<void()>> m_vecOnListener;


public:
	HRESULT Initialize(Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	_int	Update(_double _timeDelta)	override;
	HRESULT	Render();

public:
	HRESULT	Add_Listener (function<void()> _listener);
	void	Set_Text(const _tchar* pText) { m_pText = pText; }
	

	void	Set_InstanceID(int _iID) { m_iInstanceID = _iID; }


public:
	static CMyButton*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
public:
	virtual CGameObject * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};

END