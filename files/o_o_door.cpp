GM_OBJECT_o_door::GM_OBJECT_o_door(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_door = this;
	priority = 0;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;
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

	texture = locked ? TEXTURE_INTERIOR_DOOR_LOCKED : TEXTURE_INTERIOR_DOOR;
}

// draw wall
void GM_OBJECT_o_door::drawWall(float x1, float y1, float z1, float x2, float y2, float z2)
{
	t_interior.set();
	glBegin(GL_QUADS);

	glTexCoord2f(t_interior.x1[texture], t_interior.y2[texture]); glVertex3f(x1, y1, z1);
	glTexCoord2f(t_interior.x1[texture], t_interior.y1[texture]); glVertex3f(x1, y1, z2);
	glTexCoord2f(t_interior.x2[texture], t_interior.y1[texture]); glVertex3f(x2, y2, z2);
	glTexCoord2f(t_interior.x2[texture], t_interior.y2[texture]); glVertex3f(x2, y2, z1);

	glEnd();
}

void GM_OBJECT_o_door::GM_draw()
{
	drawWall(x + 1, y, z + position, x, y, z + 1 + position);
	drawWall(x + 1, y + 1, z + position, x + 1, y, z + 1 + position);
	drawWall(x, y + 1, z + position, x + 1, y + 1, z + 1 + position);
	drawWall(x, y, z + position, x, y + 1, z + 1 + position);
	
	// ceil
	glBegin(GL_QUADS);

	glTexCoord2f(t_interior.x1[TEXTURE_INTERIOR_CEIL], t_interior.y1[TEXTURE_INTERIOR_CEIL]); glVertex3f(x, y, z + position);
	glTexCoord2f(t_interior.x2[TEXTURE_INTERIOR_CEIL], t_interior.y1[TEXTURE_INTERIOR_CEIL]); glVertex3f(x, y + 1, z + position);
	glTexCoord2f(t_interior.x2[TEXTURE_INTERIOR_CEIL], t_interior.y2[TEXTURE_INTERIOR_CEIL]); glVertex3f(x + 1, y + 1, z + position);
	glTexCoord2f(t_interior.x1[TEXTURE_INTERIOR_CEIL], t_interior.y2[TEXTURE_INTERIOR_CEIL]); glVertex3f(x + 1, y, z + position);

	glEnd();
}

uint GM_OBJECT_o_door::GM_id()
{
	return GM_OBJECT_ID_o_door;
}