
#include <iostream>

class Complex
{
public:
	Complex();
	Complex(double r,double i);
	Complex operator+(Complex &d);
	void print();

private:
	double real;
	double imag;
	friend std::ostream& operator<<(std::ostream& os,Complex f);
};

Complex::Complex()
{
	real = 0;
	imag = 0;
}


Complex::Complex(double r,double i)
{
	real = r;
	imag = i;
}

Complex Complex::operator+(Complex &d)
{
	Complex c;
	c.real = real + d.real;
	c.imag = imag + d.imag;
	return c;
}

void Complex::print()
{
	std::cout<<"("<<real<<", "<<imag<<"i)\n";
}

std::ostream& operator<<(std::ostream& os,Complex f);

int main()
{
	Complex c1(3,4),c2(5,-10),c3;
	
	c3 = c1 + c2;
	std::cout<<"c1 = "<<c1<<"\n";
	//c1.print();
	std::cout<<"c2 = "<<c2<<"\n";
	//c2.print();
	std::cout<<"c1 + c2 ="<<c3<<"\n";
	//c3.print();
	
	return 0;
}

std::ostream& operator<<(std::ostream& os,Complex f)
{
	os<<"("<<f.real<<", "<<f.imag<<"i)";
	return os;
}














