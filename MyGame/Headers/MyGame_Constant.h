#pragma once

BEGIN(MyGame)

const unsigned int		g_iWinCX = 1280;
const unsigned int		g_iWinCY = 720;
#define MYDEBUG

#define TILECX 25
#define TILECY 25
#define WORLDX 400
#define WORLDY 400
//레벨 최대 층수
#define MAX_DEPTH 2


#define OBJ_NOEVENT 0
#define OBJ_CLICKED 1

enum SCENEID { SCENE_STATIC, SCENE_MENU, SCENE_LOADING, SCENE_CHARACTER_SELECT, SCENE_EDITOR, SCENE_STAGE, SCENE_END };
enum TIER	{ TIER_COMMON, TIER_RARE, TIER_LAGEND, TIER_END};
enum BODYPART { BODY_HAND, BODY_TORSO, BODY_FINGER, BODY_ARTEFACT, BODY_END };

#define TURN_NOEVENT	98
#define TURN_END		99

#define AC_DROP			L"DROP"
#define AC_THROW		L"THROW"
#define AC_EAT			L"EAT"
#define AC_EQUIP		L"EQUIP"
#define AC_UNEQUIP		L"UNEQUIP"
#define AC_READ			L"READ"
#define AC_ZAP			L"ZAP"
#define MSG_WIN(OTHER)	 new wstring(L"당신은 " + wstring(OTHER) + L"을(를) 쓰려뜨렸다!")
#define MSG_DAMAGE(VICTIME, ATTACKER, DAMAGE) new wstring(wstring(VICTIME) + L"은 " + wstring(ATTACKER) + L"에게 " + wstring(DAMAGE) + L"데미지를 받았다.")
#define MSG_PICK(OTHER)	 new wstring(L"당신은 " + wstring(OTHER) + L"을(를) 주웠다.")




END