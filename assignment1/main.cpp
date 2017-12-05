// CSE221 Assignment 1

#include "polynomial.h"
#include <iostream>

int main()
{
	Polynomial<double> f, g;
	
	f.CreateTerm(-4.8, 3);

	f.CreateTerm(2.9, 2);
	f.CreateTerm(-3, 0);
	
	std::cout << "f = ";
	f.Print();
	
	g.CreateTerm(4.3, 4);
	g.CreateTerm(-8.1, 0);
	g.CreateTerm(2.2, 3);
	
	std::cout << "g = ";
	g.Print();
	
	g.CreateTerm(3.5,2);
	std::cout << "g (creating a new term) = ";
	g.Print();
	
	// copy constructor test
	std::cout << "h (created from f) = ";
	Polynomial<double> h = f;
	h.Print();
	
	// assignment operator test
	std::cout << "h (assigned from g) = ";
	h = g;	
	h.Print();
	
	// Add test
	std::cout << "f + g = ";
	h = f + g;	
	h.Print();
	
	// Subtract test
	std::cout << "f - g = ";
	h = f - g;
	h.Print();
	
	// Eval test
	std::cout << "f(3.5) is " << f.Eval(3.5) << std::endl;
	
	Polynomial<int> i;
	i.CreateTerm(2.1,2);
	i.CreateTerm(4.8,1);
	i.CreateTerm(3.2,0);
	std::cout << "i (integer coefficients) = ";
	i.Print();
	
	Polynomial<int> j;
	j.CreateTerm(2,1);
	std::cout << "j (integer coefficients) = ";
	j.Print();
	
	// Mult test
	std::cout << "i * j = ";
	Polynomial<int> k = i * j;
	k.Print();
	
	// Eval test
	std::cout << "i(6) = " << i.Eval(6) << std::endl;
	
	return 0;
}
