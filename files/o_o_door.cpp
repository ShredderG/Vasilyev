GM_OBJECT_o_door::GM_OBJECT_o_door(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_door = this;
	priority = 0;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;

	texture = 0;
	locked = false;
	opened = false;
	position = 0;
}

void GM_OBJECT_o_door::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;

	if (o_door == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_door = (GM_OBJECT_o_door*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_door = (GM_OBJECT_o_door*)GM_right;
		if (o_door == this) o_door = (GM_OBJECT_o_door*)GM_id();
	}
}

void GM_OBJECT_o_door::GM_step()
{
	if (opened)
	{
		if (position < 1) position += 0.05;
	}
	else
	{
		if (position > 0) position -= 0.05;
	}
}

void GM_OBJECT_o_door::GM_draw()
{
	drawWall(x + 1, y, z + position, x, y, z + 1 + position);
	drawWall(x + 1, y + 1, z + position, x + 1, y, z + 1 + position);
	drawWall(x, y + 1, z + position, x + 1, y + 1, z + 1 + position);
	drawWall(x, y, z + position, x, y + 1, z + 1 + position);
	// надо низ двери нарисовать еще
}

uint GM_OBJECT_o_door::GM_id()
{
	return GM_OBJECT_ID_o_door;
}