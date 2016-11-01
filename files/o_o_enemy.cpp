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

void GM_OBJECT_o_enemy::GM_step()
{
}

void GM_OBJECT_o_enemy::GM_draw()
{
}

uint GM_OBJECT_o_enemy::GM_id()
{
	return GM_OBJECT_ID_o_enemy;
}