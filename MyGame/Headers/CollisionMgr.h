#pragma once
#include "Base.h"

BEGIN(MyGame)
class CGameObject;
class CCollisionMgr : public CBase
{
private:
	explicit CCollisionMgr();
	virtual ~CCollisionMgr() = default;

public:
	//사각형 충돌함수
	static bool Collision_Rect(list<CGameObject*> _Dst, list<CGameObject*> _Src);
	static bool	GameObjectInTile(list<CGameObject*> _listObj, list<CGameObject*> _listTerrain);
	static bool	Collision(list<CGameObject*> _Dst, list<CGameObject*> _Src, bool _bisCollided);

public:
	//static bool Intersect_LIne(const LINE _line1, const LINE _line2, Vector2& _result);

public:
	virtual void Free() override;

};
END

