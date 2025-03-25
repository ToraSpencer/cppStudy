#pragma once 
// 自己写的辅助接口，只涉及C++基本类型；

#include <iostream>
#include <fstream>
#include <sstream>			// 字符串流
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
#include <limits>				// 提供std::numeric_limits<>模板

#include <cmath>
#include <random>
#include <ctime>
#include <typeinfo>
#include <type_traits>

#include <memory> 
#include <thread>					// c++线程支持库
#include <mutex>
#include <atomic>			// 原子类型 
#include <cassert>			// 断言

// MFC
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif 
#include <windows.h> 
#include <atlstr.h>				// 包含CString类。属于microsoft ATL(活动模板库avtive template library)
#include <io.h>
#endif  
   
#include <omp.h>			// openMP


// #define USE_BOOST
#ifdef  USE_BOOST
#include <boost/tuple/tuple.hpp>
#endif  
 

// 内存和CPU监视接口需要的一些头文件；
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


////////////////////////////////////////////////////////////////////////////////////////////// 工具接口
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


    // 函数子——打印std::cout支持的类型变量。
    template <typename	T>
    class disp
    {
    public:
        void operator()(const T& arg)
        {
            std::cout << arg << ", ";
        }
    };


    // 函数子——打印std::pair
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


    // 传入函数子或函数指针遍历stl容器
    template<typename T, typename F>
    void traverseSTL(T& con, F f, const std::string& headStr = std::string{})
    {
        if (!headStr.empty())
            std::cout << headStr << std::endl;
        std::for_each(con.begin(), con.end(), f);
        std::cout << std::endl;
    }


    // 传入函数子或函数指针遍历std::map, std::unordered_map等
    template<typename mapType, typename F>
    void traverseSTLmap(mapType& m, F f)
    {
        std::for_each(m.begin(), m.end(), f);
        std::cout << std::endl;
    }


    // 反向遍历
    template<typename T, typename F>
    void revTraverseSTL(T& con, F f)
    {
        std::for_each(con.rbegin(), con.rend(), f);
        std::cout << std::endl;
    } 
     

    // 并行for循环——传入函数子原型为：void(const size_t index)
    template<typename Func>
    void PARALLEL_FOR(size_t beg, size_t end, \
        const Func& func, const size_t serial_if_less_than = 12)
    {
        /*
            PARALLEL_FOR(
                size_t   beg,                                     起始元素索引
                size_t  end,                                      尾元素索引
                const size_t  serial_if_less_than,      如果需要处理的元素不小于该值，则使用并行化；
                const Func & func										操作元素的函数子；
                )
        */
        size_t elemCount = end - beg + 1;

        if (elemCount < serial_if_less_than)
            for (size_t i = beg; i < end; ++i)
                func(i);
        else
        {
            // 确定起的线程数；
            const static unsigned n_threads_hint = std::thread::hardware_concurrency();
            const static unsigned n_threads = (n_threads_hint == 0u) ? 8u : n_threads_hint;

            // for循环的范围分解成几段；
            size_t slice = (size_t)std::round(elemCount / static_cast<double>(n_threads));
            if (slice < 1u)
                slice = 1u;

            // 线程函数：
            auto subTraverse = [&func](size_t head, size_t tail)
                {
                    for (size_t k = head; k < tail; ++k)
                        func(k);
                };

            // 生成线程池，执行并发for循环；
            std::vector<std::thread> pool;              // 线程池；
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

            // 线程同步；
            for (std::thread& t : pool)
            {
                if (t.joinable())
                    t.join();
            }
        }
    }


    // 变参并行for循环——索引以外的参数使用std::tuple传入；
    template<typename Func, typename paramTuple>
    void PARALLEL_FOR(size_t beg, size_t end, const Func& func, \
        const paramTuple& pt, const size_t serial_if_less_than = 12)
    {
        /*
            PARALLEL_FOR(
                size_t   beg,                                     起始元素索引
                size_t  end,                                      尾元素索引
                const size_t  serial_if_less_than,      如果需要处理的元素不小于该值，则使用并行化；
                const paramTuple& pt								索引以外的其他参数；
                const Func & func										操作元素的函数子；
                )
        */
        size_t elemCount = end - beg + 1;

        if (elemCount < serial_if_less_than)
            for (size_t i = beg; i < end; ++i)
                func(i, pt);
        else
        {
            // 确定起的线程数；
            const static unsigned n_threads_hint = std::thread::hardware_concurrency();
            const static unsigned n_threads = (n_threads_hint == 0u) ? 8u : n_threads_hint;

            // for循环的范围分解成几段；
            size_t slice = (size_t)std::round(elemCount / static_cast<double>(n_threads));
            if (slice < 1u)
                slice = 1u;

            // 线程函数：
            auto subTraverse = [&func, &pt](size_t head, size_t tail)
                {
                    for (size_t k = head; k < tail; ++k)
                        func(k, pt);
                };

            // 生成线程池，执行并发for循环；
            std::vector<std::thread> pool;              // 线程池；
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

            // 线程同步；
            for (std::thread& t : pool)
            {
                if (t.joinable())
                    t.join();
            }
        }
    }


    // config文件路径字符串字面量 → std::wstring字符串；
    void GetConfigDir(std::wstring& confDir, const TCHAR* pszConfFile);


    // 读取config文件中的某一个类型为double的键值
    double INIGetFloat(const TCHAR* pszKey, const TCHAR* pszConfFile);


    // 读取config文件中的某一个类型为int的键值
    DWORD INIGetInt(const TCHAR* pszKey, const TCHAR* pszConfFile);


    // 输入流中读取基本类型数据——除了bool
    template <typename T>
    void readStreamData(T& data, std::istream& is)
    {
        is.read(reinterpret_cast<char*>(&data), sizeof(T));
    }


    // 基本类型数据写入到输出流对象中；
    template<typename T>
    void writeStreamData(std::ostream& os, const T& data)
    {
        os.write(reinterpret_cast<const char*>(&data), sizeof(T));
    }


    // 得到模板类型参数T对应的枚举量；
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


    // 数组序列化： 
    template <typename T>
    bool serializeVector(const std::string& datFilePath, const std::vector<T>& vec)
    {
        std::ofstream fileOut(datFilePath.c_str(), std::ios::binary);
        if (!fileOut.is_open())
            return false;

        // 0. char表示的元素类型信息；
        DATA_TYPE_ENUM dataType = getDataType<T>();
        if (DATA_TYPE_ENUM::UNSUPPORTED == dataType)
            return false;
        writeStreamData(fileOut, static_cast<char>(dataType));

        // 1. uint64_t表示的元素数
        std::uint64_t elemsCount = vec.size();
        writeStreamData(fileOut, elemsCount);

        // 2. 具体元素
        for (const auto& elem : vec)
            writeStreamData(fileOut, elem);

        // 3. 关闭文件句柄；
        fileOut.close();

        return true;
    }


    // 数组反序列化： 
    template <typename T>
    bool deserializeVector(std::vector<T>& vec, const std::string& datFilePath)
    {
        std::ifstream file(datFilePath.c_str(), std::ios::binary);
        if (!file.is_open())
            return false;

        // 0. char表示的元素类型信息；
        char type{ -1 };
        DATA_TYPE_ENUM currentType = getDataType<T>();
        readStreamData(type, file);
        if (currentType != static_cast<DATA_TYPE_ENUM>(type))
            return false;

        // 1. uint64_t表示的元素数
        std::uint64_t num0{ 0 };
        size_t elemsCount{ 0 };
        readStreamData(num0, file);
        elemsCount = static_cast<size_t>(num0);

        // 2. 具体元素
        vec.clear();
        vec.resize(elemsCount);
        for (size_t i = 0; i < elemsCount; ++i)
            readStreamData(vec[i], file);

        // 3. 关闭文件句柄；
        file.close();

        return true;
    }


    // 按照索引容器中的索引从输入容器中提取元素
    /*
        bool subFromIdxCon(
            Container& conOut,
            const Container& conIn,
            const IndexContainer& conIdxes
            )
        输入的所有容器都必须是支持begin(), end(), operator[]方法的STL容器；
        索引容器conIdxes中的元素必须是整型数；
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


    // 按照flag容器中的布尔值从输入容器中提取元素
    template <typename Container, typename FlagContainer>
    bool subFromFlagCon(Container& conOut, const Container& conIn, const FlagContainer& flags)
    {
        conOut.clear();
        const size_t elemsCount = conIn.size();

        // 1. 输入错误处理；
        if (elemsCount != flags.size())
            return false;

        // 2. 提取元素：
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


    // flag容器（元素类型为bool）转换为索引容器（索引类型为int）；
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


    // 索引容器（索引类型为int）转换为flag容器（元素类型为bool
    template <typename IndexContainer>
    bool idxCon2FlagVec(std::vector<bool>& flags, const IndexContainer& conIdxes, const size_t elemsCount)
    {
        flags.clear();
        flags.resize(elemsCount, false);
        for (const auto& idx : conIdxes)
            flags[static_cast<size_t>(idx)] = true;

        return true;
    }


    // 由flag容器得到新老索引字典；
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



////////////////////////////////////////////////////////////////////////////////////////////// 工具接口——字符串、文件系统相关
namespace AUXILIARY_STRING_FILE
{
    void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);


    // 字符串转换为宽字符串；
    std::wstring s2ws(const std::string& s);


    // 宽字符串转换为字符串；
    std::string ws2s(const std::wstring& ws);


    // 在指定目录下创建文件夹：
    bool CreateFolder(const std::string& dirPath);


    // 检测路径是否存在
    bool CheckValidPath(const std::string& path);


    // 返回正确的文件夹路径
    std::string CorrectDirPath(const std::string& dirPath);


    // 输入文件完整路径，输出文件名字符串
    std::string ExtractFileName(const std::string& filePath);


    // 输入文件夹完整路径，输出文件夹名称（不包括末尾的'/'或'\\'）：
    std::string ExtractDirName(const std::string& dirPath);


    // 输入文件名或文件完整路径，输出文件后缀名字符串（包括'.'）
    std::string ExtractNameExt(const std::string& filePath);


    // 输入文件完整路径（末尾不能是"/"或"\\"），输出其所在文件夹完整路径，末尾没有"/"或"\\"
    std::string ExtractFileDir(const std::string& filePath);


    // 生成头部补0的数字字符串：
    std::string formatNumWithLeadingZeros(const int number, const size_t width);


    // （递归）读取输入目录下的所有文件
    void GetFileNames(std::vector<std::string>& files, std::string path, const bool blSenseDir);


    // 读取输入目录下的所有文件夹
    void GetDirNames(std::vector<std::string>& files, std::string path);


    // 复制文件：
    bool CopyFileViaWinAPI(const std::string& outputPath, const std::string& inputPath);
}
using namespace AUXILIARY_STRING_FILE;



/////////////////////////////////////////////////////////////////////////////////////////////////  by tora: debug接口： 
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
     

    // 基于std::chrono的自定义计时器
    using namespace std::chrono;
    class tiktok
    {
        // 禁用constructor和destructor
    private:
        tiktok() = default;
        tiktok(const tiktok&) {}
        ~tiktok() = default;

        // 成员数据：
    public:
        time_point<steady_clock> startTik;
        time_point<steady_clock> endTik;
        unsigned recordCount;
        std::vector<time_point<steady_clock>> records;
        double lastDur = 0;                                    // 上一次结束计时记录下的时间间隔，单位为秒；

        // 方法：
    public:
        static tiktok& getInstance()
        {
            static tiktok tt_instance;
            return tt_instance;
        }

        // 开始计时
        void start()
        {
            this->startTik = steady_clock::now();
            this->recordCount = 0;
            this->records.clear();
        }


        // 结束计时
        double end()
        {
            this->endTik = steady_clock::now();
            microseconds duration = duration_cast<microseconds>(this->endTik - this->startTik);
            this->lastDur = static_cast<double>(duration.count()) * \
                microseconds::period::num / microseconds::period::den;
            return this->lastDur;
        }


        // 结束计时，控制台上打印时间间隔，单位为秒
        double endCout(const char* str)
        {
            end();
            std::cout << str << this->lastDur << " s." << std::endl;
            return this->lastDur;
        }


        // 结束计时，时间间隔写入到fileName的文本文件中，单位为秒；
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


        // 结束计时，返回std::chrono::microseconds类型的时间间隔；
        microseconds endGetCount()
        {
            this->endTik = steady_clock::now();
            microseconds duration = duration_cast<microseconds>(this->endTik - this->startTik);
            this->lastDur = static_cast<double>(duration.count()) * \
                microseconds::period::num / microseconds::period::den;
            return duration;
        }


        // 按下秒表，记录此刻的时刻，保存在this->records向量中；
        void takeArecord()
        {
            this->records.push_back(steady_clock::now());
            recordCount++;
        }
    };
}
using namespace MY_DEBUG;


