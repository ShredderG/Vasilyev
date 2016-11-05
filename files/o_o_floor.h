struct GM_OBJECT_o_floor : public GM_object
{
	int texture = TEXTURE_INTERIOR_METAL;

	static int GM_count;
	GM_OBJECT_o_floor(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

} *o_floor = (GM_OBJECT_o_floor*)GM_OBJECT_ID_o_floor;

int GM_OBJECT_o_floor::GM_count = 0;