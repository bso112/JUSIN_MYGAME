#pragma once
#include "Buff.h"
BEGIN(MyGame)
class CParalyze final :public CBuff
{

private:
	explicit CParalyze() :CBuff() {};
	virtual ~CParalyze() = default;

public:
	virtual HRESULT Initialize(void* _pArg);

protected:
	virtual void OnAct(CCharacter* _pTarget) override;

public:
	static CParalyze* Create(void* _pArg);
	virtual void Free() override;

};
END
