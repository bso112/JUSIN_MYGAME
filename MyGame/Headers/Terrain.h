#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CTransform;
class CTexture;
class CVIBuffer;
class CTerrain final : public CGameObject
{
public:
	typedef struct tag_SaveData
	{
		_tchar		m_PrototypeTag[MAX_PATH];
		Vector3		m_vPosition;
		Vector3		m_vSize;
		Vector3		m_vRotation;

	}SAVE_DATA;
private:
	explicit CTerrain() {};
	explicit CTerrain(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CTerrain(CTerrain& _rhs);
	virtual ~CTerrain() = default;

private:
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CVIBuffer*		m_pVIBuffer = nullptr;

private:
	TERRAIN			m_tInfo = {};
	const _tchar*	m_pPrototypeTag;
	// _uint로 하면 음수가 되는순간 4500어쩌구 하는 큰값이 들어가서 최대 텍스쳐 사이즈 -1 이됨.
	_int			m_iCurFrame = 0;


public:
	virtual HRESULT	Initialize_Prototype(TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, const _tchar* _pPrototypeTag,_tchar* _pFilePath = nullptr);
	virtual	HRESULT	Initialize();
	virtual HRESULT	Render();

public:
	SAVE_DATA	Get_SaveData();
	HRESULT		Load_Data(SAVE_DATA _eSaveData);

public:
	HRESULT		Forward_Frame();
	HRESULT		Backward_Frame();


	
public:
	static CTerrain*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene,  _tchar* _pFilePath = nullptr);
	virtual CGameObject* Clone(void * _param = nullptr);
	virtual void Free() override;

public:

private:
	HRESULT	Initalize_Module();

};
END
