#pragma once 
// �Լ�д�ĸ����ӿڣ�ֻ�漰C++�������ͣ�

#include <iostream>
#include <fstream>
#include <sstream>			// �ַ�����
#include <iomanip>

#include <iterator>
#include <utility>

#include <string>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <initializer_list>
#include <bitset>	

#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>				// �ṩstd::numeric_limits<>ģ��

#include <cmath>
#include <random>
#include <ctime>
#include <typeinfo>
#include <type_traits>

#include <memory> 
#include <thread>					// c++�߳�֧�ֿ�
#include <mutex>
#include <atomic>			// ԭ������ 
#include <cassert>			// ����

// MFC
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif 
#include <windows.h> 
#include <atlstr.h>				// ����CString�ࡣ����microsoft ATL(�ģ���avtive template library)
#include <io.h>
#endif  
   
#include <omp.h>			// openMP


// #define USE_BOOST
#ifdef  USE_BOOST
#include <boost/tuple/tuple.hpp>
#endif  
 

// �ڴ��CPU���ӽӿ���Ҫ��һЩͷ�ļ���
#ifdef _WIN32 
#include <psapi.h>   
#include <direct.h>
#include <process.h>
#else
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <unistd.h>
#endif


#define BLUE_REGION
#ifdef BLUE_REGION
const std::string g_samplePath = "C:/myData/";
const std::string g_debugPath = "C:/myData/output/";
#else
const std::string g_samplePath = "E:/myData/";
const std::string g_debugPath = "E:/outputData/";
#endif   


////////////////////////////////////////////////////////////////////////////////////////////// ���߽ӿ�
namespace AUXILIARY
{
    enum class DATA_TYPE_ENUM
    {
        UNSUPPORTED = -1,
        UNSIGNED_CHAR = 0,
        CHAR = 1,
        UINT32 = 2,
        UINT64 = 3,
        INT32 = 4,
        INT64 = 5,
        FLOAT32 = 6,
        FLOAT64 = 7,
    };


    // �����ӡ�����ӡstd::cout֧�ֵ����ͱ�����
    template <typename	T>
    class disp
    {
    public:
        void operator()(const T& arg)
        {
            std::cout << arg << ", ";
        }
    };


    // �����ӡ�����ӡstd::pair
    template <typename pairType>
    class dispPair
    {
    public:
        void operator()(const pairType& p)
        {
            std::cout << "(" << p.first << ", " << p.second << "), ";
        }

        void operator()(const std::string& str, const pairType& p)
        {
            std::cout << str << "(" << p.first << ", " << p.second << "), ";
        }
    };


    // ���뺯���ӻ���ָ�����stl����
    template<typename T, typename F>
    void traverseSTL(T& con, F f, const std::string& headStr = std::string{})
    {
        if (!headStr.empty())
            std::cout << headStr << std::endl;
        std::for_each(con.begin(), con.end(), f);
        std::cout << std::endl;
    }


    // ���뺯���ӻ���ָ�����std::map, std::unordered_map��
    template<typename mapType, typename F>
    void traverseSTLmap(mapType& m, F f)
    {
        std::for_each(m.begin(), m.end(), f);
        std::cout << std::endl;
    }


    // �������
    template<typename T, typename F>
    void revTraverseSTL(T& con, F f)
    {
        std::for_each(con.rbegin(), con.rend(), f);
        std::cout << std::endl;
    } 
     

    // ����forѭ���������뺯����ԭ��Ϊ��void(const size_t index)
    template<typename Func>
    void PARALLEL_FOR(size_t beg, size_t end, \
        const Func& func, const size_t serial_if_less_than = 12)
    {
        /*
            PARALLEL_FOR(
                size_t   beg,                                     ��ʼԪ������
                size_t  end,                                      βԪ������
                const size_t  serial_if_less_than,      �����Ҫ�����Ԫ�ز�С�ڸ�ֵ����ʹ�ò��л���
                const Func & func										����Ԫ�صĺ����ӣ�
                )
        */
        size_t elemCount = end - beg + 1;

        if (elemCount < serial_if_less_than)
            for (size_t i = beg; i < end; ++i)
                func(i);
        else
        {
            // ȷ������߳�����
            const static unsigned n_threads_hint = std::thread::hardware_concurrency();
            const static unsigned n_threads = (n_threads_hint == 0u) ? 8u : n_threads_hint;

            // forѭ���ķ�Χ�ֽ�ɼ��Σ�
            size_t slice = (size_t)std::round(elemCount / static_cast<double>(n_threads));
            if (slice < 1u)
                slice = 1u;

            // �̺߳�����
            auto subTraverse = [&func](size_t head, size_t tail)
                {
                    for (size_t k = head; k < tail; ++k)
                        func(k);
                };

            // �����̳߳أ�ִ�в���forѭ����
            std::vector<std::thread> pool;              // �̳߳أ�
            pool.reserve(n_threads);
            size_t head = beg;
            size_t tail = (beg + slice < end) ? (beg + slice) : end;
            for (size_t i = 0; i + 1 < n_threads && head < end; ++i)
            {
                pool.emplace_back(subTraverse, head, tail);
                head = tail;
                tail = (tail + slice < end) ? (tail + slice) : end;
            }
            if (head < end)
                pool.emplace_back(subTraverse, head, end);

            // �߳�ͬ����
            for (std::thread& t : pool)
            {
                if (t.joinable())
                    t.join();
            }
        }
    }


    // ��β���forѭ��������������Ĳ���ʹ��std::tuple���룻
    template<typename Func, typename paramTuple>
    void PARALLEL_FOR(size_t beg, size_t end, const Func& func, \
        const paramTuple& pt, const size_t serial_if_less_than = 12)
    {
        /*
            PARALLEL_FOR(
                size_t   beg,                                     ��ʼԪ������
                size_t  end,                                      βԪ������
                const size_t  serial_if_less_than,      �����Ҫ�����Ԫ�ز�С�ڸ�ֵ����ʹ�ò��л���
                const paramTuple& pt								�������������������
                const Func & func										����Ԫ�صĺ����ӣ�
                )
        */
        size_t elemCount = end - beg + 1;

        if (elemCount < serial_if_less_than)
            for (size_t i = beg; i < end; ++i)
                func(i, pt);
        else
        {
            // ȷ������߳�����
            const static unsigned n_threads_hint = std::thread::hardware_concurrency();
            const static unsigned n_threads = (n_threads_hint == 0u) ? 8u : n_threads_hint;

            // forѭ���ķ�Χ�ֽ�ɼ��Σ�
            size_t slice = (size_t)std::round(elemCount / static_cast<double>(n_threads));
            if (slice < 1u)
                slice = 1u;

            // �̺߳�����
            auto subTraverse = [&func, &pt](size_t head, size_t tail)
                {
                    for (size_t k = head; k < tail; ++k)
                        func(k, pt);
                };

            // �����̳߳أ�ִ�в���forѭ����
            std::vector<std::thread> pool;              // �̳߳أ�
            pool.reserve(n_threads);
            size_t head = beg;
            size_t tail = (beg + slice < end) ? (beg + slice) : end;
            for (size_t i = 0; i + 1 < n_threads && head < end; ++i)
            {
                pool.emplace_back(subTraverse, head, tail);
                head = tail;
                tail = (tail + slice < end) ? (tail + slice) : end;
            }
            if (head < end)
                pool.emplace_back(subTraverse, head, end);

            // �߳�ͬ����
            for (std::thread& t : pool)
            {
                if (t.joinable())
                    t.join();
            }
        }
    }


    // config�ļ�·���ַ��������� �� std::wstring�ַ�����
    void GetConfigDir(std::wstring& confDir, const TCHAR* pszConfFile);


    // ��ȡconfig�ļ��е�ĳһ������Ϊdouble�ļ�ֵ
    double INIGetFloat(const TCHAR* pszKey, const TCHAR* pszConfFile);


    // ��ȡconfig�ļ��е�ĳһ������Ϊint�ļ�ֵ
    DWORD INIGetInt(const TCHAR* pszKey, const TCHAR* pszConfFile);


    // �������ж�ȡ�����������ݡ�������bool
    template <typename T>
    void readStreamData(T& data, std::istream& is)
    {
        is.read(reinterpret_cast<char*>(&data), sizeof(T));
    }


    // ������������д�뵽����������У�
    template<typename T>
    void writeStreamData(std::ostream& os, const T& data)
    {
        os.write(reinterpret_cast<const char*>(&data), sizeof(T));
    }


    // �õ�ģ�����Ͳ���T��Ӧ��ö������
    template <typename T>
    DATA_TYPE_ENUM getDataType()
    {
        if (std::is_same<T, unsigned char>::value)
            return DATA_TYPE_ENUM::UNSIGNED_CHAR;
        else if (std::is_same<T, char>::value)
            return DATA_TYPE_ENUM::CHAR;
        else if (std::is_same<T, std::uint32_t>::value)
            return DATA_TYPE_ENUM::UINT32;
        else if (std::is_same<T, std::uint64_t>::value)
            return DATA_TYPE_ENUM::UINT64;
        else if (std::is_same<T, std::int32_t>::value)
            return DATA_TYPE_ENUM::INT32;
        else if (std::is_same<T, std::int64_t>::value)
            return DATA_TYPE_ENUM::INT64;
        else if (std::is_same<T, std::float_t>::value)
            return DATA_TYPE_ENUM::FLOAT32;
        else if (std::is_same<T, std::double_t>::value)
            return DATA_TYPE_ENUM::FLOAT64;
        else
            return DATA_TYPE_ENUM::UNSUPPORTED;
    }


    // �������л��� 
    template <typename T>
    bool serializeVector(const std::string& datFilePath, const std::vector<T>& vec)
    {
        std::ofstream fileOut(datFilePath.c_str(), std::ios::binary);
        if (!fileOut.is_open())
            return false;

        // 0. char��ʾ��Ԫ��������Ϣ��
        DATA_TYPE_ENUM dataType = getDataType<T>();
        if (DATA_TYPE_ENUM::UNSUPPORTED == dataType)
            return false;
        writeStreamData(fileOut, static_cast<char>(dataType));

        // 1. uint64_t��ʾ��Ԫ����
        std::uint64_t elemsCount = vec.size();
        writeStreamData(fileOut, elemsCount);

        // 2. ����Ԫ��
        for (const auto& elem : vec)
            writeStreamData(fileOut, elem);

        // 3. �ر��ļ������
        fileOut.close();

        return true;
    }


    // ���鷴���л��� 
    template <typename T>
    bool deserializeVector(std::vector<T>& vec, const std::string& datFilePath)
    {
        std::ifstream file(datFilePath.c_str(), std::ios::binary);
        if (!file.is_open())
            return false;

        // 0. char��ʾ��Ԫ��������Ϣ��
        char type{ -1 };
        DATA_TYPE_ENUM currentType = getDataType<T>();
        readStreamData(type, file);
        if (currentType != static_cast<DATA_TYPE_ENUM>(type))
            return false;

        // 1. uint64_t��ʾ��Ԫ����
        std::uint64_t num0{ 0 };
        size_t elemsCount{ 0 };
        readStreamData(num0, file);
        elemsCount = static_cast<size_t>(num0);

        // 2. ����Ԫ��
        vec.clear();
        vec.resize(elemsCount);
        for (size_t i = 0; i < elemsCount; ++i)
            readStreamData(vec[i], file);

        // 3. �ر��ļ������
        file.close();

        return true;
    }


    // �������������е�������������������ȡԪ��
    /*
        bool subFromIdxCon(
            Container& conOut,
            const Container& conIn,
            const IndexContainer& conIdxes
            )
        ���������������������֧��begin(), end(), operator[]������STL������
        ��������conIdxes�е�Ԫ�ر�������������
    */
    template <typename Container, typename IndexContainer>
    bool subFromIdxCon(Container& conOut, const Container& conIn, const IndexContainer& conIdxes)
    {
        conOut.clear();
        if (conIn.empty() || conIdxes.empty())
            return true;

        const size_t maxIdx = static_cast<size_t>(*std::max_element(conIdxes.begin(), conIdxes.end()));
        const size_t elemsCount = conIn.size();
        const size_t elemsOutCount = conIdxes.size();
        assert((maxIdx < elemsCount) && "Assesrt!!! index out of range in matIn.");

        auto iter = conIdxes.begin();
        conOut.resize(elemsOutCount);
        for (size_t i = 0; iter != conIdxes.end(); ++i)
        {
            const size_t index = static_cast<size_t>(*iter++);
            conOut[i] = conIn[index];
        }

        return true;
    }


    // ����flag�����еĲ���ֵ��������������ȡԪ��
    template <typename Container, typename FlagContainer>
    bool subFromFlagCon(Container& conOut, const Container& conIn, const FlagContainer& flags)
    {
        conOut.clear();
        const size_t elemsCount = conIn.size();

        // 1. ���������
        if (elemsCount != flags.size())
            return false;

        // 2. ��ȡԪ�أ�
        size_t elemsCountNew{ 0 };
        auto iter = conIn.begin();
        auto iterFlag = flags.begin();
        for (const auto& f : flags)
            if (f)
                elemsCountNew++;
        conOut.reserve(elemsCountNew);
        while (iter != conIn.end())
        {
            if (*iterFlag)
                conOut.push_back(*iter);
            iter++;
            iterFlag++;
        }

        return true;
    }


    // flag������Ԫ������Ϊbool��ת��Ϊ������������������Ϊint����
    template <typename IndexContainer, typename FlagContainer>
    bool flagCon2IdxCon(IndexContainer& conIdxes, const FlagContainer& flags)
    {
        conIdxes.clear();

        const size_t elemsCount = flags.size();
        size_t elemsCountNew{ 0 };
        for (const auto& f : flags)
            if (f)
                elemsCountNew++;

        int idxSld{ 0 };
        conIdxes.reserve(elemsCountNew);
        for (const auto& f : flags)
        {
            if (f)
                conIdxes.push_back(idxSld);
            idxSld++;
        }

        return true;
    }


    // ������������������Ϊint��ת��Ϊflag������Ԫ������Ϊbool
    template <typename IndexContainer>
    bool idxCon2FlagVec(std::vector<bool>& flags, const IndexContainer& conIdxes, const size_t elemsCount)
    {
        flags.clear();
        flags.resize(elemsCount, false);
        for (const auto& idx : conIdxes)
            flags[static_cast<size_t>(idx)] = true;

        return true;
    }


    // ��flag�����õ����������ֵ䣻
    template <typename FlagContainer>
    bool getOldNewIdxMap(std::unordered_map<int, int>& old2New, std::unordered_map<int, int>& new2Old, \
        const FlagContainer& flags)
    {
        old2New.clear();
        new2Old.clear();
        const size_t elemsCount = flags.size();
        size_t elemsCountNew{ 0 };
        int newIdx{ 0 };
        int oldIdx{ 0 };
        for (const auto& f : flags)
            if (f)
                elemsCountNew++;
        for (const auto& f : flags)
        {
            if (f)
            {
                old2New.insert(std::make_pair(oldIdx, newIdx));
                new2Old.insert(std::make_pair(newIdx, oldIdx));
                newIdx++;
            }
            else
                old2New.insert(std::make_pair(oldIdx, -1));
            oldIdx++;
        }

        return true;
    }
}
using namespace AUXILIARY;



////////////////////////////////////////////////////////////////////////////////////////////// ���߽ӿڡ����ַ������ļ�ϵͳ���
namespace AUXILIARY_STRING_FILE
{
    void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);


    // �ַ���ת��Ϊ���ַ�����
    std::wstring s2ws(const std::string& s);


    // ���ַ���ת��Ϊ�ַ�����
    std::string ws2s(const std::wstring& ws);


    // ��ָ��Ŀ¼�´����ļ��У�
    bool CreateFolder(const std::string& dirPath);


    // ���·���Ƿ����
    bool CheckValidPath(const std::string& path);


    // ������ȷ���ļ���·��
    std::string CorrectDirPath(const std::string& dirPath);


    // �����ļ�����·��������ļ����ַ���
    std::string ExtractFileName(const std::string& filePath);


    // �����ļ�������·��������ļ������ƣ�������ĩβ��'/'��'\\'����
    std::string ExtractDirName(const std::string& dirPath);


    // �����ļ������ļ�����·��������ļ���׺���ַ���������'.'��
    std::string ExtractNameExt(const std::string& filePath);


    // �����ļ�����·����ĩβ������"/"��"\\"��������������ļ�������·����ĩβû��"/"��"\\"
    std::string ExtractFileDir(const std::string& filePath);


    // ����ͷ����0�������ַ�����
    std::string formatNumWithLeadingZeros(const int number, const size_t width);


    // ���ݹ飩��ȡ����Ŀ¼�µ������ļ�
    void GetFileNames(std::vector<std::string>& files, std::string path, const bool blSenseDir);


    // ��ȡ����Ŀ¼�µ������ļ���
    void GetDirNames(std::vector<std::string>& files, std::string path);


    // �����ļ���
    bool CopyFileViaWinAPI(const std::string& outputPath, const std::string& inputPath);
}
using namespace AUXILIARY_STRING_FILE;



/////////////////////////////////////////////////////////////////////////////////////////////////  by tora: debug�ӿڣ� 
namespace MY_DEBUG
{
    void debugDisp();


    template <typename T, typename... Types>
    void debugDisp(const T& firstArg, const Types&... args)
    {
        std::cout << firstArg << " ";
        debugDisp(args...);
    }

    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& pair)
    {
        os << "(" << pair.first << ", " << pair.second << ")";
        return os;
    }

    void debugDispWStr(const std::wstring& wstr);
     

    // ����std::chrono���Զ����ʱ��
    using namespace std::chrono;
    class tiktok
    {
        // ����constructor��destructor
    private:
        tiktok() = default;
        tiktok(const tiktok&) {}
        ~tiktok() = default;

        // ��Ա���ݣ�
    public:
        time_point<steady_clock> startTik;
        time_point<steady_clock> endTik;
        unsigned recordCount;
        std::vector<time_point<steady_clock>> records;
        double lastDur = 0;                                    // ��һ�ν�����ʱ��¼�µ�ʱ��������λΪ�룻

        // ������
    public:
        static tiktok& getInstance()
        {
            static tiktok tt_instance;
            return tt_instance;
        }

        // ��ʼ��ʱ
        void start()
        {
            this->startTik = steady_clock::now();
            this->recordCount = 0;
            this->records.clear();
        }


        // ������ʱ
        double end()
        {
            this->endTik = steady_clock::now();
            microseconds duration = duration_cast<microseconds>(this->endTik - this->startTik);
            this->lastDur = static_cast<double>(duration.count()) * \
                microseconds::period::num / microseconds::period::den;
            return this->lastDur;
        }


        // ������ʱ������̨�ϴ�ӡʱ��������λΪ��
        double endCout(const char* str)
        {
            end();
            std::cout << str << this->lastDur << " s." << std::endl;
            return this->lastDur;
        }


        // ������ʱ��ʱ����д�뵽fileName���ı��ļ��У���λΪ�룻
        bool endWrite(const char* fileName, const char* str)
        {
            end();
            std::ofstream file(fileName, std::ios_base::out | std::ios_base::app);
            if (!file)
                return false;
            file << str << this->lastDur << std::endl;
            file.close();
            return true;
        }


        // ������ʱ������std::chrono::microseconds���͵�ʱ������
        microseconds endGetCount()
        {
            this->endTik = steady_clock::now();
            microseconds duration = duration_cast<microseconds>(this->endTik - this->startTik);
            this->lastDur = static_cast<double>(duration.count()) * \
                microseconds::period::num / microseconds::period::den;
            return duration;
        }


        // ���������¼�˿̵�ʱ�̣�������this->records�����У�
        void takeArecord()
        {
            this->records.push_back(steady_clock::now());
            recordCount++;
        }
    };
}
using namespace MY_DEBUG;


