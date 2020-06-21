


#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
	int ia[6] = {27,217,12,47,109,83};
	std::vector<int,std::allocator<int> > vi(ia,ia+6);

	std::cout<<std::count_if(vi.begin(),vi.end(),std::not1(std::bind2nd(std::less<int>(),40)));

	return 0;
}
