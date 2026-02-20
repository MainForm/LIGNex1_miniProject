#include "MutexGuard.hpp"

namespace AppCommon {

    MutexGuard::MutexGuard(osMutexId_t mutex, uint32_t timeout)
        : _mutex(mutex), locked(false)
    {
        locked = ( osMutexAcquire(_mutex, timeout) == osOK);
    }

    MutexGuard::~MutexGuard()
    {
        if (locked){
            osMutexRelease(_mutex);
        }
    }

    bool MutexGuard::isLocked() const { 
        return locked; 
    }

    MutexGuard::operator bool() const{
        return isLocked();
    }
    
    void MutexGuard::unlock(){
        if (locked)
        {
            osMutexRelease(_mutex);
            locked = false;
        }
    }
}