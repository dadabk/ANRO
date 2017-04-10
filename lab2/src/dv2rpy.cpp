#include <iostream>
#include <math.h>
#include <cmath>

int main()
{
	int i;
	std::cout << "i=";
	std::cin >> i;
	std::cout << std::endl;
	float tab[i][4];
	for(int k=0;k<i;++k)
	{
		std::cout << "-------- i=" << k+1 << std::endl;
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
	for (int o=0; o<i; ++o)
	{	
		float cos_theta = cos(tab[o][3]);
		float sin_theta = sin(tab[o][3]);
		float cos_alpha = cos(tab[o][2]);
		float sin_alpha = sin(tab[o][2]);

		float fi = atan2(cos_theta*sin_alpha, cos_alpha);
		float theta = atan2(-1*sin_theta*sin_alpha, sqrt(1 - cos_theta*sin_alpha*cos_theta*sin_alpha));
		float psi = atan2(sin_theta*cos_alpha, cos_theta);

		std::cout << "roll: " << psi << " pitch: " << theta << " yaw: " << fi << std::endl;
	}
}
		

