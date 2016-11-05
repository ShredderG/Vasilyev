void GM_ROOM_r_start()
{
	objectCreate(0, 0, 0, o_hud);
	genmap("textures/level.bmp");
}

GM_room
	r_start(GM_ROOM_r_start);
