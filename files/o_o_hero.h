struct GM_OBJECT_o_hero : public GM_object
{
	float
		xDir = 0,
		yDir = 90;
	int shootDelay = 0;
	int reloadDelay = 0;
	int hp = HP_MAX;
	int ammo = AMMO_MAX,
		ammoTotal = AMMO_START;
	bool key = false;
	int bobbing = 0;
	float zDeath = 0;

	static const float HEIGHT;
	static const float SIZE;
	static const float SPEED;
	static const int HP_MAX = 100;
	static const int AMMO_MAX = 12;
	static const int AMMO_TOTAL_MAX = 48;
	static const int AMMO_START = 12;
	static const int SHOOT_DELAY = 10;
	static const int RELOAD_DELAY = 20;
	static const int BOBBING_MAX = 25;

	static int GM_count;
	GM_OBJECT_o_hero(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();
	void destructor();
	
	// collision check
	bool placeFree(float x, float y);

	// taking damage
	void getDamage(int damage);

} *o_hero = (GM_OBJECT_o_hero*)GM_OBJECT_ID_o_hero;

const float GM_OBJECT_o_hero::HEIGHT = 0.5;
const float GM_OBJECT_o_hero::SIZE = 0.25;
const float GM_OBJECT_o_hero::SPEED = 0.045;
int GM_OBJECT_o_hero::GM_count = 0;