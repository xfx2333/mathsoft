#include <iostream>
#include <cstdlib>
#include "Window.h"
#include "Julia.h"
#include "bitmap.h"

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		std::cerr << "Usage: " << argv[0]
				  << " filename cx cy " << std::endl;
		exit(-1);
	}
	
	Window win(std::atof(argv[2]), std::atof(argv[3]));
	double lpp = win.get_lpp();
	double dim = win.get_dimension();
	int width = win.get_width();
	int height = win.get_height();
	double cx = win.get_ox();
	double ox = - dim;
	double cy = win.get_oy();
	double oy = - dim / width * height;

	char *cache = new char[width * height * 3];

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
			double x = ox + lpp * i;
			double y = oy + lpp * j;
			int pos = width * j + i;
			int k  = 0;
			Julia jun(std::complex<double>{x, y},
						   std::complex<double>{cx, cy});
			while (!jun.stop_criterion())
			{
				jun.forward_step();
				k++;
				if (k == 255)
				  break;
			}
			if (k!=255)
			  {
			    if (k % 7 == 0)
			       {
			          cache[pos * 3] = 0 ;
			          cache[pos * 3 + 1] = 0;
			          cache[pos * 3 + 2] = 255;
			       }
			    else if (k % 7 == 1)
			      {
			          cache[pos * 3] = 0 ;
			          cache[pos * 3 + 1] = 128;
			          cache[pos * 3 + 2] = 255;
			       }
			    else if (k % 7 == 2)
			      {
			          cache[pos * 3] = 0 ;
			          cache[pos * 3 + 1] = 255;
			          cache[pos * 3 + 2] = 255;
			       }
			    else if (k % 7 == 3)
			      {
			          cache[pos * 3] = 0;
			          cache[pos * 3 + 1] = 128;
			          cache[pos * 3 + 2] = 0;
			       }
			    else if (k % 7 == 4)
			      {
			          cache[pos * 3] = 128;
			          cache[pos * 3 + 1] = 128;
			          cache[pos * 3 + 2] = 0;
			       }
			    else if (k % 7 == 5)
			      {
			          cache[pos * 3] = 255;
			          cache[pos * 3 + 1] = 0;
			          cache[pos * 3 + 2] = 0;
			       }
			    else
			      {
			          cache[pos * 3] = 128;
			          cache[pos * 3 + 1] = 0;
			          cache[pos * 3 + 2] = 128;
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

