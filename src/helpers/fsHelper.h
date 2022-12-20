#pragma once

#include "nn/fs.h"
#include "result.h"

namespace FsHelper {
    nn::Result writeFileToPath(void *buf, size_t size, const char *path);
    long getFileSize(const char* path);
    bool isFileExist(const char* path);
};
