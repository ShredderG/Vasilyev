GM_OBJECT_o_hud::GM_OBJECT_o_hud(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_hud = this;
	priority = 0;
	solid = false;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;
}

GM_OBJECT_o_hud::~GM_OBJECT_o_hud()
{
	if (o_hud == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_hud = (GM_OBJECT_o_hud*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_hud = (GM_OBJECT_o_hud*)GM_right;
		if (o_hud == this) o_hud = (GM_OBJECT_o_hud*)GM_id();
	}
}

void GM_OBJECT_o_hud::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;
}

void GM_OBJECT_o_hud::GM_step()
{
}

void GM_OBJECT_o_hud::GM_draw()
{
}

uint GM_OBJECT_o_hud::GM_id()
{
	return GM_OBJECT_ID_o_hud;
}