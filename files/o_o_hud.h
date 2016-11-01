struct GM_OBJECT_o_hud : public GM_object
{

	static int GM_count;
	GM_OBJECT_o_hud(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

} *o_hud = (GM_OBJECT_o_hud*)GM_OBJECT_ID_o_hud;

int GM_OBJECT_o_hud::GM_count;
