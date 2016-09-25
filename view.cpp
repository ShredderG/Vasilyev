struct GM_view
{
	float x, y, z, vx, vy, vz, distance;

	GM_view() :
		x(0), y(0), z(0), vx(0), vy(0), vz(0), distance(512)
	{
	}

	void set(float GM_x, float GM_y, float GM_z, float GM_vx, float GM_vy, float GM_vz, float GM_distance)
	{
		distance = GM_distance;
		set(GM_x, GM_y, GM_z, GM_vx, GM_vy, GM_vz);
	}

	void set(float GM_x, float GM_y, float GM_z, float GM_vx, float GM_vy, float GM_vz)
	{
		while (GM_vx >= 360) GM_vx -= 360;
		while (GM_vy >= 360) GM_vy -= 360;
		while (GM_vz >= 360) GM_vz -= 360;
		while (GM_vx < 0) GM_vx += 360;
		while (GM_vy < 0) GM_vy += 360;
		while (GM_vz < 0) GM_vz += 360;

		x = GM_x;
		y = GM_y;
		z = GM_z;
		vx = GM_vx - 90;
		vy = GM_vy;
		vz = GM_vz;

		update();
	}

	void update()
	{
		glLoadIdentity();
		glRotatef(-vy, 1, 0, 0); // вверх-вниз
		glRotatef(-vz, 0, 1, 0); // вбок-невбок
		glRotatef(-vx, 0, 0, 1); // влево-вправо
		glTranslatef(-x, -y, -z);
	}

	void set2d(short x1, short y1, short x2, short y2)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glOrtho(x1, x2, y2, y1, 0, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void set3d()
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		update();
	}

} view;