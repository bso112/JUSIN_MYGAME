#pragma once
#include "Scene.h"
BEGIN(MyGame)
class CImage;
class CLoading;
class CScene_Loading :
	public CScene
{
protected:
	explicit CScene_Loading(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CScene_Loading() = default;

private:
	CImage*		m_pMainUI = nullptr;
	CLoading*	m_pLoading = nullptr;
public:
	virtual HRESULT Initialize();
	virtual _int	Update(_double _timeDelta);
	virtual HRESULT	Render();

public:
	HRESULT	Initialize_Scene(SCENEID _SceneID, _uint _iLevel);


public:
	static CScene_Loading* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
