GM_OBJECT_o_wall::GM_OBJECT_o_wall(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_wall = this;
	priority = 0;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;
}

void GM_OBJECT_o_wall::destructor()
{
	if (o_wall == this)
	{
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

// draw wall
void GM_OBJECT_o_wall::drawWall(float x1, float y1, float z1, float x2, float y2, float z2)
{
	t_interior.set();
	glBegin(GL_QUADS);

	glTexCoord2f(t_interior.x1[texture], t_interior.y2[texture]); glVertex3f(x1, y1, z1);
	glTexCoord2f(t_interior.x1[texture], t_interior.y1[texture]); glVertex3f(x1, y1, z2);
	glTexCoord2f(t_interior.x2[texture], t_interior.y1[texture]); glVertex3f(x2, y2, z2);
	glTexCoord2f(t_interior.x2[texture], t_interior.y2[texture]); glVertex3f(x2, y2, z1);

	glEnd();
}

void GM_OBJECT_o_wall::GM_draw()
{
	drawWall(x + 1, y, z, x, y, z + 1);
	drawWall(x + 1, y + 1, z, x + 1, y, z + 1);
	drawWall(x, y + 1, z, x + 1, y + 1, z + 1);
	drawWall(x, y, z, x, y + 1, z + 1);
}

uint GM_OBJECT_o_wall::GM_id()
{
	return GM_OBJECT_ID_o_wall;
}