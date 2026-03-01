/**
 * @file    Manager.h
 * @author  Sead Niksic
 */

#pragma once

namespace homey {

/**
 * @brief Specifies an interface for a class that manages a thread
 *        that does work
 */
class Manager {

public:
    virtual void start_worker() = 0;
    virtual void worker() = 0;
    virtual ~Manager() = default;

};

}