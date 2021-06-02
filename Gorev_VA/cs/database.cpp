#include <vector>
#include <string>
#include <iostream>

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "database.h"
#include "server.h"
#include <sstream>

int main()
{
	Base B;
	/*std::string S = "AAA";
	B.add_detail(S, 78);
	B.add_detail("BBBB", 200);
	B.add_detail("CCC", 300);
	std::cout << B.num << ", " << B.name[0] << ", " << B.hash_name[3][0] << "\n";
	std::cout << B.num << ", " << B.name[1] << ", " << B.hash_name[4][0] << "\n";
	std::cout << B.num << ", " << B.name[2] << ", " << B.hash_name[3][1] << "\n";
	
	std::vector <int> m, mm;
	m.resize(5);
	mm.resize(5);
	m[0] = 5, m[1] = 4, m[2] = 3, m[3] = 2, m[4] = 1;
	mm[0] = 5, mm[1] = 2, mm[2] = 1, mm[3] = 4, mm[4] = 3;
	std::cout << B.map_eq(m, mm) << "\n";
	m[0] = 5, m[1] = 4, m[2] = 3, m[3] = 2, m[4] = 1;
	mm[0] = 5, mm[1] = 2, mm[2] = 1, mm[3] = 4, mm[4] = 4;
	std::cout << B.map_eq(m, mm) << "\n";
	m[0] = 5, m[1] = 4, m[2] = 3, m[3] = 2, m[4] = 1;
	mm[0] = 5, mm[1] = 1, mm[2] = 1, mm[3] = 4, mm[4] = 3;
	std::cout << B.map_eq(m, mm) << "\n";
	//std::cout << m[0] << m[1] << m[2] << m[3] << m[4] << "\n";
	//B.show_base();
	
	std::vector <int> M(5);
	M[0] = 2, M[1] = 0, M[2] = 20, M[3] = 1, M[4] = 47;
	B.add_map(M);
	B.add_map(M);
	B.add_detail(S, 1);
	//B.show_base();
	M[2] = 10;
	B.add_map(M);
	//B.show_maps();
	
	std::vector <std::string> V(5);
	V[0] = "CCC", V[1] = "AAA", V[2] = "10", V[3] = "BBBB", V[4] = "470";
	std::cout << B.find_map(V);
	B.add_map(V);
	B.show_base();
	
	std::vector <std::string> VV(5);
	VV[0] = "CCC", VV[1] = "AAA", VV[2] = "20", VV[3] = "BBBB", VV[4] = "47";
	std::cout << B.can_build_map(B.map[1]) << " " << B.can_build_map(VV);
	
	
	B.show_details();*/
	
	B.add_detail("AAA", 12);
	B.add_detail("BBB", 10);
	B.add_detail("CCC", 10);
	struct Map M;
	M.resize(2);
	M.res = 2, M.comp[0].num = 0, M.comp[0].quant = 2, M.comp[1].num = 1, M.comp[1].quant = 3;
	struct Map MM;
	MM.resize(1);
	MM.res = 1, MM.comp[0].num = 0, MM.comp[0].quant = 2;
	B.add_map(M);
	B.add_map(MM);
	B.show_base();
	
	std::cout << B.can_build_map(1) << "\n";
	std::cout << B.build_map(1, 3);
	B.show_details();
	std::cout << "\n\n\n";
	
	std::ifstream in("database.txt");
	std::string stri = "CCC AAA 1 BBB 22 end   BBB AAA 2 end";
	std::istringstream sin(stri);
	char ch[1024] = "CCC AAA 1 BBB 22 end   BBB AAA 2 end";
	std::istringstream ssin(ch);
	
	B.do_from(in);
	B.do_from(sin);
	B.do_from(ssin);
	return 0;
}
