struct GM_OBJECT_o_enemy : public GM_object
{

	static int GM_count;
	GM_OBJECT_o_enemy(float GM_x, float GM_y, float GM_z);
	~GM_OBJECT_o_enemy();
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

} *o_enemy = (GM_OBJECT_o_enemy*)GM_OBJECT_ID_o_enemy;

int GM_OBJECT_o_enemy::GM_count;
