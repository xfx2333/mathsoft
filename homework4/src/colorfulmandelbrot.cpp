#include <iostream>
#include <cstdlib>
#include "Window.h"
#include "Manderbrot.h"
#include "bitmap.h"

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		std::cerr << "Usage: " << argv[0]
				  << " filename ox oy dimension" << std::endl;
		exit(-1);
	}
	
	Window win(std::atof(argv[2]), std::atof(argv[3]), std::atof(argv[4]));
	double lpp = win.get_lpp();
	double dim = win.get_dimension();
	int width = win.get_width();
	int height = win.get_height();
	double ox = win.get_ox() - dim;
	double oy = win.get_oy() - dim / width * height;
	int N = 1000;

	char *cache = new char[width * height * 3];

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
			double x = ox + lpp * i;
			double y = oy + lpp * j;
			int pos = width * j + i;
			int n = 0;
			Manderbrot man(std::complex<double>{0.0, 0.0},
						   N,
						   std::complex<double>{x, y});
			while (!man.stop_criterion())
			{
				man.forward_step();
				n++;
				if (man.is_disconvergence())
					break;
			}
			if (man.stop_criterion())
			{
			  if ((n % 7) == 1)
			    {
				cache[pos * 3] = 128;
				cache[pos * 3 + 1] = 0;
				cache[pos * 3 + 2] = 128;
			    }
			  else if ((n % 7) == 2)
			    {
			        cache[pos * 3] = 255;
			        cache[pos * 3 + 1 ] = 0;
			        cache[pos * 3 + 2 ] = 0;
			    }
			  else if ((n % 7) == 3)
			    {
				cache[pos * 3] = 128;
				cache[pos * 3 + 1] = 128;
				cache[pos * 3 + 2] = 0;
			    }
			  else if ((n % 7) == 4)
			    {
				cache[pos * 3] = 0;
				cache[pos * 3 + 1] = 128;
				cache[pos * 3 + 2] = 0;
			    }
			  else if ((n % 7) == 5)
			    {
				cache[pos * 3] = 0;
				cache[pos * 3 + 1] = 255;
				cache[pos * 3 + 2] = 255;
			    }
			  else if ((n % 7) == 6)
			    {
				cache[pos * 3] = 0;
				cache[pos * 3 + 1] = 156;
				cache[pos * 3 + 2] = 255;
			    }
			  else
			    {
			        cache[pos * 3] = 0;
			        cache[pos * 3 + 1] = 0;
			        cache[pos * 3 + 2] = 255;
			    }
			}
			else
			{
				cache[pos * 3] = 255;
				cache[pos * 3 + 1] = 255;
				cache[pos * 3 + 2] = 255;
			}
		}
	build_bmp(argv[1], width, height, cache);
	delete [] cache;
	return 0;
};
