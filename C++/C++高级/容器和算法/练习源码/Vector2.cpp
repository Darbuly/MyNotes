

#include <iostream>
#include <string>
#include <vector>


int main()
{
	std::vector<std::string> names;
	
	names.push_back("Darbuly");
	names.push_back("DBL");
	
	std::vector<std::string>::iterator iter = names.begin();
	
	while(iter!=names.end())
	{
		std::cout<< *iter<<"\n";
		++iter;
	}


	return 0;
}

