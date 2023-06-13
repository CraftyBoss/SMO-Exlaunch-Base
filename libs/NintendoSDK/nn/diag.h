/**
 * @file diag.h
 * @brief Module, logging, and symbol operations.
 */

#pragma once

#include "result.h"
#include "types.h"

namespace nn {
namespace diag {

// From Darksiders 2 DWARF info
enum LogSeverity
{
    LogSeverity_Trace = 0x0,
    LogSeverity_Info = 0x1,
    LogSeverity_Warn = 0x2,
    LogSeverity_Error = 0x3,
    LogSeverity_Fatal = 0x4,
};
// From Darksiders 2 DWARF info
struct SourceInfo
{
    int lineNumber;
    const unsigned char *fileName;
    const unsigned char *functionName;
};
// From Darksiders 2 DWARF info
struct LogMetaData {
    nn::diag::SourceInfo sourceInfo;
    const unsigned char *moduleName;
    nn::diag::LogSeverity severity;
    int verbosity;
    bool useDefaultLocaleCharset;
    void *pAdditionalData;
    size_t additionalDataBytes;
};

struct ModuleInfo {
    char* mPath;
    u64 mBaseAddr;
    u64 mSize;
};

struct AbortInfo {
    const char *fmt;
    va_list va_args;
};

enum AssertionType {};

namespace detail {
// LOG
void LogImpl(nn::diag::LogMetaData const&, char const*, ...);
void AbortImpl(char const*, char const*, char const*, s32);
void AbortImpl(char const*, char const*, char const*, int, Result);

void OnAssertionFailure(nn::diag::AssertionType,char const*,char const*,char const*,int);
void NotNullImpl(ulong);
void PutImpl(nn::diag::LogMetaData const&,char const*,ulong);

}  // namespace detail

// MODULE / SYMBOL
u64 GetSymbolName(char* name, u64 nameSize, u64 addr);
u64 GetRequiredBufferSizeForGetAllModuleInfo();
s32 GetAllModuleInfo(nn::diag::ModuleInfo** out, void* buffer, u64 bufferSize);
u64 GetSymbolSize(u64 addr);
}  // namespace diag
}  // namespace nn
