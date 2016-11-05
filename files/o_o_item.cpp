GM_OBJECT_o_item::GM_OBJECT_o_item(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_item = this;
	priority = 0;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;
}

void GM_OBJECT_o_item::destructor()
{
	if (o_item == this)
	{
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_item = (GM_OBJECT_o_item*)GM_right;
		if (o_item == this) o_item = (GM_OBJECT_o_item*)GM_id();
	}
}

void GM_OBJECT_o_item::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;
}

void GM_OBJECT_o_item::GM_step()
{
	angle++;
	if (angle >= 360) angle = 0;
}

void GM_OBJECT_o_item::GM_draw()
{
	float
		x1 = x - stepX(SIZE, angle),
		x2 = x + stepX(SIZE, angle),
		y1 = y - stepY(SIZE, angle),
		y2 = y + stepY(SIZE, angle),
		z1 = z - SIZE + HEIGHT + cos(angle / 28.647889756541160438399077407053) / 8.0,
		z2 = z + SIZE + HEIGHT + cos(angle / 28.647889756541160438399077407053) / 8.0;

	t_icons.set();

	glBegin(GL_QUADS);
	glTexCoord2f(t_icons.x1[type], t_icons.y2[type]); glVertex3f(x1, y1, z1);
	glTexCoord2f(t_icons.x1[type], t_icons.y1[type]); glVertex3f(x1, y1, z2);
	glTexCoord2f(t_icons.x2[type], t_icons.y1[type]); glVertex3f(x2, y2, z2);
	glTexCoord2f(t_icons.x2[type], t_icons.y2[type]); glVertex3f(x2, y2, z1);
	
	glTexCoord2f(t_icons.x1[type], t_icons.y1[type]); glVertex3f(x1, y1, z2);
	glTexCoord2f(t_icons.x1[type], t_icons.y2[type]); glVertex3f(x1, y1, z1);
	glTexCoord2f(t_icons.x2[type], t_icons.y2[type]); glVertex3f(x2, y2, z1);
	glTexCoord2f(t_icons.x2[type], t_icons.y1[type]); glVertex3f(x2, y2, z2);

	glEnd();
}

uint GM_OBJECT_o_item::GM_id()
{
	return GM_OBJECT_ID_o_item;
}