GM_OBJECT_o_bullet::GM_OBJECT_o_bullet(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_bullet = this;
	priority = 0;
	solid = false;
	persistent = false;
	x = GM_x;
	y = GM_y;
	z = GM_z;
}

GM_OBJECT_o_bullet::~GM_OBJECT_o_bullet()
{
	if (o_bullet == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_bullet = (GM_OBJECT_o_bullet*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_bullet = (GM_OBJECT_o_bullet*)GM_right;
		if (o_bullet == this) o_bullet = (GM_OBJECT_o_bullet*)GM_id();
	}
}

void GM_OBJECT_o_bullet::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;

}

void GM_OBJECT_o_bullet::GM_step()
{
}

void GM_OBJECT_o_bullet::GM_draw()
{
}

uint GM_OBJECT_o_bullet::GM_id()
{
	return GM_OBJECT_ID_o_bullet;
}