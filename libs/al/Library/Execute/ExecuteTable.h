#pragma once

#include "ExecuteOrder.h"

namespace al {
    struct ExecuteTable
    {
        const char* mName = nullptr;
        const al::ExecuteOrder* mExecuteOrders = nullptr;
        int mExecuteOrderCount = 0;
    };
}