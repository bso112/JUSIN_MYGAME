#pragma once
#include "Scene.h"

BEGIN(MyGame)
class CTilePalette;
class CLevel;
class CTerrain;
class CCamera;
class CEditor final: public CScene
{
private:
	explicit CEditor(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CEditor() = default;


public:
	virtual HRESULT Initialize();
	virtual _int	Update(_double _timeDelta);
	virtual HRESULT	Render();

private:
	CTilePalette*	m_pPalette = nullptr;
	CLevel*			m_pWorld = nullptr;
	//Editor ������ �ִ� �ӽ�Ÿ���̴�.
	CTerrain*		m_pCurrTerrain = nullptr;
	CCamera*		m_pMainCam = nullptr;


public:
	static CEditor* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

public:
	virtual HRESULT	OnKeyDown(_int KeyCode);
	virtual HRESULT OnKeyPressing(_int KeyCode);




};
END
