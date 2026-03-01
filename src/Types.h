/**
 * @file    Types.h
 * @brief   Holds assorted useful types for the project (low dependency)
 * @author  Sead Niksic
 */

#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

namespace homey {

/**
 * @brief   Holds assorted useful threadsafe that can be shared with sub threads
 *          providing communication with the main thread.
 */
struct ApplicationContext {
    // general context
    std::condition_variable main_update; // condition variable that main waits on
    std::mutex main_mutex; // lock when you want to update any of the application context
    std::exception_ptr exception_ptr; // way to communicate sub thread exceptions with main thread
    std::atomic<bool> has_thrown; // if a sub thread has thrown

    // render context
    std::queue<std::function<void()>> render_queue; // holds render commands passed by sub threads that
                                                    // want something visualized (must happen in main thread)
};

}

