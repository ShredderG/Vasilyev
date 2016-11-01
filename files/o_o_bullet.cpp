GM_OBJECT_o_bullet::GM_OBJECT_o_bullet(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_bullet = this;
	priority = 0;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;

	xDir = yDir = 0;
	speed = 0.1;
	size = 0.05;
}

void GM_OBJECT_o_bullet::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;

	if (o_bullet == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_bullet = (GM_OBJECT_o_bullet*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_bullet = (GM_OBJECT_o_bullet*)GM_right;
		if (o_bullet == this) o_bullet = (GM_OBJECT_o_bullet*)GM_id();
	}
}

void GM_OBJECT_o_bullet::GM_step()
{
	x += stepX(speed, xDir, yDir);
	y += stepY(speed, xDir, yDir);
	z += stepZ(speed, xDir, yDir);

	// collision with floor/roof
	if (z < 0) destroy();
	if (z > 1) destroy();

	// collision with wall
	with(o_wall)
	{
		if (x > o_wall->x)
			if (y > o_wall->y)
				if (x < o_wall->x + 1)
					if (y < o_wall->y + 1)
					{
						destroy();
						break;
					}
	}

	// collision with door
	with(o_door)
	{
		if (!o_door->opened || o_door->position != 1)
			if (x > o_door->x)
				if (y > o_door->y)
					if (x < o_door->x + 1)
						if (y < o_door->y + 1)
						{
							destroy();
							break;
						}
	}
}

void GM_OBJECT_o_bullet::GM_draw()
{
	glDisable(GL_TEXTURE_2D); // можно удалить, если добавить текстуру

	float
		x1 = x - stepX(size, o_hero->xDir + 90),
		x2 = x + stepX(size, o_hero->xDir + 90),
		y1 = y - stepY(size, o_hero->xDir + 90),
		y2 = y + stepY(size, o_hero->xDir + 90),
		z1 = z - size,
		z2 = z + size;

	// текстуру надо добавить
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, z2);
	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y2, z1);
	glEnd();

	glEnable(GL_TEXTURE_2D); // удалить
}

uint GM_OBJECT_o_bullet::GM_id()
{
	return GM_OBJECT_ID_o_bullet;
}