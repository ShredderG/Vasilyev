#include <sstream>
void genmap(const char * imagepath)
{

    int i;
    FILE* f = fopen(imagepath, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    
    //const int width = *(int*)&info[18];
    //const int height = *(int*)&info[22];

	const int width = 10;
	const int height = 10;

    int size = 3 * width * height;
    unsigned char data[width][height][3];
    fread(data, 3, width * height, f);
    fclose(f);

	for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
			if(data[x][y][2] == 255 && data[x][y][1] == 255 && data[x][y][0] == 255)	
			{
				showMessage("player"); continue;
			}

			if(data[x][y][2] == 0 && data[x][y][1] == 255 && data[x][y][0] == 0)	
			{
				showMessage("grass"); continue;
			}

			if(data[x][y][2] == 255 && data[x][y][1] == 0 && data[x][y][0] == 0)	
			{
				showMessage("health kit"); continue;
			}

			if(data[x][y][2] == 64 && data[x][y][1] == 0 && data[x][y][0] == 0)	
			{
				showMessage("door"); continue;
			}

			if(data[x][y][2] == 0 && data[x][y][1] == 255 && data[x][y][0] == 255)	
			{
				showMessage("enemy #1"); continue;
			}

			if(data[x][y][2] == 255 && data[x][y][1] == 255 && data[x][y][0] == 0)	
			{
				showMessage("key"); continue;
			}

			if(data[x][y][2] == 0 && data[x][y][1] == 64 && data[x][y][0] == 0)	
			{
				showMessage("ammo pack"); continue;
			}
        }
    }
}
