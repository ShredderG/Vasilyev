struct GM_OBJECT_o_hero : public GM_object
{
	float xDir, yDir;
	float height;
	float size;
	int ammo;
	int shootDelay;
	float speed;
	bool key;

	static int GM_count;
	GM_OBJECT_o_hero(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

	bool placeFree(float x, float y);

} *o_hero = (GM_OBJECT_o_hero*)GM_OBJECT_ID_o_hero;

int GM_OBJECT_o_hero::GM_count;
