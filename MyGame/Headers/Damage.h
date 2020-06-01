#pragma once
#include "Buff.h"
BEGIN(MyGame)
class CDamage final :public CBuff
{

private:
	explicit CDamage():CBuff() {};
	virtual ~CDamage()=default;

public:
	virtual HRESULT Initialize(void* _pArg);

protected:
	virtual void OnAct(CCharacter* _pTarget) override;

public:
	static CDamage* Create(void* _pArg = nullptr);
	virtual void Free() override;

};
END
