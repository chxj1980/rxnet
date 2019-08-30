#ifndef _RX_FILE_UTIL_H_
#define _RX_FILE_UTIL_H_

#include <iostream>
#include <vector>
#include <map>
#include <tuple>

namespace rxnet{
	namespace coreutil{
		class rxfileutil{
			public:
				rxfileutil(){};
				virtual ~rxfileutil(){};

			//遍历文件夹
			//返回值:文件个数
			//输入参数:文件夹路径
			//输出参数:文件路径，文件大小
			int reversefile(std::string spath, std::vector<std::map<std::string, int>> &arrFileList);
			
			//遍历文件夹
			//返回值:文件个数
			//输入参数:文件夹路径
			//输出参数:文件路径，文件大小，文件类型
			int reversefile(std::string spath, std::vector<std::tuple<std::string, int, int>> &arrFileList, int depth, std::string sdepthpath);


			//获取文件大小
			int getfilesize(std::string spath);	
		};
	}
}

#endif
