GM_OBJECT_o_hud::GM_OBJECT_o_hud(float GM_x, float GM_y, float GM_z)
{
	GM_count++;
	o_hud = this;
	priority = -1;
	persistent = true;
	x = GM_x;
	y = GM_y;
	z = GM_z;
}

void GM_OBJECT_o_hud::destroy()
{
	if (!GM_active) return;
	GM_count--;
	GM_active = false;

	if (o_hud == this)
	{
		if (GM_left)  if (GM_left->GM_id() == GM_id()) o_hud = (GM_OBJECT_o_hud*)GM_left;
		if (GM_right) if (GM_right->GM_id() == GM_id()) o_hud = (GM_OBJECT_o_hud*)GM_right;
		if (o_hud == this) o_hud = (GM_OBJECT_o_hud*)GM_id();
	}
}

void GM_OBJECT_o_hud::GM_step()
{
	if (message_time > 0) message_time--;
	if (hit_time > 0) hit_time--;
}

// show message
void GM_OBJECT_o_hud::message(string text_new)
{
	text = text_new;
	message_time = MESSAGE_TIME;
}

// draw text 2d
void GM_OBJECT_o_hud::drawText(string text, int x, int y, int size)
{
	t_font.set();
	int xStart = x;
	int n = text.length();

	glBegin(GL_QUADS);
	for (int i = 0; i < n; i++)
	{
		uchar symbol = text[i];
		if (symbol == '\n')
		{
			x = xStart;
			y += size;
			continue;
		}
		glTexCoord2f(t_font.x1[symbol], t_font.y1[symbol]); glVertex2f(x, y);
		glTexCoord2f(t_font.x1[symbol], t_font.y2[symbol]); glVertex2f(x, y + size);
		glTexCoord2f(t_font.x2[symbol], t_font.y2[symbol]); glVertex2f(x + size, y + size);
		glTexCoord2f(t_font.x2[symbol], t_font.y1[symbol]); glVertex2f(x + size, y);
		x += size;
	}
	glEnd();
}

// draw a picture 2d
void GM_OBJECT_o_hud::drawPic2d(GM_texture &texture, int image, int x, int y, int width, int height)
{
	texture.set();

	glBegin(GL_QUADS);
	glTexCoord2f(texture.x1[image], texture.y1[image]); glVertex2f(x, y);
	glTexCoord2f(texture.x1[image], texture.y2[image]); glVertex2f(x, y + height);
	glTexCoord2f(texture.x2[image], texture.y2[image]); glVertex2f(x + width, y + height);
	glTexCoord2f(texture.x2[image], texture.y1[image]); glVertex2f(x + width, y);
	glEnd();
}

void GM_OBJECT_o_hud::GM_draw()
{
	view.set2d(0, 0, window.width, window.height);

	// red glow when hit
	if (hit_time > 0)
	{
		glDisable(GL_TEXTURE_2D);

		// grey bar
		glColor4f(1, 0, 0, 0.8 * hit_time / HIT_TIME);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, window.height);
		glVertex2f(window.width, window.height);
		glVertex2f(window.width, 0);
		glEnd();

		glColor3f(1, 1, 1);

		glEnable(GL_TEXTURE_2D);
	}

	// draw message
	if (message_time > 0)
	{
		int xx = window.width / 2 - text.length() / 2.0 * FONT_SIZE;
		int yy = FONT_SIZE * 3;

		glColor3f(0, 0, 0);
		drawText(text, xx - 1, yy - 1, FONT_SIZE);
		drawText(text, xx + 1, yy - 1, FONT_SIZE);
		drawText(text, xx + 1, yy + 1, FONT_SIZE);
		drawText(text, xx - 1, yy + 1, FONT_SIZE);

		glColor3f(1, 1, 1);
		drawText(text, xx, yy, FONT_SIZE);
	}

	// draw heart
	drawPic2d(t_icons, TEXTURE_ICONS_HEART, 16, 16, ICON_SIZE, ICON_SIZE);

	// draw hp bar
	glDisable(GL_TEXTURE_2D);

	int hp_x = 16 + ICON_SIZE + 16,
		hp_y = 16 + 8,
		hp_width = 300,
		hp_height = ICON_SIZE - 16,
		hp_length = hp_width * ((float)o_hero->hp / o_hero->HP_MAX);

	// grey bar
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex2f(hp_x, hp_y);
	glVertex2f(hp_x, hp_y + hp_height);
	glVertex2f(hp_x + hp_width, hp_y + hp_height);
	glVertex2f(hp_x + hp_width, hp_y);
	glEnd();

	// red bar
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(hp_x, hp_y);
	glVertex2f(hp_x, hp_y + hp_height);
	glVertex2f(hp_x + hp_length, hp_y + hp_height);
	glVertex2f(hp_x + hp_length, hp_y);
	glEnd();

	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);

	// draw hp bar text
	string text_hp = str(o_hero->hp) + " / " + str(o_hero->HP_MAX);
	drawText(text_hp,
		hp_x + hp_width / 2 - text_hp.length() / 2.0 * FONT_SIZE_SMALL,
		hp_y + (hp_height - FONT_SIZE_SMALL) / 2,
		FONT_SIZE_SMALL);

	// draw key
	if (o_hero->key)
		drawPic2d(t_icons, TEXTURE_ICONS_KEY, window.width - 16 - ICON_SIZE, 16, ICON_SIZE, ICON_SIZE);

	// draw bullets
	for (int i = o_hero->AMMO_MAX - 1; i >= 0; i--)
	{
		int tex = i + 1 <= o_hero->ammo ? TEXTURE_ICONS_BULLET_YES : TEXTURE_ICONS_BULLET_NO;
		drawPic2d(t_icons, tex, 16, window.height - (i + 3) * ICON_SIZE / 4, ICON_SIZE, ICON_SIZE);
	}

	// draw ammo text
	drawText(str(o_hero->ammo) + "/" + str(o_hero->AMMO_MAX),
		16 + ICON_SIZE + 16,
		window.height - FONT_SIZE * 1.5,
		FONT_SIZE);

	drawText(str(o_hero->ammoTotal),
		16 + ICON_SIZE + 16,
		window.height - FONT_SIZE * 2.5,
		FONT_SIZE_SMALL);

	// draw weapon
	int shiftDelayShoot = (float)o_hero->shootDelay / o_hero->SHOOT_DELAY * 100;
	int shiftDelayReload = sin((float)o_hero->reloadDelay / o_hero->RELOAD_DELAY * PI) * 300;
	int shiftBobbing = sin((float)o_hero->bobbing / o_hero->BOBBING_MAX * PI * 2.0) * 20;
	drawPic2d(t_weapon,
		o_hero->shootDelay > 7 ? TEXTURE_WEAPON_FIRE : TEXTURE_WEAPON_COLD,
		window.width - WEAPON_SIZE + shiftDelayShoot + 100,
		window.height - WEAPON_SIZE + shiftDelayShoot + shiftDelayReload + shiftBobbing + 120,
		WEAPON_SIZE, WEAPON_SIZE);

	view.set3d();
}

uint GM_OBJECT_o_hud::GM_id()
{
	return GM_OBJECT_ID_o_hud;
}