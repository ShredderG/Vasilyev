GM_OBJECT_o_hero::GM_OBJECT_o_hero(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_hero = this;
	priority = 1;
	solid = false;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;
	xDir = 0;
	yDir = 90;

	mouse.move(window.width / 2, window.height / 2);
}

GM_OBJECT_o_hero::~GM_OBJECT_o_hero()
{
	if (o_hero == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_hero = (GM_OBJECT_o_hero*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_hero = (GM_OBJECT_o_hero*)GM_right;
		if (o_hero == this) o_hero = (GM_OBJECT_o_hero*)GM_id();
	}
}

void GM_OBJECT_o_hero::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;
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
	float direction = NAN;
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
	if (!isnan(direction))
	{
		x += stepX(0.1, direction);
		y += stepY(0.1, direction);
	}

	// End
	mouse.move(window.width / 2, window.height / 2);
	if (keyboard.pressed[VK_ESCAPE]) GM_game = false;
}

void GM_OBJECT_o_hero::GM_draw()
{
	view.set(x, y, z + 2, xDir, yDir, 0);
}

uint GM_OBJECT_o_hero::GM_id()
{
	return GM_OBJECT_ID_o_hero;
}