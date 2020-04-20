#pragma once
#include "Scene.h"

BEGIN(MyGame)
class CCharacterSelect final : public CScene
{
private:
	explicit CCharacterSelect(PDIRECT3DDEVICE9 _pGraphicDevice) :CScene(_pGraphicDevice) {};
	virtual ~CCharacterSelect() = default;

public:
	static CCharacterSelect* Create(PDIRECT3DDEVICE9 _pGraphicDevice);
};

END