#pragma once

#include "Base.h"

BEGIN(MyGame)

#define WORLDX 100
#define WORLDY 100

class CTerrain;
class CWorld final : public CBase
{
	DECLARE_SINGLETON(CWorld)
private:
	explicit CWorld() {};
	virtual ~CWorld() = default;

private:
	//��ü�� �ƴ� �����ͷ� ������ �����Ѵ�.
	vector<CTerrain*> m_vecTerrain;

private:
	//���η�Ÿ�Ե�
	CTerrain*	m_Water;
	CTerrain*	m_Wall;
	CTerrain*	m_Grass;
	

public:
	HRESULT	Initialize(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eTextureScene, _tchar* _pFilePath = nullptr);
	HRESULT Render();

public:
	HRESULT	Set_Terrain(CTerrain* _pTerrain, POINT& _pt);

public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
