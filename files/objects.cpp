enum
{
	GM_OBJECT_ID_o_wall,
	GM_OBJECT_ID_o_item,
	GM_OBJECT_ID_o_hud,
	GM_OBJECT_ID_o_hero,
	GM_OBJECT_ID_o_floor,
	GM_OBJECT_ID_o_enemy,
	GM_OBJECT_ID_o_door,
	GM_OBJECT_ID_o_bullet
};

#include "o_o_wall.h"
#include "o_o_item.h"
#include "o_o_hud.h"
#include "o_o_hero.h"
#include "o_o_floor.h"
#include "o_o_enemy.h"
#include "o_o_door.h"
#include "o_o_bullet.h"

GM_object *objectCreate(float x, float y, float z, GM_object *GM_ptr)
{
	GM_object *GM_new = NULL;
	if (GM_ptr == o_wall) GM_new = new GM_OBJECT_o_wall(x, y, z);
	if (GM_ptr == o_item) GM_new = new GM_OBJECT_o_item(x, y, z);
	if (GM_ptr == o_hud) GM_new = new GM_OBJECT_o_hud(x, y, z);
	if (GM_ptr == o_hero) GM_new = new GM_OBJECT_o_hero(x, y, z);
	if (GM_ptr == o_floor) GM_new = new GM_OBJECT_o_floor(x, y, z);
	if (GM_ptr == o_enemy) GM_new = new GM_OBJECT_o_enemy(x, y, z);
	if (GM_ptr == o_door) GM_new = new GM_OBJECT_o_door(x, y, z);
	if (GM_ptr == o_bullet) GM_new = new GM_OBJECT_o_bullet(x, y, z);
	//if (GM_ptr < (GM_object*)0x0000FFFF) return NULL;
	GM_new->GM_insert(GM_ptr);
	return GM_new;
}

#include "o_o_wall.cpp"
#include "o_o_item.cpp"
#include "o_o_hud.cpp"
#include "o_o_hero.cpp"
#include "o_o_floor.cpp"
#include "o_o_enemy.cpp"
#include "o_o_door.cpp"
#include "o_o_bullet.cpp"
