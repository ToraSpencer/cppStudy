# CppStudy 编译脚本使用说明

## 概述

`build.bat` 是 CppStudy 解决方案的一键编译脚本，基于 MSBuild 编译 `CppStudy.sln`，支持自定义编译配置和目标平台。

## 前置条件

- **Visual Studio 2022** 已安装，且包含 C++ 桌面开发工作负载
- 脚本默认 MSBuild 路径为 VS2022 Community 版：

  ```
  C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe
  ```

- 如果使用 Professional 或 Enterprise 版，需修改脚本中 `MSBUILD` 变量的路径：

  | 版本        | 路径                                                         |
  | ----------- | ------------------------------------------------------------ |
  | Community   | `C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe` |
  | Professional | `C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe` |
  | Enterprise  | `C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe` |

## 用法

```cmd
build.bat [配置] [平台]
```

### 参数

| 参数   | 说明                          | 可选值                      | 默认值  |
| ------ | ----------------------------- | --------------------------- | ------- |
| 配置   | 编译配置类型                  | `Debug`, `Release`          | `Debug` |
| 平台   | 目标平台架构                  | `x64`, `x86`, `ARM`, `ARM64` | `x64`   |

### 示例

```cmd
:: 默认编译 (Debug|x64)
build.bat

:: 编译 Release 版本 (x64)
build.bat Release

:: 编译 Debug 版本，目标 x86
build.bat Debug x86

:: 编译 Release 版本，目标 ARM64
build.bat Release ARM64
```

## 编译项目列表

脚本编译 `CppStudy.sln` 中包含的所有项目：

| 项目                 | 说明             |
| -------------------- | ---------------- |
| CppStudy             | 主项目           |
| basicTools           | 基础工具         |
| chap_basicTypes      | 基础类型章节     |
| chap_syntax          | 语法章节         |
| chap_function        | 函数章节         |
| chap_stdlib          | 标准库章节       |
| chap_STL             | STL 章节         |
| chap_errorHandling   | 错误处理章节     |
| chap_designPattern   | 设计模式章节     |
| chap_DSA             | 数据结构与算法   |
| cppTest              | C++ 测试项目     |
| DSAtest              | DSA 测试项目     |
| BinTree              | 二叉树（邓俊辉） |
| graphMatrix          | 图矩阵（邓俊辉） |

## 编译输出

编译产物按平台和配置存放在对应目录下：

```
CppStudy/
├── x64/
│   ├── Debug/      ← Debug|x64 输出
│   └── Release/    ← Release|x64 输出
├── Win32/
│   ├── Debug/      ← Debug|x86 输出
│   └── Release/    ← Release|x86 输出
└── ARM/
    ├── Debug/      ← Debug|ARM 输出
    └── Release/    ← Release|ARM 输出
```

## MSBuild 参数说明

脚本调用 MSBuild 时使用了以下参数：

| 参数                   | 说明                                 |
| ---------------------- | ------------------------------------ |
| `/p:Configuration=...` | 指定编译配置 (Debug/Release)         |
| `/p:Platform=...`      | 指定目标平台 (x64/x86/ARM/ARM64)     |
| `/m`                   | 启用多核并行编译，加快编译速度       |
| `/v:minimal`           | 最小化输出，仅显示警告和错误         |
| `/nologo`              | 不显示 MSBuild 启动版权信息          |

## 常见问题

### 提示 MSBuild not found

- 确认已安装 Visual Studio 2022 及 C++ 桌面开发工作负载
- 确认 MSBuild 路径与安装版本一致（Community/Professional/Enterprise）
- 也可使用 **Developer Command Prompt for VS 2022** 直接运行 `msbuild CppStudy.sln`

### 编译失败

- 查看错误输出，常见原因包括缺少依赖项或源文件语法错误
- 如需详细编译日志，可将脚本中 `/v:minimal` 改为 `/v:detailed` 或 `/v:diag`

### 想清理编译产物

在脚本所在目录执行：

```cmd
:: 使用 MSBuild 清理
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" CppStudy.sln /t:Clean /p:Configuration=Debug /p:Platform=x64

:: 或直接删除输出目录
rmdir /s /q x64\Debug
```
