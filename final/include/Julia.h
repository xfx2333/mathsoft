#include <complex>

class Iteration
{
protected:
	std::complex<double> iteration_point{0.0, 0.0};
	std::complex<double> iteration_const{0.0, 0.0};
	bool flag_stop = false;
public:
	Iteration(){};
	Iteration(std::complex<double> _ip,
			  std::complex<double> _ic) :
		iteration_point(_ip),
		iteration_const(_ic) {};
	Iteration(double _ix,
			  double _iy,
			  double _cx,
			  double _cy) :
		iteration_point(std::complex<double>{_ix, _iy}),
		iteration_const(std::complex<double>{_cx, _cy}) {};
	std::complex<double> get_iteration_point()
	{
		return iteration_point;
	};
	std::complex<double> get_iteration_const()
	{
		return iteration_const;
	};
	virtual void forward_step() = 0;
	virtual bool stop_criterion() = 0;
};

class Julia : public Iteration
{
public:
	Julia() : Iteration() {};
	Julia(std::complex<double> _ip,
			   std::complex<double> _ic) : Iteration(_ip, _ic) {};
	Julia(double _ix,
			   double _iy,
			   double _cx,
			   double _cy) : Iteration(_ix, _iy, _cx, _cy) {};
	virtual void forward_step();
	virtual bool stop_criterion();
};

void Julia::forward_step()
{
	iteration_point = iteration_point * iteration_point + iteration_const;
	if (std::abs(iteration_point) > 1000000.0)
		flag_stop = true;
};

bool Julia::stop_criterion()
{
	return flag_stop;
};
