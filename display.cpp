struct GM_display
{
	short width, height;

	GM_display() :
		width(GetSystemMetrics(SM_CXSCREEN)),
		height(GetSystemMetrics(SM_CYSCREEN))
	{
	}
} display;