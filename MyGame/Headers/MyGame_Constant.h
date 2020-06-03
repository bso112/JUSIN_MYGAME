#pragma once

BEGIN(MyGame)

const unsigned int		g_iWinCX = 1280;
const unsigned int		g_iWinCY = 720;
#define MYDEBUG

#define TILECX 25
#define TILECY 25
#define WORLDX 400
#define WORLDY 400
//���� �ִ� ����
#define MAX_DEPTH 2


#define OBJ_NOEVENT 0
#define OBJ_CLICKED 1

enum SCENEID { SCENE_STATIC, SCENE_MENU, SCENE_LOADING, SCENE_CHARACTER_SELECT, SCENE_EDITOR, SCENE_STAGE, SCENE_END };
enum TIER { TIER_COMMON, TIER_RARE, TIER_LAGEND, TIER_END };
enum BODYPART { BODY_HAND, BODY_TORSO, BODY_FINGER, BODY_ARTEFACT, BODY_END };

#define TURN_NOEVENT	98
#define TURN_END		99

#define AC_DROP			L"������"
#define AC_THROW		L"������"
#define AC_EAT			L"�Դ´�"
#define AC_DRINK		L"���Ŵ�"
#define AC_EQUIP		L"�����Ѵ�"
#define AC_UNEQUIP		L"�����Ѵ�"
#define AC_READ			L"�д´�"
#define AC_ZAP			L"����Ѵ�"
#define MSG_WIN(OTHER)	 new wstring(L"����� " + wstring(OTHER) + L" ��(��) �����߷ȴ�!")
#define MSG_DAMAGE(VICTIME, ATTACKER, DAMAGE) new wstring(wstring(VICTIME) + L"�� " + wstring(ATTACKER) + L" ���� " + wstring(DAMAGE) + L"�������� �޾Ҵ�.")
#define MSG_PICK(OTHER)	 new wstring(L"����� " + wstring(OTHER) + L" ��(��) �ֿ���.")
#define MSG_EAT(OTHER)	 new wstring(L"����� " + wstring(OTHER) + L" ��(��) �Ծ���. ���� ���־���!")
#define MSG_EXHAUST(OTHER) new wstring(L"�ƹ��ϵ� �Ͼ�� �ʾҴ�. " + wstring(OTHER) + L" ��(��) �� ������� �ϴ�.")



END