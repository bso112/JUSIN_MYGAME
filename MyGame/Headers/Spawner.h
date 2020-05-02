#pragma once
#include "Base.h"

BEGIN(MyGame)
/*
몬스터, 아이템을 랜덤하게 스폰해주는 클래스
*/
class CSpawner : public CBase
{
private:
	explicit CSpawner();
	virtual ~CSpawner() = default;

public:
	static HRESULT Ready_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eScene);
	static HRESULT Spawn(SCENEID _eScene);


	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
