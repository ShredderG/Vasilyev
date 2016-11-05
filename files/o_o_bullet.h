struct GM_OBJECT_o_bullet : public GM_object
{
	float // redefined after creating
		xDir = 0,
		yDir = 0;
	bool heroBullet = false;

	static const float SPEED;
	static const float SIZE;
	static const int DAMAGE = 10;

	static int GM_count;
	GM_OBJECT_o_bullet(float GM_x, float GM_y, float GM_z);
	void destroy();
	void GM_step();
	void GM_draw();
	uint GM_id();

} *o_bullet = (GM_OBJECT_o_bullet*) GM_OBJECT_ID_o_bullet;

const float GM_OBJECT_o_bullet::SPEED = 0.1;
const float GM_OBJECT_o_bullet::SIZE = 0.05;
int GM_OBJECT_o_bullet::GM_count = 0;