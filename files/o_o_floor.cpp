GM_OBJECT_o_floor::GM_OBJECT_o_floor(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_floor = this;
	priority = 0;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;

	texture = 0;
}

void GM_OBJECT_o_floor::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;

	if (o_floor == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_floor = (GM_OBJECT_o_floor*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_floor = (GM_OBJECT_o_floor*)GM_right;
		if (o_floor == this) o_floor = (GM_OBJECT_o_floor*)GM_id();
	}
}

void GM_OBJECT_o_floor::GM_step()
{
}

void GM_OBJECT_o_floor::GM_draw()
{
	t_floor.set();

	glBegin(GL_QUADS);

	glTexCoord2f(t_floor.x1[texture], t_floor.y1[texture]); glVertex3f(x, y, z);
	glTexCoord2f(t_floor.x2[texture], t_floor.y1[texture]); glVertex3f(x + 1, y, z);
	glTexCoord2f(t_floor.x2[texture], t_floor.y2[texture]); glVertex3f(x + 1, y + 1, z);
	glTexCoord2f(t_floor.x1[texture], t_floor.y2[texture]); glVertex3f(x, y + 1, z);

	glEnd();
}

uint GM_OBJECT_o_floor::GM_id()
{
	return GM_OBJECT_ID_o_floor;
}