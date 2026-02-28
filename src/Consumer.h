#pragma once

#include <memory>

namespace homey {

template<typename T>
class Consumer {

    public:
        virtual void update(const T) = 0;
        virtual ~Consumer() = default;
};


}