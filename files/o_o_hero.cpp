GM_OBJECT_o_hero::GM_OBJECT_o_hero(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_hero = this;
	priority = 1;
	persistent = true;
	x = GM_x;
	y = GM_y;
	z = GM_z;

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
void GM_OBJECT_o_hero::getDamage(int damage)
{
	hp -= damage;

	o_hud->hit_time = o_hud->HIT_TIME;

	if (hp <= 0)
	{
		sndPlaySound("sounds/s_death.wav", SND_FILENAME | SND_ASYNC);
		hp = 0;
		o_hud->message("You are dead for good!");
	}
	else
	{
		sndPlaySound("sounds/s_damage.wav", SND_FILENAME | SND_ASYNC);
	}
}

void GM_OBJECT_o_hero::GM_step()
{
	// Mouse look
	xDir += ((window.width / 2) - mouse.x) / 10.0;
	yDir += ((window.height / 2) - mouse.y) / 10.0;

	while (xDir < 0) xDir += 360;
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

		// bobbing
		bobbing++;
		if (bobbing > BOBBING_MAX)
			bobbing = 0;

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
	else
	{
		// disable bobbing
		if (bobbing != 0)
		{
			if (bobbing < BOBBING_MAX / 2)
				bobbing--;
			else
			{
				bobbing++;
				if (bobbing > BOBBING_MAX)
					bobbing = 0;
			}
		}
	}

	// Delays
	if (shootDelay > 0) shootDelay--;
	if (reloadDelay > 0) reloadDelay--;

	// shooting
	if (mouse.pressed[MOUSE_LEFT])
	{
		if (shootDelay <= 0 && reloadDelay <= 0) // can shoot?
		{
			if (ammo > 0) // have ammo?
			{
				objectCreate(
					x + stepX(SIZE, xDir, yDir),
					y + stepY(SIZE, xDir, yDir),
					z + stepZ(SIZE, xDir, yDir) + HEIGHT - 0.1,
					o_bullet);

				o_bullet->xDir = xDir;
				o_bullet->yDir = yDir;
				o_bullet->heroBullet = true;

				sndPlaySound("sounds/s_shot.wav", SND_FILENAME | SND_ASYNC);
				shootDelay = SHOOT_DELAY;
				ammo--;
			}
			else
			{
				sndPlaySound("sounds/s_noammo.wav", SND_FILENAME | SND_ASYNC);
				if (ammoTotal > 0) o_hud->message("Reload weapon!");
				else o_hud->message("No more ammo!");
			}
		}
	}

	// Reloading weapon
	if (keyboard.pressed['R'])
	{
		if (reloadDelay <= 0) // can reload?
		{
			if (ammo < AMMO_MAX) // need ammo?
			{
				if (ammoTotal != 0) // have ammo?
				{
					int ammoHave = ammoTotal;
					int ammoNeed = AMMO_MAX - ammo;
					int ammoLoad = (ammoNeed > ammoHave) ? ammoHave : ammoNeed;

					sndPlaySound("sounds/s_reload.wav", SND_FILENAME | SND_ASYNC);
					ammo += ammoLoad;
					ammoTotal -= ammoLoad;
					reloadDelay = RELOAD_DELAY;
				}
				else
				{
					sndPlaySound("sounds/s_message.wav", SND_FILENAME | SND_ASYNC);
					o_hud->message("No more ammo!");
				}
			}
		}
	}

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
				if (!o_door->opened)
				{
					if (o_door->locked)
					{
						if (key)
						{
							o_door->locked = !o_door->locked;
							o_door->opened = !o_door->opened;
							sndPlaySound("sounds/s_door.wav", SND_FILENAME | SND_ASYNC);
							key = false;
						}
						else
						{
							sndPlaySound("sounds/s_denied.wav", SND_FILENAME | SND_ASYNC);
							o_hud->message("Need key!");
						}
					}
					else
					{
						sndPlaySound("sounds/s_door.wav", SND_FILENAME | SND_ASYNC);
						o_door->opened = !o_door->opened;
					}
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
							if (ammoTotal < AMMO_TOTAL_MAX)
							{
								sndPlaySound("sounds/s_ammo.wav", SND_FILENAME | SND_ASYNC);
								ammoTotal += o_item->AMMO;
								if (ammoTotal > AMMO_TOTAL_MAX) ammoTotal = AMMO_TOTAL_MAX;
								o_item->destroy();
							}
							else
							{
								o_hud->message("Ammo is full!");
							}
							break;

							// medkit
						case ITEM_MEDKIT:
							if (hp < HP_MAX)
							{
								sndPlaySound("sounds/s_medkit.wav", SND_FILENAME | SND_ASYNC);
								hp += o_item->MEDKIT;
								if (hp > HP_MAX) hp = HP_MAX;
								o_item->destroy();
							}
							else
							{
								o_hud->message("HP are full!");
							}
							break;

							// key
						case ITEM_KEY:
							if (!key)
							{
								sndPlaySound("sounds/s_key.wav", SND_FILENAME | SND_ASYNC);
								key = true;
								o_item->destroy();
							}
							else
							{
								o_hud->message("Already have a key!");
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