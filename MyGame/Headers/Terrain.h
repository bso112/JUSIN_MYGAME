#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CTransform;
class CTexture;
class CVIBuffer;
class CTerrain  : public CGameObject
{

public:
	enum STATE { STATE_NORMAL = 0, STATE_UNLOCKED = 0, STATE_LOCKED = 1, STATE_USED = 1 , STATE_END};
public:
	typedef struct tag_SaveData
	{
		_tchar		m_PrototypeTag[MAX_PATH];
		Vector3		m_vPosition;
		Vector3		m_vSize;
		Vector3		m_vRotation;
		_int		m_iCurFrame;
		STATE		m_eState;


	}SAVE_DATA;
protected:
	explicit CTerrain() {};
	explicit CTerrain(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CTerrain(CTerrain& _rhs);
	virtual ~CTerrain() = default;

protected:
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CVIBuffer*		m_pVIBuffer = nullptr;

protected:
	STATE			m_eState = STATE_NORMAL;
	bool			m_bHidden	= false;

protected:
	TERRAIN			m_tInfo = {};
	_tchar			m_PrototypeTag[MAX_PATH];
	// _uint로 하면 음수가 되는순간 4500어쩌구 하는 큰값이 들어가서 최대 텍스쳐 사이즈 -1 이됨.
	_int			m_iCurFrame = 0;


public:
	virtual HRESULT	Initialize_Prototype(TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, const _tchar* _pPrototypeTag,_tchar* _pFilePath = nullptr);
	virtual	HRESULT	Initialize();
	virtual HRESULT	Render();

public:
	SAVE_DATA	Get_SaveData();
	HRESULT		Load_Data(SAVE_DATA& _eSaveData);
	void		Hide() { m_bHidden = true; }
	void		Reveal() { m_bHidden = false; }
	bool		IsHidden() { return m_bHidden; }

public:
	HRESULT		Forward_Frame();
	HRESULT		Backward_Frame();

protected:
	//에디터씬에서 Frame이 변할때 하위클래스에 맞는 데이터로 셋팅함.
	virtual	HRESULT	OnMoveFrame();
	//Terrain을 로드할때 하위클래스에 맞는 데이터로 셋팅함.
	virtual HRESULT	OnLoadData();
public:
	static CTerrain*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene,  _tchar* _pFilePath = nullptr);
	virtual CGameObject* Clone(void * _param = nullptr);
	virtual void Free() override;

public:
	virtual HRESULT	Interact();

private:
	HRESULT	Initalize_Module();

};
END
