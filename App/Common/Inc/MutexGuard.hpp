#ifdef __cplusplus
#ifndef __APP_COMMON_MUTEX_GUARD_H__
#define __APP_COMMON_MUTEX_GUARD_H__

#include "cmsis_os.h"

namespace AppCommon {
    class MutexGuard {
    private:
        osMutexId_t _mutex;
        bool locked;
    public:
        MutexGuard(osMutexId_t mutex, uint32_t timeout = osWaitForever);

        ~MutexGuard();

        bool isLocked() const;

        void unlock();

        operator bool() const;
    };
}


#endif // __APP_COMMON_MUTEX_GUARD_H__
#endif // __cplusplus