#pragma once

BEGIN(MyGame)

const unsigned int		g_iWinCX = 1280;
const unsigned int		g_iWinCY = 720;
#define MYDEBUG

#define TILECX 25
#define TILECY 25

//레벨 최대 층수
#define DEPTH 3


#define OBJ_NOEVENT 0
#define OBJ_CLICKED 1

enum SCENEID { SCENE_STATIC, SCENE_MENU, SCENE_CHARACTER_SELECT, SCENE_EDITOR, SCENE_STAGE, SCENE_END };
enum TIER	{ TIER_COMMON, TIER_RARE, TIER_LAGEND, TIER_END};

#define TURN_NOEVENT	98
#define TURN_END		99

#define AC_DROP			L"DROP"
#define AC_THROW		L"THROW"
#define AC_EAT			L"EAT"
#define AC_EQUIP		L"EQUIP"
#define AC_UNEQUIP		L"UNEQUIP"
#define AC_READ			L"READ"



END