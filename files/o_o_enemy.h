struct GM_OBJECT_o_enemy : public GM_object
{
	enum stageType
	{
		STAND,
		FIRE,
		WALK,
		DAMAGE,
		DIE
	};

	int hp = HP_MAX;
	int texture = TEXTURE_ENEMY_STAND;
	int stage = STAND;
	int stageTime = 10;
	float direction = 0;

	static const float SPEED;
	static const float SIZE;
	static const float HEIGHT;
	static const int HP_MAX = 100;

	static int GM_count;
	GM_OBJECT_o_enemy(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();
	void destructor();

	// hero in vision
	bool heroInSight(float distance);

	// collision check
	bool placeFree(float x, float y);

	// taking damage
	void getDamage(int damage);

} *o_enemy = (GM_OBJECT_o_enemy*)GM_OBJECT_ID_o_enemy;

const float GM_OBJECT_o_enemy::SPEED = 0.03;
const float GM_OBJECT_o_enemy::SIZE = 0.4;
const float GM_OBJECT_o_enemy::HEIGHT = 0.8;
int GM_OBJECT_o_enemy::GM_count = 0;