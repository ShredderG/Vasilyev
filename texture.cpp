struct GM_texture
{
	static GM_texture *current;
	uint id;
	uchar *data;
	string path;
	ushort count, width, height, xSize, ySize;
	float *x1, *x2, *y1, *y2;

	GM_texture(ushort w, ushort h, ushort x, ushort y, string file) :
		x1(NULL), y1(NULL), x2(NULL), y2(NULL),
		width(w), height(h), xSize(x), ySize(y),
		data(NULL), path(file)
	{
	}

	GM_texture(ushort w, ushort h, ushort x, ushort y, uchar *bytes) :
		x1(NULL), y1(NULL), x2(NULL), y2(NULL),
		width(w), height(h), xSize(x), ySize(y),
		data(bytes), path("")
	{
	}

	void load()
	{
		if (x1) return;

		// load from file
		if (path != "")
		{
			FILE *f = fopen(path.c_str(), "rb");
			if (!f) showMessage("asd");
			fseek(f, 54, SEEK_SET);
			uint length = width * height * 3;
			data = new uchar[length];
			fread(data, length, 1, f);
			fclose(f);
		}

		// texture coordinates
		int xCount = width / xSize;
		int yCount = height / ySize;
		count = xCount * yCount;

		x1 = new float[count];
		y1 = new float[count];
		x2 = new float[count];
		y2 = new float[count];

		int index = 0;
		for (int j = 0; j<yCount; j++)
		{
			for (int i = 0; i<xCount; i++)
			{
				x1[index] = (float)i * xSize / width;
				x2[index] = (float)(i + 1) * xSize / width;
				y1[index] = 1 - (float)j * ySize / height;
				y2[index] = 1 - (float)(j + 1) * ySize / height;
				index++;
			}
		}

		// texture creating
		glGenTextures(1, &id);

		uint length = width * height * 4;
		uchar *alpha = new uchar[length];

		// colors - rgba
		for (uint i = 0; i<length; i += 4)
		{
			alpha[i] = *data++;
			alpha[i + 1] = *data++;
			alpha[i + 2] = *data++;
			alpha[i + 3] = alpha[i] == 255 && !alpha[i + 1] && alpha[i + 2] == 255 ? 0 : 255;
		}

		set();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, path != "" ? GL_BGRA_EXT : GL_RGBA, GL_UNSIGNED_BYTE, alpha);

		//if (path != "") delete[] data;
		delete[] alpha;
	}

	void unload()
	{
		if (!x1) return;
		x1 = x2 = y1 = y2 = NULL;
		glDeleteTextures(1, &id);
		delete x1;
		delete y1;
		delete x2;
		delete y2;
	}

	void set()
	{
		// if (current == this) return;
		glBindTexture(GL_TEXTURE_2D, id);
		current = this;
	}
};

GM_texture *GM_texture::current = NULL;