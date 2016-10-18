GM_OBJECT_o_floor::GM_OBJECT_o_floor(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_floor = this;
	priority = 0;
	solid = false;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;
}

GM_OBJECT_o_floor::~GM_OBJECT_o_floor()
{
	if (o_floor == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_floor = (GM_OBJECT_o_floor*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_floor = (GM_OBJECT_o_floor*)GM_right;
		if (o_floor == this) o_floor = (GM_OBJECT_o_floor*)GM_id();
	}
}

void GM_OBJECT_o_floor::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;
}

void GM_OBJECT_o_floor::GM_step()
{
}

void GM_OBJECT_o_floor::GM_draw()
{
	t_floor.set();

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); glVertex3f(x, y, z);
	glTexCoord2f(1, 0); glVertex3f(x + 1, y, z);
	glTexCoord2f(1, 1); glVertex3f(x + 1, y + 1, z);
	glTexCoord2f(0, 1); glVertex3f(x, y + 1, z);

	glEnd();
}

uint GM_OBJECT_o_floor::GM_id()
{
	return GM_OBJECT_ID_o_floor;
}