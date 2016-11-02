struct GM_OBJECT_o_hero : public GM_object
{
	float xDir, yDir;
	int shootDelay;
	int hp;
	int ammo, ammoTotal;
	bool key;

	const float HEIGHT = 0.6;
	const float SIZE = 0.25;
	const float SPEED = 0.05;
	const int HP_MAX = 100;
	const int AMMO_MAX = 8;

	static int GM_count;
	GM_OBJECT_o_hero(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

	bool placeFree(float x, float y);
	void getDamage(int damage);

} *o_hero = (GM_OBJECT_o_hero*)GM_OBJECT_ID_o_hero;

int GM_OBJECT_o_hero::GM_count;
