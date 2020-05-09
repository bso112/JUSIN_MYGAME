#pragma once
#include "Module.h"
BEGIN(MyGame)
class CStateCon abstract :public CModule
{
protected:
	explicit CStateCon(LPDIRECT3DDEVICE9 _pGraphic_Device) :CModule(_pGraphic_Device) {};
	explicit CStateCon(CStateCon& _rhs) :CModule(_rhs) {};
	virtual ~CStateCon() = default;

public:
	virtual _int	Start(_bool _canAttack, _bool _isAlerted) = 0;
	//프레임마다 판정 체크
	virtual _int	Update(_bool _canAttack, _bool _isAlerted) = 0;


};
END
