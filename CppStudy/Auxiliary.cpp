#include "Auxiliary.h"


/////////////////////////////////////////////////////////////////////////////////////////////////  by tora: debug接口： 
namespace MY_DEBUG
{
	void debugDisp()            // 递归终止
	{                        //        递归终止设为无参或者一个参数的情形都可以。
		std::cout << std::endl;
		return;
	}

	void debugDispWStr(const std::wstring& wstr)
	{
		std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));        // 设置wcout的语言环境，缺少这一步打印中文会有错误。
		std::wcout << wstr << std::endl;
	}

}
using namespace MY_DEBUG;



////////////////////////////////////////////////////////////////////////////////////////////// 工具接口
namespace AUXILIARY
{
	// config文件路径字符串字面量 → std::wstring字符串；
	void GetConfigDir(std::wstring& confDir, const TCHAR* pszConfFile)
	{
#ifdef WIN32
		std::wstring strRet(pszConfFile);
		if ((std::string::npos != strRet.find(L"./")) ||
			(std::string::npos != strRet.find(L".\\")))
		{
			TCHAR szCurDir[256] = { 0 };
			GetCurrentDirectory(256, szCurDir);
			confDir = szCurDir;
			confDir += strRet.substr(1, strRet.length());

			return;
		}
		confDir = strRet;
#endif
		return;
	}


	// 读取config文件中的某一个类型为double的键值
	double INIGetFloat(const TCHAR* pszKey, const TCHAR* pszConfFile)
	{
		std::wstring strFileName;
		GetConfigDir(strFileName, pszConfFile);
		TCHAR szValue[256] = { 0 };
		GetPrivateProfileString(L"MY_MESH_CONFIG", pszKey, L"", szValue, 256, strFileName.c_str());

#ifdef UNICODE
		std::string szValue0 = ws2s(szValue);
		return atof(szValue0.c_str());
#else
		return atof(szValue);
#endif 

	}


	// 读取config文件中的某一个类型为int的键值
	DWORD INIGetInt(const TCHAR* pszKey, const TCHAR* pszConfFile)
	{
#ifdef WIN32
		std::wstring strFileName;
		GetConfigDir(strFileName, pszConfFile);
		return GetPrivateProfileInt(L"MY_MESH_CONFIG", pszKey, 0, strFileName.c_str());
#else
		return 0;
#endif
	}

}
using namespace AUXILIARY;



////////////////////////////////////////////////////////////////////////////////////////////// 工具接口——字符串、文件系统相关
namespace AUXILIARY_STRING_FILE
{
	void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
	{
		std::string::size_type pos1, pos2;
		pos2 = s.find(c);
		pos1 = 0;
		while (std::string::npos != pos2)
		{
			v.push_back(s.substr(pos1, pos2 - pos1));

			pos1 = pos2 + c.size();
			pos2 = s.find(c, pos1);
		}
		if (pos1 != s.length())
			v.push_back(s.substr(pos1));
	}


	// 字符串转换为宽字符串；
	std::wstring s2ws(const std::string& s)
	{
		std::locale old_loc = std::locale::global(std::locale(""));
		const char* src_str = s.c_str();
		const size_t buffer_size = s.size() + 1;
		wchar_t* dst_wstr = new wchar_t[buffer_size];
		wmemset(dst_wstr, 0, buffer_size);
		mbstowcs(dst_wstr, src_str, buffer_size);
		std::wstring result = dst_wstr;
		delete[]dst_wstr;
		std::locale::global(old_loc);
		return result;
	}


	// 宽字符串转换为字符串；
	std::string ws2s(const std::wstring& ws)
	{
		std::locale old_loc = std::locale::global(std::locale(""));
		const wchar_t* src_wstr = ws.c_str();
		size_t buffer_size = ws.size() * 4 + 1;
		char* dst_str = new char[buffer_size];
		memset(dst_str, 0, buffer_size);
		wcstombs(dst_str, src_wstr, buffer_size);
		std::string result = dst_str;
		delete[]dst_str;
		std::locale::global(old_loc);
		return result;
	}


	// 在指定目录下创建文件夹：
	bool CreateFolder(const std::string& dirPath)
	{
		bool retFlag = false;

		// 1. 生成路径宽字符串： 
		std::wstring wdirPath = s2ws(dirPath);

		// 2. 创建文件夹
#ifdef _WIN32
		int retInt = CreateDirectory(wdirPath.c_str(), NULL);
		retFlag = (retInt > 0);
#endif 

		return retFlag;
	}


	// 检测路径是否存在
	bool CheckValidPath(const std::string& path)
	{
		bool retFlag = false;

		// 1. 生成路径宽字符串： 
		std::wstring wPath = s2ws(path);

		// 2. 使用GetFileAttributes()判断路径属性：
#ifdef _WIN32 
		DWORD attributes = GetFileAttributes(wPath.c_str());
		if (attributes != INVALID_FILE_ATTRIBUTES)
			retFlag = true;
#endif 
		return retFlag;
	}


	// 返回正确的文件夹路径
	std::string CorrectDirPath(const std::string& dirPath)
	{
		const size_t length = dirPath.length();
		if (length < 2)
			return dirPath;
		if ('/' == *dirPath.rbegin() || '\\' == *dirPath.rbegin())
			return dirPath;
		else
			return dirPath + "/";
	}


	// 输入文件完整路径，输出文件名字符串
	std::string ExtractFileName(const std::string& filePath)
	{
		std::string retStr;
		size_t posNum{ 0 };
		if (filePath.empty())
			return retStr;

		size_t posNum1 = filePath.find_last_of("\\");
		size_t posNum2 = filePath.find_last_of("/");
		int pn1 = std::string::npos == posNum1 ? -1 : static_cast<int>(posNum1);
		int pn2 = std::string::npos == posNum2 ? -1 : static_cast<int>(posNum2);
		if (pn1 < 0 && pn2 < 0)
			return filePath;
		posNum = pn1 < pn2 ? posNum2 : posNum1;
		if (posNum >= filePath.size() - 1)
			return retStr;
		retStr = &filePath[posNum + 1];

		return retStr;
	}


	// 输入文件夹完整路径，输出文件夹名称（不包括末尾的'/'或'\\'）：
	std::string ExtractDirName(const std::string& dirPath)
	{
		std::string path = dirPath;
		if ('\\' == *path.rbegin() || '/' == *path.rbegin())
			path.erase(path.size() - 1);
		return ExtractFileName(path);
	}


	// 输入文件名或文件完整路径，输出文件后缀名字符串（包括'.'）
	std::string ExtractNameExt(const std::string& filePath)
	{
		std::string retStr;
		size_t posNum{ 0 };
		if (filePath.empty())
			return retStr;
		posNum = filePath.find_last_of(".");
		if (posNum >= filePath.size() - 1)
			return retStr;
		retStr = &filePath[posNum];
		return retStr;
	}


	// 输入文件完整路径（末尾不能是"/"或"\\"），输出其所在文件夹完整路径，末尾没有"/"或"\\"
	std::string ExtractFileDir(const std::string& filePath)
	{
		std::string retStr;
		size_t posNum{ 0 };
		if (filePath.empty())
			return retStr;

		size_t posNum1 = filePath.find_last_of("\\");
		size_t posNum2 = filePath.find_last_of("/");
		int pn1 = std::string::npos == posNum1 ? -1 : static_cast<int>(posNum1);
		int pn2 = std::string::npos == posNum2 ? -1 : static_cast<int>(posNum2);
		if (pn1 < 0 && pn2 < 0)
			return retStr;
		posNum = pn1 < pn2 ? posNum2 : posNum1;
		if (posNum >= filePath.size() - 1)
			return retStr;
		retStr = filePath.substr(0, posNum);

		if ("." == retStr)
			return std::string{};

		return retStr;
	}


	// 生成头部补0的数字字符串：
	std::string formatNumWithLeadingZeros(const int number, const size_t width)
	{
		std::stringstream ss;
		ss << std::setw(width) << std::setfill('0') << number;            // 需要<iomanip>
		return ss.str();
	}


	// （递归）读取输入目录下的所有文件
	void GetFileNames(std::vector<std::string>& files, std::string path, const bool blSenseDir)
	{
#ifdef _WIN32
		intptr_t hFile = 0;                     // 文件句柄；注意：我发现有些文章代码此处是long类型，实测运行中会报错访问异常 
		struct _finddata_t fileinfo;        // 文件信息
		std::string tmpPath;
		if ('/' != *path.crbegin() && '\\' != *path.crbegin())
			path.assign(path).append("/");
		if ((hFile = _findfirst(tmpPath.assign(path).append("*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				// 如果是目录，递归查找；如果不是,把文件绝对路径存入vector中
				if (fileinfo.attrib & _A_SUBDIR)
				{
					if (blSenseDir && strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						GetFileNames(files, tmpPath.assign(path).append(fileinfo.name), blSenseDir);
				}
				else
					files.push_back(tmpPath.assign(path).append(fileinfo.name));
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
#else
		// to be optimized....
		DIR* pDir;
		struct dirent* ptr;
		if (!(pDir = opendir(path.c_str())))
			return;
		while ((ptr = readdir(pDir)) != 0)
			if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
				files.push_back(path + "/" + ptr->d_name);
		closedir(pDir);
#endif
	}


	// 读取输入目录下的所有文件夹
	void GetDirNames(std::vector<std::string>& files, std::string path)
	{
#ifdef _WIN32
		intptr_t hFile = 0;                     // 文件句柄；注意：我发现有些文章代码此处是long类型，实测运行中会报错访问异常
		struct _finddata_t fileinfo;        // 文件信息
		std::string tmpPath;
		if ('/' != *path.crbegin() && '\\' != *path.crbegin())
			path.assign(path).append("/");
		if ((hFile = _findfirst(tmpPath.assign(path).append("*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				if (fileinfo.attrib & _A_SUBDIR)
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						files.push_back(tmpPath.assign(path).append(fileinfo.name).append("/"));
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
#else
		// to be optimized....
		DIR* pDir;
		struct dirent* ptr;
		if (!(pDir = opendir(path.c_str())))
			return;
		while ((ptr = readdir(pDir)) != 0)
			if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
				files.push_back(path + "/" + ptr->d_name);
		closedir(pDir);
#endif
	}


	// 复制文件：
	bool CopyFileViaWinAPI(const std::string& outputPath, const std::string& inputPath)
	{
		const std::string destDir = ExtractFileDir(outputPath);
		const LPCSTR sourceFile = inputPath.c_str();
		const LPCSTR destFolder = destDir.c_str();
		const LPCSTR destFilePath = outputPath.c_str();

		// 1. 检查目标文件夹是否存在
		DWORD folderAttr = GetFileAttributesA(destFolder);
		if (folderAttr == INVALID_FILE_ATTRIBUTES || !(folderAttr & FILE_ATTRIBUTE_DIRECTORY))
			return false;

		// 2. 复制文件
		if (!CopyFileA(sourceFile, destFilePath, FALSE))
		{
			std::cerr << "文件复制失败，错误代码：" << GetLastError() << "\n";
			return false;
		}

		return true;
	}

}

