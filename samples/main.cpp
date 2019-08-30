#include "rxfileutil.h"

using namespace std;
using namespace rxnet;
using namespace coreutil;


int main(int argc, char* agrv[])
{
	rxfileutil* rft = new rxfileutil();
        std::vector<std::tuple<std::string, int, int>> arrFileList;
	rft->reversefile("./", arrFileList, 2, "./");	
	return 0;
}
