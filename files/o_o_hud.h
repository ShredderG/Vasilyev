struct GM_OBJECT_o_hud : public GM_object
{
	string text = "";
	int message_time = 0;
	int hit_time = 0;

	static const int FONT_SIZE = 32;
	static const int FONT_SIZE_SMALL = FONT_SIZE / 2;
	static const int ICON_SIZE = 64;
	static const int WEAPON_SIZE = 512;
	static const int MESSAGE_TIME = 2 * GM_FPS;
	static const int HIT_TIME = 1 * GM_FPS;

	static int GM_count;
	GM_OBJECT_o_hud(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

	// show message
	void message(string text_new);

	// draw text 2d
	void drawText(string text, int x, int y, int size);

	// draw a picture 2d
	void drawPic2d(GM_texture &texture, int image, int x, int y, int width, int height);

} *o_hud = (GM_OBJECT_o_hud*)GM_OBJECT_ID_o_hud;

int GM_OBJECT_o_hud::GM_count = 0;