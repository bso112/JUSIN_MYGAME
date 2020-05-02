#pragma once
#include "Base.h"

BEGIN(MyGame)
/*
����, �������� �����ϰ� �������ִ� Ŭ����
*/
class CSpawner : public CBase
{
private:
	explicit CSpawner();
	virtual ~CSpawner() = default;

public:
	static HRESULT Ready_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eScene);
	static HRESULT Spawn(SCENEID _eScene);


	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
