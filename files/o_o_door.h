struct GM_OBJECT_o_door : public GM_object
{
	int texture = TEXTURE_INTERIOR_DOOR;
	bool locked = false;
	bool opened = false;
	float position = 0;

	static int GM_count;
	GM_OBJECT_o_door(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

	// draw wall
	void drawWall(float x1, float y1, float z1, float x2, float y2, float z2);

} *o_door = (GM_OBJECT_o_door*) GM_OBJECT_ID_o_door;

int GM_OBJECT_o_door::GM_count = 0;