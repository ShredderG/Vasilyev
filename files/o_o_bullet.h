struct GM_OBJECT_o_bullet : public GM_object
{
	float xDir, yDir; // переопределяются после создания

	const float SPEED = 0.1;
	const float SIZE = 0.05;
	const int DAMAGE = 10;

	static int GM_count;
	GM_OBJECT_o_bullet(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

} *o_bullet = (GM_OBJECT_o_bullet*) GM_OBJECT_ID_o_bullet;

	int GM_OBJECT_o_bullet::GM_count;
