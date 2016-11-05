GM_texture
	t_interior(256, 128, 64, 64, "textures/t_interior.bmp"),
	t_icons(128, 64, 32, 32, "textures/t_icons.bmp"),
	t_font(128, 64, 8, 8, "textures/t_font.bmp"),
	t_weapon(512, 256, 256, 256, "textures/t_weapon.bmp"),
	t_enemy(256, 256, 64, 64, "textures/t_enemy.bmp");

void GM_loadTextures()
{
	t_interior.load();
	t_icons.load();
	t_font.load();
	t_weapon.load();
	t_enemy.load();
}

void GM_unloadTextures()
{
	t_interior.unload();
	t_icons.unload();
	t_font.unload();
	t_weapon.unload();
	t_enemy.unload();
}

// Icons pictures
enum textureIcons
{
	TEXTURE_ICONS_AMMO,
	TEXTURE_ICONS_MEDKIT,
	TEXTURE_ICONS_KEY,
	TEXTURE_ICONS_HEART,
	TEXTURE_ICONS_BULLET,
	TEXTURE_ICONS_BULLET_YES,
	TEXTURE_ICONS_BULLET_NO,
	TEXTURE_ICONS_AIM
};

// Icons pictures
enum textureInterior
{
	TEXTURE_INTERIOR_SEWER,
	TEXTURE_INTERIOR_METAL,
	TEXTURE_INTERIOR_PLATE,
	TEXTURE_INTERIOR_CEIL,
	TEXTURE_INTERIOR_WALL,
	TEXTURE_INTERIOR_GLASS,
	TEXTURE_INTERIOR_DOOR,
	TEXTURE_INTERIOR_DOOR_LOCKED
};

// Weapon pictures
enum textureWeapon
{
	TEXTURE_WEAPON_COLD,
	TEXTURE_WEAPON_FIRE
};

// Enemy pictures
enum textureEnemy
{
	TEXTURE_ENEMY_STAND,
	TEXTURE_ENEMY_FIRE,
	TEXTURE_ENEMY_WALK_1,
	TEXTURE_ENEMY_WALK_2,
	TEXTURE_ENEMY_WALK_3,
	TEXTURE_ENEMY_WALK_4,
	TEXTURE_ENEMY_WALK_5,
	TEXTURE_ENEMY_WALK_6,
	TEXTURE_ENEMY_DAMAGE,
	TEXTURE_ENEMY_DIE_1,
	TEXTURE_ENEMY_DIE_2,
	TEXTURE_ENEMY_DIE_3,
	TEXTURE_ENEMY_DIE_4,
	TEXTURE_ENEMY_DIE_5,
	TEXTURE_ENEMY_DIE_6,
	TEXTURE_ENEMY_DIE_7
};