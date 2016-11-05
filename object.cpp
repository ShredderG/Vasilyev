// Конструкция with
#define with(object)                                 \
for (GM_OBJECT_##object *object = ::object;          \
	object > (GM_OBJECT_##object*)0x0000FFFF;        \
	object = (GM_OBJECT_##object*)object->GM_right)  \
	if (object->GM_id() != ::object->GM_id()) break; \
	else if (object->GM_active)

// Существует ли экземпляр объекта
#define objectExists(object) (objectCount(object) > 0)

// Кол-во экземпляров объекта
#define objectCount(object) GM_OBJECT_ ## object::GM_count

// На всякий
#define repeat(count) for(int GM_index = 0; GM_index < count; GM_index++)

struct GM_object
{
	GM_object *GM_left, *GM_right;
	float x, y, z;
	bool GM_active, persistent;
	int priority;

	// constructor
	GM_object() : GM_active(true)
	{
	}

	// destructor
	~GM_object()
	{
		(GM_left ? GM_left->GM_right : GM_list) = GM_right;
		if (GM_right) GM_right->GM_left = GM_left;
	}

	// insert object to the object list
	void GM_insert(GM_object *ptr)
	{
		GM_object *before = NULL, *after = ptr;

		if (after < (GM_object*)0x0000FFFF)
			after = GM_list;
		else
			before = after->GM_left;

		while (after)
		{
			if (priority < after->priority)
			{
				before = after;
				after = after->GM_right;
			}
			else break;
		}

		GM_left = before;
		GM_right = after;

		(GM_left ? GM_left->GM_right : GM_list) = this;
		if (GM_right) GM_right->GM_left = this;
	}

	// Виртуальные функции
	virtual void destroy() = 0;
	virtual void GM_step() = 0;
	virtual void GM_draw() = 0;
	virtual uint GM_id() = 0;
	virtual void destructor() = 0;

} *GM_list = NULL;

// Delete everything
void GM_deleteObjects()
{
	for (GM_object *ptr = GM_list, *ptr_next = ptr ? ptr->GM_right : NULL; ptr; ptr = ptr_next, ptr_next = ptr ? ptr->GM_right : NULL)
		delete ptr;
}

// Global step
void GM_step()
{
	mouse.update(window.hWnd, window.width, window.height);

	for (GM_object *ptr = GM_list; ptr; ptr = ptr->GM_right)
		if (ptr->GM_active) ptr->GM_step();

	for (GM_object *ptr = GM_list, *ptr_next = ptr ? ptr->GM_right : NULL; ptr; ptr = ptr_next, ptr_next = ptr ? ptr->GM_right : NULL)
		if (!ptr->GM_active)
		{
			ptr->destructor();
			delete ptr;
		}

	keyboard.reset();
	mouse.reset();
}

// Global draw
void GM_draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (GM_object *ptr = GM_list; ptr; ptr = ptr->GM_right)
		ptr->GM_draw();

	SwapBuffers(window.hDC);
}