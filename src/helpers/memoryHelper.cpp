#include "memoryHelper.h"

namespace MemoryHelper {
    template <class T>
    void logMemory(T* ptr) {
        int size = sizeof(T);
        auto all = (unsigned char*)ptr;

        for (int i = 0; i < size; i++) {
            Logger::log("%02X", all[i]);
        }
        Logger::log("\n");
    }

    void logMemory(void* ptr, size_t size) {
        auto all = (unsigned char*)ptr;
        for (int i = 0; i < size; i++) {
            Logger::log("%02X", all[i]);
        }
        Logger::log("\n");
    }
}
