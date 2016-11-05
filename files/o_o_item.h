enum itemType : unsigned int
{
	ITEM_AMMO,
	ITEM_MEDKIT,
	ITEM_KEY
};

struct GM_OBJECT_o_item : public GM_object
{
	itemType type = ITEM_AMMO; // redefined after creating
	int angle = 0;

	static const float SIZE;
	static const float HEIGHT;
	static const int AMMO = 12;
	static const int MEDKIT = 50;

	static int GM_count;
	GM_OBJECT_o_item(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();
	void destructor();

} *o_item = (GM_OBJECT_o_item*)GM_OBJECT_ID_o_item;

const float GM_OBJECT_o_item::SIZE = 0.15;
const float GM_OBJECT_o_item::HEIGHT = 0.3;
int GM_OBJECT_o_item::GM_count = 0;