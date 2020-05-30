#pragma once
#include "Buff.h"
BEGIN(MyGame)
class CBurn final :public CBuff
{

private:
	explicit CBurn():CBuff() {};
	virtual ~CBurn()=default;

public:
	virtual HRESULT Initialize(void* _pArg);

protected:
	virtual void OnAct(CCharacter* _pTarget) override;

public:
	static CBurn* Create(void* _pArg = nullptr);
	virtual void Free() override;

};
END
