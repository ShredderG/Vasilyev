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
	x += stepX(SPEED, xDir, yDir);
	y += stepY(SPEED, xDir, yDir);
	z += stepZ(SPEED, xDir, yDir);

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

	// collision with hero
	with(o_hero) // на случай, если героя не существует
	{
		if (o_hero->hp > 0)
			if (x > o_hero->x - o_hero->SIZE)
				if (y > o_hero->y - o_hero->SIZE)
					if (x < o_hero->x + o_hero->SIZE)
						if (y < o_hero->y + o_hero->SIZE)
							if (z > o_hero->z)
								if (z < o_hero->z + o_hero->HEIGHT)
								{
									o_hero->getDamage(DAMAGE);
									destroy();
									break;
								}
	}

	// collision with enemy
	with(o_enemy)
	{
		if (o_enemy->hp > 0)
			if (x > o_enemy->x - o_enemy->SIZE)
				if (y > o_enemy->y - o_enemy->SIZE)
					if (x < o_enemy->x + o_enemy->SIZE)
						if (y < o_enemy->y + o_enemy->SIZE)
							if (z > o_enemy->z)
								if (z < o_enemy->z + o_enemy->HEIGHT)
								{
									o_enemy->getDamage(DAMAGE);
									destroy();
									break;
								}
	}
}

void GM_OBJECT_o_bullet::GM_draw()
{
	glDisable(GL_TEXTURE_2D); // можно удалить, если добавить текстуру

	float
		x1 = x - stepX(SIZE, o_hero->xDir + 90),
		x2 = x + stepX(SIZE, o_hero->xDir + 90),
		y1 = y - stepY(SIZE, o_hero->xDir + 90),
		y2 = y + stepY(SIZE, o_hero->xDir + 90),
		z1 = z - SIZE,
		z2 = z + SIZE;

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