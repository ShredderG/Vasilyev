struct GM_room
{
	void(*create)();
	static bool transition;

	GM_room() :
		create(NULL)
	{
		transition = false;
	}
	
	GM_room(void(*function)())
	{
		create = function;
	}

	bool operator == (GM_room &rm)
	{
		return create == rm.create;
	}

	bool operator != (GM_room &rm)
	{
		return create != rm.create;
	}

	void set(GM_room &room_next)
	{
		transition = true;
		room = room_next;
		for (GM_object *ptr = GM_list; ptr; ptr = ptr->GM_right)
			if (!ptr->persistent) ptr->destroy();
	}
} room;

bool GM_room::transition;

bool GM_transition()
{
	if (GM_room::transition)
	{
		room.create();
		GM_room::transition = false;
		return true;
	}
	return false;
}