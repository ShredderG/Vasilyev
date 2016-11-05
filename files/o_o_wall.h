struct GM_OBJECT_o_wall : public GM_object
{
	int texture = TEXTURE_INTERIOR_WALL;

	static int GM_count;
	GM_OBJECT_o_wall(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();
	void destructor();

	void drawWall(float x1, float y1, float z1, float x2, float y2, float z2);

} *o_wall = (GM_OBJECT_o_wall*)GM_OBJECT_ID_o_wall;

int GM_OBJECT_o_wall::GM_count = 0;