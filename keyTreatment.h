#include <iostream>
#include <map>
#include <functional>

using namespace std;
class keyTreatment {
	
public:
	void setF(void(*k)(), int key/*Sample text*/)
	{
		ptof[key] = k;
	}
	void test(int key/*Sample text*/)
	{
		ptof[key]();
	}
private:
	map <int/*Sample text*/,void (*)()> ptof;
};
