#pragma once
#include "Base.h"

BEGIN(MyGame)
class CCharacter;
class CBuff abstract : public CBase
{
public:
	CBuff();
	virtual ~CBuff();

public:
	enum BuffType {TYPE_POSITIVE, TYPE_NEGATIVE, TYPE_END};

protected:
	BuffType	m_eType;
	CCharacter* m_pTarget;

public:
	void	AttachTo(CCharacter* _pCharacter);
	void	Detach();
	virtual void	Act() = 0;
};
END
