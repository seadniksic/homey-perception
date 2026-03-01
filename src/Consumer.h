/**
 * @file    Consumer.h
 * @author  Sead Niksic
 */

#pragma once


namespace homey {

/**
 * @brief Base class for any entity that is updated with data
 *        by a Provider subclass
 * @tparam Type of data passed from provider
 */
template<typename T>
class Consumer {

    public:
        virtual void update(const T&) = 0;
        virtual ~Consumer() = default;
};


}