#include <iostream>
#include <math.h>

int main()
{
	int i;
	std::cout << "i=";
	std::cin >> i;
	std::cout << std::endl;
	float tab[i][4];
	for(int k=0;k<i;++k)
	{
		std::cout << "--------" << std::endl;
		std::cout << "a_=";
		std::cin >> tab[k][0];
		std::cout << std::endl;
		std::cout << "d_=";
		std::cin >> tab[k][1];
		std::cout << std::endl;
		std::cout << "alfa_=";
		std::cin >> tab[k][2];
		std::cout << std::endl;
		std::cout << "theta_=";
		std::cin >> tab[k][3];
		std::cout << std::endl;
	}
	float tan_psi = (sin(tab[1][2]))/(cos(tab[1][2]));
}
		

