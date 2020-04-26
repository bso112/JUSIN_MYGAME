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
	//객체가 아닌 포인터로 지형을 구성한다.
	vector<CTerrain*> m_vecTerrain;

private:
	//프로로타입들
	CTerrain*	m_Water;
	CTerrain*	m_Wall;
	CTerrain*	m_Grass;
	

public:
	HRESULT	Initialize(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eTextureScene, _tchar* _pFilePath = nullptr);
	HRESULT Render();

public:
	HRESULT	Set_Terrain(CTerrain* _pTerrain, POINT& _pt);

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
