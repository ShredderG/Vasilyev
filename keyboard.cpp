struct GM_keyboard
{
	uchar last;
	bool
		check[256],
		pressed[256],
		released[256];

	void reset()
	{
		//  лавиши и мышь
		memset(pressed, false, 256);
		memset(released, false, 256);

		last = 0;
	}
} keyboard;