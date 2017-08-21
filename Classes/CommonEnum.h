#ifndef _COMMON_ENUM_H_
#define _COMMON_ENUM_H_

#include <map>
#include "cocos2d.h"


enum MsgType
{
	msg_destroy_self,
	msg_reply_bullet_arrived,
	msg_on_attack,
	msg_enemy_died,
};

enum ObjectType 
{
	bullet = 0x0001,
	stone_bullet = 0x0002,
	ship = 0x0004,
	environment = 0x0008,
	hero = 0x0010,
	creep = 0x0020,
	camp_axis = 0x0040,
	camp_allies = 0x0080,
	tower = 0x0100
};

enum ComponentType
{
	comp_null_type = 0x0000,
	comp_communicator = 0x0001,
	comp_moving = 0x0002,
	comp_displayer = 0x0004,
	comp_battle = 0x0008,
	comp_controller_test = 0x0010,
	comp_shadow = 0x0020,
};

enum AttackBonus
{
	//普攻
	normal	= 0x0001,
	//暴击
	crit	= 0x0002,
	//减速
	slow	= 0x0004,
	//晕眩
	stun	= 0x0008,
	//持续伤害
	dot		= 0x0010
	//to do, more types
};

enum Debuf
{
	stunned = 0x0001,
	burned = 0x0002
};

//hatred priority
const int hatred_creep = 3;
const int hatred_hero = 2;
const int hatred_tower = 1;

//math
#define PI 3.1415926
const float max_float = 3.402823466e+38F;
const float precision = 0.001f;

//sys
const float FPS = 60.0f;
const float ADT = 1.0f / FPS;
const int next_frame = 1;
const float screen_width = 1366.0f;
const float screen_height = 768.0f;

//map size
const int WHOLE_MAP_WIDTH = 8000;
const int WHOLE_MAP_HEIGHT = 8000;
const int HERO_RADIUS = 80;
const cocos2d::Vec2 illegal_aim = cocos2d::Vec2(-999.0f, -999.0f);

//weight for force
const float BrakingWeight = 0.1f;
const float SeekWeight = 1.0f;
const float FleeWeight = 1.0f;
const float ObsAvoiWeight = 0.05f;
const float PursuitWeight = 1.0f;
const float EvadeWeight = 1.0f;
const float SeparationWeight = 2.0f;
const size_t smoothing_frames = 20;
const float seek_offset_precision = 1.0f;
const float separation_dist = 160.0f;

//id，从1-100为系统保留id
const int illegal_id = -9999;
const int selfMsgReceiver_id = 1;
const int hero_id = 2;

//depth,z_order
const int bg_zorder = -10;
//define [0,100) as world depth
const int world_below_sea_zorder = 0;
const int world_sea_zorder = 10;
const int world_above_sea_zorder = 20;
const int world_air_zorder = 30;


#define CREATE_SPRITE(__filename__) (Sprite::create(__filename__))

#endif
