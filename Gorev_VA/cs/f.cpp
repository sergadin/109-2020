#include <iostream>
#include <vector>

struct Map
{
	int res;
	struct Comp
	{
		int num;
		int quant;
	};
	std::vector < Map::Comp > comp;
	
};

int main()
{
	struct Map M;
	M.res = 2;
	M.comp.resize(2);
	M.comp[0].num = 0;
	M.comp[0].quant = 2;
	M.comp[1].num = 1;
	M.comp[1].quant = 3;
	std::cout << M.res << " " << M.comp[0].num << " " << M.comp[0].quant << " " << M.comp[1].num << " " << M.comp[1].quant;
	return 0;
}
