#pragma once

BEGIN(MyGame)

const unsigned int		g_iWinCX = 1280;
const unsigned int		g_iWinCY = 720;

enum SCENEID { SCENE_STATIC, SCENE_LOADING, SCENE_STAGE, SCENE_END };
enum MODULE { MODULE_VIBUFFER, MODULE_TEXTURE, MODULE_TRANSFORM, MODULE_END };

#define	TILECX 100
#define TILECY 100
#define TILEX 50
#define TILEY 50


END