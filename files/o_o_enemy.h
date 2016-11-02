struct GM_OBJECT_o_enemy : public GM_object
{
	int hp;

	const float SIZE = 0.25;
	const float HEIGHT = 0.6;
	const int HP_MAX = 100;

	static int GM_count;
	GM_OBJECT_o_enemy(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

	bool placeFree(float x, float y);
	void getDamage(int damage);

} *o_enemy = (GM_OBJECT_o_enemy*)GM_OBJECT_ID_o_enemy;

int GM_OBJECT_o_enemy::GM_count;
