struct GM_OBJECT_o_door : public GM_object
{

	static int GM_count;
	GM_OBJECT_o_door(float GM_x, float GM_y, float GM_z);
	~GM_OBJECT_o_door();
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

} *o_door = (GM_OBJECT_o_door*) GM_OBJECT_ID_o_door;

	int GM_OBJECT_o_door::GM_count;
