

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


int main()
{
	std::vector<std::string> names;
	
	names.push_back("Darbuly");
	names.push_back("Lola");
	names.push_back("Dingding");
	names.push_back("Joy");
	names.push_back("Micheal");
	names.push_back("Lucy");
	names.push_back("Lilei");
	
	std::sort(names.begin(),names.end());
	




	std::vector<std::string>::iterator iter = names.begin();
	
	while(iter!=names.end())
	{
		std::cout<< *iter<<"\n";
		++iter;
	}


	return 0;
}

