#pragma once

BEGIN(MyGame)

class CGameObject;

const unsigned int		g_iWinCX = 512;
const unsigned int		g_iWinCY = 720;


#define TILECX 25
#define TILECY 25

#define OBJ_NOEVENT 0
#define OBJ_CLICKED 1

enum SCENEID { SCENE_STATIC, SCENE_MENU, SCENE_CHARACTER_SELECT, SCENE_EDITOR, SCENE_STAGE, SCENE_END };
enum TIER	{ TIER_COMMON, TIER_RARE, TIER_LAGEND, TIER_END};

extern int g_iTileX;
extern CGameObject* g_pSelected;

END