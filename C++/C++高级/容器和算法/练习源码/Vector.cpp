

#include <iostream>
#include <string>
#include <vector>


int main()
{
	std::vector<std::string> names;
	
	names.push_back("Darbuly");
	names.push_back("DBL");

	for(int i=0;i<names.size();i++)
	{
		std::cout<<names[i]<<"\n";
	}
	
	return 0;
}

