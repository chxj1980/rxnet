#include "rxfileutil.h"

#ifdef _WIN32
#include <io.h>
#else
#include <sys/io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/io.h>
#endif

using namespace std;
using namespace rxnet;
using namespace coreutil;

int rxfileutil::getfilesize(std::string spath)
{
#ifndef _WIN32
	struct stat info;  
	stat(spath.c_str(), &info);  
	int size = info.st_size;
	//int size = 0;
	//FILE* file = fopen(spath.c_str(), "rb");  
	//if (file)  
	//{  
	//    size = fseek(file, 0, SEEK_END);  
	//    cout<< size<< endl;  
	//    fclose(file);  
	//} 
#else
#if 0
	HANDLE handle = CreateFile(filepath, FILE_READ_EA, 
	FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);  
	if (handle != INVALID_HANDLE_VALUE)  
	{  
    		int size = GetFileSize(handle, NULL);  
        	CloseHandle(handle);
		return size; 
        }
	//int size = 0;
	//FILE* file = fopen(spath.c_str(), "rb");  
	//if (file)  
	//{  
	//    size = filelength(fileno(file));  
	//    cout<< size<< endl;  
	//    fclose(file);  
	//} 
#endif
	struct _stat info;  
	_stat(spath.c_str(), &info);  
	int size = info.st_size;
#endif
	return size;
}


//遍历文件夹
//返回值:文件个数
//输入参数:文件夹路径
//输出参数:文件路径，文件大小
int rxfileutil::reversefile(std::string spath, std::vector<std::map<std::string, int>> &arrFileList)
{
	return arrFileList.size();
}
			
//遍历文件夹
//返回值:文件个数
//输入参数:文件夹路径
//输出参数:文件路径，文件大小，文件类型
int rxfileutil::reversefile(std::string spath, std::vector<std::tuple<std::string, int, int>> &arrFileList, int depth, string sdepthpath)
{
#ifdef _WIN32
	long hFile = 0;
    	struct _finddata_t fileInfo;
	string pathName;
	if ( ( hFile = _findfirst(pathName.assign(spath).append("\\*").c_str(), &fileInfo) ) == -1)
		return ;
	do {
		cout << spath+"\\"+fileInfo.name << endl;
		if( strcmp(fileInfo.name,"..") && strcmp(fileInfo.name,".") && fileInfo.attrib==_A_SUBDIR)
		
		//递归遍历
		reversefile(path+"\\"+fileInfo.name, arrFileList);
	} while ( _findnext(hFile, &fileInfo) == 0 );
	_findclose(hFile);
#else
	DIR *p_dir = NULL;
	struct dirent *p_entry = NULL;
	struct stat statbuf;

	if((p_dir = opendir(spath.c_str())) == NULL)
	{
		printf("can't open dir.\n");
		return arrFileList.size();
	}
	chdir (spath.c_str());
	while(NULL != (p_entry = readdir(p_dir))) 
	{
		lstat(p_entry->d_name, &statbuf);
		if(S_IFDIR & statbuf.st_mode) {
			if (strcmp(".", p_entry->d_name) == 0 || strcmp("..", p_entry->d_name) == 0)
				continue;
			//printf("%*s%s/\n", depth, "", p_entry->d_name);
			std::string sttpath = spath;
			sttpath += "/";
			sttpath += p_entry->d_name;
			reversefile(p_entry->d_name, arrFileList, depth+4, sttpath); // 扫描下一级目录的内容
		} 
		else 
		{
			//printf("%*s%s\n", depth, "", p_entry->d_name);// 输出属性不是目录的成员
			std::string strtmppath = sdepthpath;
			strtmppath += "/";
			strtmppath += p_entry->d_name;
			std::cout << "path:" << strtmppath.c_str() << std::endl;;
		}
	}
	chdir(".."); // 回到上级目录
	closedir(p_dir);
#endif
	return arrFileList.size();
}
