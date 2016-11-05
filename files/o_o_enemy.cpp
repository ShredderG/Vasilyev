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

void GM_OBJECT_o_enemy::destructor()
{
	if (o_enemy == this)
	{
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_enemy = (GM_OBJECT_o_enemy*)GM_right;
		if (o_enemy == this) o_enemy = (GM_OBJECT_o_enemy*)GM_id();
	}
}

void GM_OBJECT_o_enemy::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;
}

// hero in vision
bool GM_OBJECT_o_enemy::heroInSight(float distance)
{
	// if too far away
	float d;
	if ((d = pointDistance(x, y, o_hero->x, o_hero->y)) > distance) return false;
	if (d < distance) distance = d;
	float direction = pointDirection(x, y, o_hero->x, o_hero->y);

	// check for walls and doors
	for (int i = 2; i < distance; i++)
	{
		if (!placeFree(x + stepX(i, direction), y + stepY(i, direction)))
			return false;
	}

	return true;
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
		if (!o_door->opened || o_door->position < 1)
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

	stage = DAMAGE;
	stageTime = 10;

	if (hp <= 0)
	{
		sndPlaySound("sounds/s_death.wav", SND_FILENAME | SND_ASYNC);
		hp = 0;
		stage = DIE;
		stageTime = 90;
	}
	else
	{
		sndPlaySound("sounds/s_damage.wav", SND_FILENAME | SND_ASYNC);
	}
}

void GM_OBJECT_o_enemy::GM_step()
{
	if (stageTime > 0)
	{
		stageTime--;
		if (stageTime <= 0)
		{
			if (stage == DAMAGE || stage == FIRE)
			{
				stage = STAND;
				stageTime = 10;
			}
			else if (stage == STAND || stage == WALK)
			{
				if (random() < 0.75 && heroInSight(12))
				{
					stage = FIRE;
					stageTime = 10;
					
					// shoot
					float
						xDir = pointDirection(x, y, o_hero->x, o_hero->y) + random(4) - 2,
						yDir = 90 + random(2) - 1;
					objectCreate(
						x + stepX(SIZE, xDir, yDir),
						y + stepY(SIZE, xDir, yDir),
						z + stepZ(SIZE, xDir, yDir) + SIZE,
						o_bullet);

					o_bullet->xDir = xDir;
					o_bullet->yDir = yDir;
					o_bullet->heroBullet = false;

					sndPlaySound("sounds/s_shot.wav", SND_FILENAME | SND_ASYNC);
				}
				else
				{
					stage = WALK;
					stageTime = 75;
					direction = random(360);
				}
			}
		}
	}

	if (stage == WALK)
	{
		float
			xPrevious = x,
			yPrevious = y;

		x += stepX(SPEED, direction);
		y += stepY(SPEED, direction);

		// Collision with wall
		if (!placeFree(x, y))
		{
			if (placeFree(xPrevious, y)) x = xPrevious;
			else if (placeFree(x, yPrevious)) y = yPrevious;
			else {
				x = xPrevious;
				y = yPrevious;
			}
		}
	}
}

void GM_OBJECT_o_enemy::GM_draw()
{
	float
		x1 = x - stepX(SIZE, o_hero->xDir + 90),
		x2 = x + stepX(SIZE, o_hero->xDir + 90),
		y1 = y - stepY(SIZE, o_hero->xDir + 90),
		y2 = y + stepY(SIZE, o_hero->xDir + 90),
		z1 = z,
		z2 = z + HEIGHT;

	t_enemy.set();
	
	// choose image
	if (stage == STAND)  texture = TEXTURE_ENEMY_STAND;
	if (stage == FIRE)   texture = TEXTURE_ENEMY_FIRE;
	if (stage == WALK)   texture = TEXTURE_ENEMY_WALK_6 - stageTime / 75.0 * 5;
	if (stage == DAMAGE) texture = TEXTURE_ENEMY_DAMAGE;
	if (stage == DIE)    texture = TEXTURE_ENEMY_DIE_7 - stageTime / 90.0 * 6;

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