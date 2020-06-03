#pragma once
#include "Base.h"
BEGIN(MyGame)
class CItem;
class CItemFactory : public CBase
{
public:
	enum ITEM_ID
	{
		ITEM_SHORTSWORD,
		ITEM_LONGSWORD,
		ITEM_DAGGER,
		ITEM_IRONSWORD,
		ITEM_BATTLEAXE,
		ITEM_GOLDAXE,
		ITEM_SPEAR,
		ITEM_TRIDENT,
		ITEM_MACE,
		ITEM_LETHERARMOR,
		ITEM_CHAINARMOR,
		ITEM_PLATEARMOR,
		ITEM_IRONARMOR,
		ITEM_DRAGONARMOR,
		ITEM_ARROW,
		ITEM_BOMB,
		ITEM_BOTTLE,
		ITEM_NUCKLE,
		ITEM_REDRING,
		ITEM_HEALPOTION,
		ITEM_FIREPOTION,
		ITEM_PARALYZEPOTION,
		ITEM_POSIONPOTION,
		ITEM_LIGHTNINGWAND,
		ITEM_END
	};
private:
	explicit CItemFactory();
	virtual ~CItemFactory() = default;

public:
	static HRESULT	Make_Prototpyes(PDIRECT3DDEVICE9 _pGraphic_Device);
	static CItem*	Make_Item(BASEDESC _tDesc, ITEM_ID _eID, _int _level);


};
END
