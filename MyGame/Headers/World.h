#pragma once

#include "Base.h"

BEGIN(MyGame)

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
	HRESULT	Generate_World(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath);
	HRESULT Render();


public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
