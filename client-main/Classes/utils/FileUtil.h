#ifndef _FILE_UTIL_H_
#define _FILE_UTIL_H_


#include <string> 
using namespace std;
class FileUtil
{
public:
	FileUtil(void);
	~FileUtil(void);

public:
	static string read(const char *fileName);
	static void write(const char *fileName,const char *buff);
};
#endif
