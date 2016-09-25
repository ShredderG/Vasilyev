

GM_object *objectCreate(float x, float y, float z, GM_object *GM_ptr)
{
	GM_object *GM_new = NULL;
	//if (GM_ptr < (GM_object*)0x0000FFFF) return NULL;
	GM_new->GM_insert(GM_ptr);
	return GM_new;
}

