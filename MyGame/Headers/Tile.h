#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CTile final: public CGameObject
{ 
protected:
	explicit CTile() {};
	explicit CTile(CTile& _tile) :CGameObject(_tile) {};
	virtual ~CTile() = default;

public:
	HRESULT Initalize(float _fX, float _fY);
	HRESULT	Render();
	static CTile*	Create(float _fX ,float _fY);
	virtual CGameObject * Clone(void * _param = nullptr) override;



};
END
