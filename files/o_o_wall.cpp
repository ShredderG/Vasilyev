GM_OBJECT_o_wall::GM_OBJECT_o_wall(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_wall = this;
	priority = 0;
	solid = false;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;
	height = 1;
}

GM_OBJECT_o_wall::~GM_OBJECT_o_wall()
{
	if (o_wall == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_wall = (GM_OBJECT_o_wall*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_wall = (GM_OBJECT_o_wall*)GM_right;
		if (o_wall == this) o_wall = (GM_OBJECT_o_wall*)GM_id();
	}
}

void GM_OBJECT_o_wall::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;
}

void GM_OBJECT_o_wall::GM_step()
{
}

void GM_OBJECT_o_wall::GM_draw()
{
	drawWall(x + 1, y, z, x, y, z + height);
	drawWall(x + 1, y + 1, z, x + 1, y, z + height);
	drawWall(x, y + 1, z, x + 1, y + 1, z + height);
	drawWall(x, y, z, x, y + 1, z + height);
}

uint GM_OBJECT_o_wall::GM_id()
{
	return GM_OBJECT_ID_o_wall;
}