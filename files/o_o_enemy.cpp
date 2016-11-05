GM_OBJECT_o_enemy::GM_OBJECT_o_enemy(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_enemy = this;
	priority = 0;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;
}

void GM_OBJECT_o_enemy::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;

	if (o_enemy == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_enemy = (GM_OBJECT_o_enemy*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_enemy = (GM_OBJECT_o_enemy*)GM_right;
		if (o_enemy == this) o_enemy = (GM_OBJECT_o_enemy*)GM_id();
	}
}

// collision with wall or door
bool GM_OBJECT_o_enemy::placeFree(float x, float y)
{
	with(o_wall)
	{
		if (x + SIZE > o_wall->x)
			if (y + SIZE > o_wall->y)
				if (x - SIZE < o_wall->x + 1)
					if (y - SIZE < o_wall->y + 1)
						return false;
	}

	with(o_door)
	{
		if (!o_door->opened || o_door->position != 1)
			if (x + SIZE > o_door->x)
				if (y + SIZE > o_door->y)
					if (x - SIZE < o_door->x + 1)
						if (y - SIZE < o_door->y + 1)
							return false;
	}

	return true;
}

// taking damage
void GM_OBJECT_o_enemy::getDamage(int damage)
{
	hp -= damage;

	if (hp < 0)
	{
		hp = 0;
		showMessage("Enemy killed!"); // надо поменять
		destroy();
	}
}

void GM_OBJECT_o_enemy::GM_step()
{
}

void GM_OBJECT_o_enemy::GM_draw()
{
	float
		x1 = x - stepX(SIZE, o_hero->xDir + 90),
		x2 = x + stepX(SIZE, o_hero->xDir + 90),
		y1 = y - stepY(SIZE, o_hero->xDir + 90),
		y2 = y + stepY(SIZE, o_hero->xDir + 90),
		z1 = z,
		z2 = z + SIZE * 2;

	glColor3f(1, 1, 1);
	t_enemy.set();
	glBegin(GL_QUADS);
	glTexCoord2f(t_enemy.x2[texture], t_enemy.y2[texture]); glVertex3f(x1, y1, z1);
	glTexCoord2f(t_enemy.x2[texture], t_enemy.y1[texture]); glVertex3f(x1, y1, z2);
	glTexCoord2f(t_enemy.x1[texture], t_enemy.y1[texture]); glVertex3f(x2, y2, z2);
	glTexCoord2f(t_enemy.x1[texture], t_enemy.y2[texture]); glVertex3f(x2, y2, z1);
	glEnd();
}

uint GM_OBJECT_o_enemy::GM_id()
{
	return GM_OBJECT_ID_o_enemy;
}