#pragma once

BEGIN(MyGame)

class CGameObject;

//백버퍼 사이즈
const unsigned int		g_iWinCX = 800;
const unsigned int		g_iWinCY = 600;


const unsigned int		g_iFormViewCX = 300;
const unsigned int		g_iFormViewCY = 600;

#define TILECX 130
#define TILECY 68

#define OBJ_NOEVENT 0
#define OBJ_CLICKED 1

enum SCENEID { SCENE_STATIC, SCENE_MENU, SCENE_CHARACTER_SELECT, SCENE_EDITOR, SCENE_STAGE, SCENE_END };
enum TIER	{ TIER_COMMON, TIER_RARE, TIER_LAGEND, TIER_END};

extern int g_iTileX;
extern CGameObject* g_pSelected;
extern int g_TextureIndex;

END