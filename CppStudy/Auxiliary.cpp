#include "Auxiliary.h"


/////////////////////////////////////////////////////////////////////////////////////////////////  by tora: debug�ӿڣ� 
namespace MY_DEBUG
{
	void debugDisp()            // �ݹ���ֹ
	{                        //        �ݹ���ֹ��Ϊ�޲λ���һ�����������ζ����ԡ�
		std::cout << std::endl;
		return;
	}

	void debugDispWStr(const std::wstring& wstr)
	{
		std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));        // ����wcout�����Ի�����ȱ����һ����ӡ���Ļ��д���
		std::wcout << wstr << std::endl;
	}

}
using namespace MY_DEBUG;



////////////////////////////////////////////////////////////////////////////////////////////// ���߽ӿ�
namespace AUXILIARY
{
	// config�ļ�·���ַ��������� �� std::wstring�ַ�����
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


	// ��ȡconfig�ļ��е�ĳһ������Ϊdouble�ļ�ֵ
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


	// ��ȡconfig�ļ��е�ĳһ������Ϊint�ļ�ֵ
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



////////////////////////////////////////////////////////////////////////////////////////////// ���߽ӿڡ����ַ������ļ�ϵͳ���
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


	// �ַ���ת��Ϊ���ַ�����
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


	// ���ַ���ת��Ϊ�ַ�����
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


	// ��ָ��Ŀ¼�´����ļ��У�
	bool CreateFolder(const std::string& dirPath)
	{
		bool retFlag = false;

		// 1. ����·�����ַ����� 
		std::wstring wdirPath = s2ws(dirPath);

		// 2. �����ļ���
#ifdef _WIN32
		int retInt = CreateDirectory(wdirPath.c_str(), NULL);
		retFlag = (retInt > 0);
#endif 

		return retFlag;
	}


	// ���·���Ƿ����
	bool CheckValidPath(const std::string& path)
	{
		bool retFlag = false;

		// 1. ����·�����ַ����� 
		std::wstring wPath = s2ws(path);

		// 2. ʹ��GetFileAttributes()�ж�·�����ԣ�
#ifdef _WIN32 
		DWORD attributes = GetFileAttributes(wPath.c_str());
		if (attributes != INVALID_FILE_ATTRIBUTES)
			retFlag = true;
#endif 
		return retFlag;
	}


	// ������ȷ���ļ���·��
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


	// �����ļ�����·��������ļ����ַ���
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


	// �����ļ�������·��������ļ������ƣ�������ĩβ��'/'��'\\'����
	std::string ExtractDirName(const std::string& dirPath)
	{
		std::string path = dirPath;
		if ('\\' == *path.rbegin() || '/' == *path.rbegin())
			path.erase(path.size() - 1);
		return ExtractFileName(path);
	}


	// �����ļ������ļ�����·��������ļ���׺���ַ���������'.'��
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


	// �����ļ�����·����ĩβ������"/"��"\\"��������������ļ�������·����ĩβû��"/"��"\\"
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


	// ����ͷ����0�������ַ�����
	std::string formatNumWithLeadingZeros(const int number, const size_t width)
	{
		std::stringstream ss;
		ss << std::setw(width) << std::setfill('0') << number;            // ��Ҫ<iomanip>
		return ss.str();
	}


	// ���ݹ飩��ȡ����Ŀ¼�µ������ļ�
	void GetFileNames(std::vector<std::string>& files, std::string path, const bool blSenseDir)
	{
#ifdef _WIN32
		intptr_t hFile = 0;                     // �ļ������ע�⣺�ҷ�����Щ���´���˴���long���ͣ�ʵ�������лᱨ������쳣 
		struct _finddata_t fileinfo;        // �ļ���Ϣ
		std::string tmpPath;
		if ('/' != *path.crbegin() && '\\' != *path.crbegin())
			path.assign(path).append("/");
		if ((hFile = _findfirst(tmpPath.assign(path).append("*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				// �����Ŀ¼���ݹ���ң��������,���ļ�����·������vector��
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


	// ��ȡ����Ŀ¼�µ������ļ���
	void GetDirNames(std::vector<std::string>& files, std::string path)
	{
#ifdef _WIN32
		intptr_t hFile = 0;                     // �ļ������ע�⣺�ҷ�����Щ���´���˴���long���ͣ�ʵ�������лᱨ������쳣
		struct _finddata_t fileinfo;        // �ļ���Ϣ
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


	// �����ļ���
	bool CopyFileViaWinAPI(const std::string& outputPath, const std::string& inputPath)
	{
		const std::string destDir = ExtractFileDir(outputPath);
		const LPCSTR sourceFile = inputPath.c_str();
		const LPCSTR destFolder = destDir.c_str();
		const LPCSTR destFilePath = outputPath.c_str();

		// 1. ���Ŀ���ļ����Ƿ����
		DWORD folderAttr = GetFileAttributesA(destFolder);
		if (folderAttr == INVALID_FILE_ATTRIBUTES || !(folderAttr & FILE_ATTRIBUTE_DIRECTORY))
			return false;

		// 2. �����ļ�
		if (!CopyFileA(sourceFile, destFilePath, FALSE))
		{
			std::cerr << "�ļ�����ʧ�ܣ�������룺" << GetLastError() << "\n";
			return false;
		}

		return true;
	}

}

