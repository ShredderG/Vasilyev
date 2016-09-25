// Мышь
enum
{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_WHEEL_UP,
	MOUSE_WHEEL_DOWN
};

struct GM_mouse
{
	short x, y;

	bool
		visible,
		outside,
		pressed[3],
		released[3],
		checkPrevious[3],
		check[5];
	
	GM_mouse() : outside(false)
	{
		for (uchar i = 0; i < 3; i++)
			check[i] = false;
	}

	void move(short GM_x, short GM_y)
	{
		POINT point;
		GetCursorPos(&point);
		x = point.x - x;
		y = point.y - y;
		if (bool(GetActiveWindow())) SetCursorPos(x + GM_x, y + GM_y);
		x = GM_x;
		y = GM_y;
	}

	void show()
	{
		visible = true;
		while(ShowCursor(visible) < 0);
	}

	void hide()
	{
		visible = false;
		while (ShowCursor(visible) >= 0);
	}

	void update(HWND hWnd, short width, short height)
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hWnd, &point);
		x = point.x;
		y = point.y;

		for (uchar i = 0; i < 3; i++)
		{
			checkPrevious[i] = check[i];
			check[i] = GetAsyncKeyState(i == 2 ? 4 : i + 1);
			pressed[i] = check[i] && !checkPrevious[i];
			released[i] = !check[i] && checkPrevious[i];
		}

		if (!visible)
		{
			if (!outside)
			if (x < 0 || y < 0 || x >= width || y >= height)
			{
				ShowCursor(true);
				outside = true;
			}

			if (outside)
			if (x >= 0 && y >= 0 && x < width && y < height)
			{
				ShowCursor(false);
				outside = false;
			}
		}
	}

	void reset()
	{
		check[MOUSE_WHEEL_UP] = false;
		check[MOUSE_WHEEL_DOWN] = false;
	}
} mouse;