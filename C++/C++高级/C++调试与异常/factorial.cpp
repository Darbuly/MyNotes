
#include <iostream>
#include <climits>

class Factorial
{
public:	
	Factorial(unsigned short num);
	unsigned long getFactorial();
	
	bool inRange();
private:
	unsigned short num;
};

Factorial::Factorial(unsigned short num)
{
	this->num = num;
}

unsigned long Factorial::getFactorial()
{
	unsigned long sum = 1;
	
	for(int i=1;i<=num;i++)
	{
		sum*=i;
	}	

	return sum;
}

bool Factorial::inRange()
{
	unsigned long max = ULONG_MAX;
	for(int i=num;i>=1;i--)
	{
		max/=i;
	}
	if(max<1)
	{
		return false;
	}
	else
	{
		return true;
	}
}


int main()
{
	unsigned short num=0;
	std::cout<<"enter a number:";
	std::cin>>num;
	
	Factorial fac(num);
	if(fac.inRange())
	{
		std::cout<<num<<" 's Factorial is "<<fac.getFactorial()<<"\n\n";
	}
	else
	{
		std::cout<<"OverFlow!!!\n\n";
	}
	return 0;
}

















