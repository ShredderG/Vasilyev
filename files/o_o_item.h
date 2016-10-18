struct GM_OBJECT_o_item : public GM_object
{

	static int GM_count;
	GM_OBJECT_o_item(float GM_x, float GM_y, float GM_z);
	~GM_OBJECT_o_item();
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

} *o_item = (GM_OBJECT_o_item*)GM_OBJECT_ID_o_item;

int GM_OBJECT_o_item::GM_count;
