GM_OBJECT_o_hero::GM_OBJECT_o_hero(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_hero = this;
	priority = 1;
	persistent = true;
	x = GM_x;
	y = GM_y;
	z = GM_z;

	xDir = 0;
	yDir = 90;
	shootDelay = 0;

	hp = HP_MAX;
	ammo = AMMO_MAX;
	ammoTotal = 5;
	key = false;

	mouse.move(window.width / 2, window.height / 2);
}

void GM_OBJECT_o_hero::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;

	if (o_hero == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_hero = (GM_OBJECT_o_hero*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_hero = (GM_OBJECT_o_hero*)GM_right;
		if (o_hero == this) o_hero = (GM_OBJECT_o_hero*)GM_id();
	}
}

// collision with wall or door
bool GM_OBJECT_o_hero::placeFree(float x, float y)
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
void GM_OBJECT_o_hero::getDamage(int damage)
{
	hp -= damage;

	// + red screen

	if (hp < 0)
	{
		hp = 0;
		showMessage("You are dead for good!"); // надо поменять
	}
}

void GM_OBJECT_o_hero::GM_step()
{
	// Mouse look
	xDir += ((window.width / 2) - mouse.x) / 10.0;
	yDir += ((window.height / 2) - mouse.y) / 10.0;

	while (xDir < 0)   xDir += 360;
	while (xDir >= 360) xDir -= 360;
	if (yDir < 10)  yDir = 10;
	if (yDir > 170) yDir = 170;

	// Direction
	float direction = -1;
	if (keyboard.check['W'])
	{
		if (!keyboard.check['S'])
		{
			direction = xDir;
			if (keyboard.check['A']) direction += 45;
			if (keyboard.check['D']) direction -= 45;
		}
	}
	else if (keyboard.check['S'])
	{
		direction = xDir + 180;
		if (keyboard.check['A']) direction -= 45;
		if (keyboard.check['D']) direction += 45;
	}
	else if (keyboard.check['A'])
	{
		if (!keyboard.check['D']) direction = xDir + 90;
	}
	else if (keyboard.check['D']) direction = xDir - 90;

	// Move
	if (direction != -1)
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

	// shooting
	if (mouse.pressed[MOUSE_LEFT])
	{
		if (shootDelay <= 0)
		{
			if (ammo > 0)
			{
				objectCreate(
					x + stepX(SIZE, xDir, yDir),
					y + stepY(SIZE, xDir, yDir),
					z + stepZ(SIZE, xDir, yDir) + HEIGHT - 0.1,
					o_bullet);

				o_bullet->xDir = xDir;
				o_bullet->yDir = yDir;

				shootDelay = 10;
				ammo--;
			}
		}
	}
	if (shootDelay > 0) shootDelay--;

	// opening doors
	if (keyboard.pressed['E'])
	{
		with(o_door)
		{
			float
				dx = o_door->x + 0.5,
				dy = o_door->y + 0.5;

			if (pointDistance(x, y, dx, dy) < 2.0)
			{
				if (o_door->locked)
				{
					if (key)
					{
						o_door->locked = !o_door->locked;
						o_door->opened = !o_door->opened;
						key = false;
					}
					else showMessage("Need key!"); // надо поменять
				}
				else
				{
					o_door->opened = !o_door->opened;
				}
				break;
			}
		}
	}

	// taking items
	with(o_item)
	{
		if (x + SIZE > o_item->x)
			if (y + SIZE > o_item->y)
				if (x - SIZE < o_item->x)
					if (y - SIZE < o_item->y)
					{
						// get item type
						switch (o_item->type)
						{
							// ammo
						case ITEM_AMMO:
							ammoTotal += o_item->AMMO;
							o_item->destroy();
							break;

							// medkit
						case ITEM_MEDKIT:
							if (hp < HP_MAX)
							{
								hp += o_item->MEDKIT;
								if (hp > HP_MAX) hp = HP_MAX;
								o_item->destroy();
							}
							else
							{
								showMessage("HP are full!"); // надо поменять
							}
							break;

							// key
						case ITEM_KEY:
							if (!key)
							{
								key = true;
								o_item->destroy();
							}
							else
							{
								showMessage("Already have a key!"); // надо поменять
							}
							break;
						}

						break;
					}
	}

	// End
	mouse.move(window.width / 2, window.height / 2);
	if (keyboard.pressed[VK_ESCAPE]) GM_game = false;
}

void GM_OBJECT_o_hero::GM_draw()
{
	view.set(x, y, z + HEIGHT, xDir, yDir, 0);
}

uint GM_OBJECT_o_hero::GM_id()
{
	return GM_OBJECT_ID_o_hero;
}