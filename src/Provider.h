#pragma once

#include "Consumer.h"

#include <memory>

namespace homey {

template<typename T>
class Provider {

public:

    virtual void attach(Consumer<T>*) = 0;
    virtual void notify(T update_object) = 0;
    virtual ~Provider() = default;

};

}
