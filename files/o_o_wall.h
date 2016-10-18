struct GM_OBJECT_o_wall : public GM_object
{
	float height;

	void drawWall(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		glBegin(GL_QUADS);

		glTexCoord2f(0, 0); glVertex3f(x1, y1, z1);
		glTexCoord2f(1, 0); glVertex3f(x1, y1, z2);
		glTexCoord2f(1, 1); glVertex3f(x2, y2, z2);
		glTexCoord2f(0, 1); glVertex3f(x2, y2, z1);

		glEnd();
	}

	static int GM_count;
	GM_OBJECT_o_wall(float GM_x, float GM_y, float GM_z);
	~GM_OBJECT_o_wall();
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

} *o_wall = (GM_OBJECT_o_wall*)GM_OBJECT_ID_o_wall;

int GM_OBJECT_o_wall::GM_count;