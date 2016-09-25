// Прототип WndProc
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#define IDI_ICON1 101

struct GM_window
{
	HGLRC     hRC;       // Постоянный контекст рендеринга
	HDC       hDC;       // Приватный контекст устройства GDI
	HWND      hWnd;      // Здесь будет хранится дескриптор окна
	HINSTANCE hInstance; // Здесь будет хранится дескриптор приложения
	
	ushort x, y, width, height;
	string title;
	bool active, fullscreen;

	GM_window() :
		hRC(NULL),
		hDC(NULL),
		hWnd(NULL),
		hInstance(NULL)
	{
	}

	void move(ushort GM_x, ushort GM_y)
	{
		x = GM_x;
		y = GM_y;
		SetWindowPos(hWnd, hWnd, x, y, width, height, SWP_NOZORDER | SWP_NOSIZE);
	}

	void resize(ushort GM_width, ushort GM_height)
	{
		RECT client, window;
		GetClientRect(hWnd, &client);
		GetWindowRect(hWnd, &window);

		SetWindowPos(hWnd, hWnd, x, y,
			GM_width + window.right - window.left - client.right,
			GM_height + window.bottom - window.top - client.bottom,
			SWP_NOZORDER | SWP_NOMOVE);
	}

	void update()
	{
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Вычисление соотношения геометрических размеров для окна
		gluPerspective(60, (float)width / height, 0.5, view.distance);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void init()
	{
		glClearColor(0, 0, 0, 0);
		
		glShadeModel(GL_SMOOTH);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_BACK, GL_LINE);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glAlphaFunc(GL_GREATER, 0.01);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClearDepth(1.0);
		glEnable(GL_BLEND);
		
		srand((unsigned)time(NULL));
		if (GM_MOUSE) mouse.show();
		else mouse.hide();
	}

	void changeFullscreen()
	{
		glDisable(GL_TEXTURE_2D);
		destroy();
		create(title, !fullscreen, x, y, width, height);
	}

	void setTitle(string GM_title)
	{
		title = GM_title;
		SetWindowText(hWnd, title.c_str());
	}

	void destroy()
	{
		if (fullscreen)
		{
			short w = width, h = height;
			ChangeDisplaySettings(NULL, 0);
			width  = w;
			height = h;
		}

		if (hRC)
		{
			if (!wglMakeCurrent(NULL, NULL))
				showMessage("Release Of DC And RC Failed.");
			if (!wglDeleteContext(hRC))
				showMessage("Release Rendering Context Failed.");
		}

		if (hDC && !ReleaseDC(hWnd, hDC))
			showMessage("Release Device Context Failed.");
		if (hWnd && !DestroyWindow(hWnd))
			showMessage("Could Not Release hWnd.");
		if (!UnregisterClass("OpenGL", hInstance))
			showMessage("Could Not Unregister Class.");

		hRC = NULL;
		hDC = NULL;
		hWnd = NULL;
		hInstance = NULL;
	}

	bool create(string GM_title, bool GM_fullscreen, short GM_x, short GM_y, short GM_width, short GM_height)
	{
		title = GM_title;
		fullscreen = GM_fullscreen;
		x = GM_x;
		y = GM_y;
		width  = GM_width;
		height = GM_height;
		if (fullscreen)
		{
			x = y = 0;
			width  = GetSystemMetrics(SM_CXSCREEN);
			height = GetSystemMetrics(SM_CYSCREEN);
		}

		GLuint PixelFormat; // Хранит результат после поиска
		WNDCLASS wc;        // Структура класса окна
		DWORD dwExStyle;    // Расширенный стиль окна
		DWORD dwStyle;      // Обычный стиль окна

		RECT WindowRect;            // Grabs Rectangle Upper Left / Lower Right Values
		WindowRect.left = 0;        // Установить левую составляющую в 0
		WindowRect.right = width;   // Установить правую составляющую в Width
		WindowRect.top = 0;         // Установить верхнюю составляющую в 0
		WindowRect.bottom = height; // Установить нижнюю составляющую в Height

		hInstance = GetModuleHandle(NULL);                          // Считаем дескриптор нашего приложения
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;              // Перерисуем и создаём скрытый DC
		wc.lpfnWndProc = (WNDPROC)WndProc;                          // Процедура обработки сообщений
		wc.cbClsExtra = 0;                                          // Нет дополнительной информации для окна
		wc.cbWndExtra = 0;                                          // Нет дополнительной информации для окна
		wc.hInstance = hInstance;                                   // Устанавливаем дескриптор
		wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); // Загружаем иконку по умолчанию
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);                   // Загружаем указатель мышки
		wc.hbrBackground = NULL;                                    // Фон не требуется для GL
		wc.lpszMenuName = NULL;                                     // Меню в окне не будет
		wc.lpszClassName = "OpenGL";                                // Устанавливаем имя классу

		// Пытаемся зарегистрировать класс окна
		if (!RegisterClass(&wc))
		{
			showMessage("Failed To Register The Window Class.");
			return false;
		}

		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; // Расширенный стиль окна
		dwStyle = WS_OVERLAPPEDWINDOW;                  // Обычный стиль окна

		// Полноэкранный режим?
		if (fullscreen)
		{
			DEVMODE dmScreenSettings;                                                 // Режим устройства
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));                   // Очистка для хранения установок
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);                       // Размер структуры Devmode
			dmScreenSettings.dmPelsWidth = width;                                     // Ширина экрана
			dmScreenSettings.dmPelsHeight = height;                                   // Высота экрана
			dmScreenSettings.dmBitsPerPel = 32;                                       // Глубина цвета
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT; // Режим Пикселя

			// Пытаемся установить выбранный режим и получить результат.
			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				fullscreen = false;
			}
		}

		if (fullscreen || GM_NOBORDER)
		{
			dwExStyle = WS_EX_APPWINDOW; // Расширенный стиль окна
			dwStyle = WS_POPUP;          // Обычный стиль окна
		}
		else
		{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // Расширенный стиль окна
			dwStyle = WS_OVERLAPPEDWINDOW;
			if (!GM_MINIMIZE) dwStyle &= ~WS_MINIMIZEBOX;
			if (!GM_MAXIMIZE) dwStyle &= ~WS_MAXIMIZEBOX;
		}

		// Подбирает окну подходящие размеры
		AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

		if (!(hWnd = CreateWindowEx(dwExStyle,  // Расширенный стиль для окна
			"OpenGL",                           // Имя класса
			title.c_str(),                      // Заголовок окна
			WS_CLIPSIBLINGS |                   // Требуемый стиль для окна
			WS_CLIPCHILDREN |                   // Требуемый стиль для окна
			dwStyle,                            // Выбираемые стили для окна
			x, y,                               // Позиция окна
			WindowRect.right - WindowRect.left, // Вычисление подходящей ширины
			WindowRect.bottom - WindowRect.top, // Вычисление подходящей высоты
			NULL,                               // Нет родительского
			NULL,                               // Нет меню
			hInstance,                          // Дескриптор приложения
			NULL)))                             // Не передаём ничего до WM_CREATE (???)
		{
			destroy();                               // Восстановить экран
			showMessage("Ошибка при создании окна"); // Ошибка
			return false;                            // Вернуть false
		}

		static PIXELFORMATDESCRIPTOR pfd = { 0 };
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE;

		// Проверяем на ошибки
		if (hDC = GetDC(hWnd))
		{
			if (PixelFormat = ChoosePixelFormat(hDC, &pfd))
			{
				if (SetPixelFormat(hDC, PixelFormat, &pfd))
				{
					if (hRC = wglCreateContext(hDC))
					{
						if (wglMakeCurrent(hDC, hRC))
						{
							ShowWindow(hWnd, SW_SHOW);    // Показать окно
							SetForegroundWindow(hWnd);    // Слегка повысим приоритет
							SetFocus(hWnd);               // Установить фокус клавиатуры на наше окно
							update();                     // Перспектива
							init();                       // Прочее

							return true;                  // Окно создано
						}
						else showMessage("Can't Activate The GL Rendering Context.");
					}
					else showMessage("Can't Create A GL Rendering Context.");
				}
				else showMessage("Can't Set The PixelFormat.");
			}
			else showMessage("Can't Find A Suitable PixelFormat.");
		}
		else showMessage("Can't Create A GL Device Context.");

		// Ошибка
		destroy();
		return false;
	}

} window;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Проверка сообщения для окна
	switch (uMsg)
	{

		// Крутим колесико мыши
	case WM_MOUSEWHEEL:
		mouse.check[HIWORD(wParam) == 120 ? MOUSE_WHEEL_UP : MOUSE_WHEEL_DOWN] = true;
		return 0;

		// Проверка сообщения активности окна
	case WM_ACTIVATE:
		// Проверить состояние минимизации
		window.active = !HIWORD(wParam);
		return 0;

		// Перехватываем системную команду
	case WM_SYSCOMMAND:
		// Останавливаем системный вызов (скринсейвер или сбережение энергии)
		if (wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER) return 0;
		break;

		// Мы получили сообщение о закрытии?
	case WM_CLOSE:
		// выход
		GM_game = false;
		return 0;

		// Была ли нажата кнопка?
	case WM_KEYDOWN:
		if (!keyboard.check[keyboard.last = wParam])
			keyboard.check[wParam] = keyboard.pressed[wParam] = true;
		return 0;

		// Была ли отпущена клавиша?
	case WM_KEYUP:
		keyboard.check[wParam] = false;
		keyboard.released[wParam] = true;
		return 0;

		// Изменены размеры OpenGL окна
	case WM_SIZE:
		window.width  = LOWORD(lParam);
		window.height = HIWORD(lParam);
		window.update();
		return 0;
	
		// Изменены размеры OpenGL окна
	case WM_MOVE:
		window.x = LOWORD(lParam);
		window.y = HIWORD(lParam);
		return 0;

	}
	// Пересылаем все необработанные сообщения
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}