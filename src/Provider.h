/**
 * @file    Provider.h
 * @author  Sead Niksic
 */

#pragma once

#include "Consumer.h"

namespace homey {

/**
 * @brief Base class for any entity that updates Consumers with
 *        data.
 * @tparam Type of data to pass to consumer
 */
template<typename T>
class Provider {

public:

    virtual void attach(Consumer<T>*) = 0;
    virtual ~Provider() = default;

};

}
