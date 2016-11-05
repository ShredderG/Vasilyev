void genmap(const char * imagepath)
{
	FILE* f = fopen(imagepath, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	int width = info[18];
	int height = info[22];

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			uchar data[3];
			fread(data, 3, 1, f);

			// floor
			objectCreate(x, y, 0, o_floor);

			// sewer floor
			if (data[0] == 64 && data[1] == 128 && data[2] == 255)
			{
				objectCreate(x, y, 0.01, o_floor);
				o_floor->texture = TEXTURE_INTERIOR_SEWER;
			}

			// wall
			if (data[0] == 0 && data[1] == 0 && data[2] == 0)
				objectCreate(x, y, 0, o_wall);

			// wall glass
			if (data[0] == 255 && data[1] == 255 && data[2] == 0)
			{
				objectCreate(x, y, 0, o_wall);
				o_wall->texture = TEXTURE_INTERIOR_GLASS;
				objectCreate(x, y, 0.01, o_floor);
				o_floor->texture = TEXTURE_INTERIOR_PLATE;
			}

			// door
			if (data[0] == 192 && data[1] == 192 && data[2] == 192)
			{
				objectCreate(x, y, 0, o_door);
				objectCreate(x, y, 0.01, o_floor);
				o_floor->texture = TEXTURE_INTERIOR_PLATE;
			}

			// locked door
			if (data[0] == 128 && data[1] == 128 && data[2] == 128)
			{
				objectCreate(x, y, 0, o_door);
				o_door->locked = true;
			}

			// item ammo
			if (data[0] == 0 && data[1] == 255 && data[2] == 0)
			{
				objectCreate(x + 0.5, y + 0.5, 0, o_item);
				o_item->type = ITEM_AMMO;
			}

			// item medkit
			if (data[0] == 255 && data[1] == 0 && data[2] == 0)
			{
				objectCreate(x + 0.5, y + 0.5, 0, o_item);
				o_item->type = ITEM_MEDKIT;
			}

			// item key
			if (data[0] == 0 && data[1] == 255 && data[2] == 255)
			{
				objectCreate(x + 0.5, y + 0.5, 0, o_item);
				o_item->type = ITEM_KEY;
			}

			// enemy
			if (data[0] == 0 && data[1] == 0 && data[2] == 255)
				objectCreate(x + 0.5, y + 0.5, 0, o_enemy);

			// hero
			if (data[0] == 255 && data[1] == 0 && data[2] == 255)
				objectCreate(x + 0.5, y + 0.5, 0, o_hero);
		}
	}

	fclose(f);
}