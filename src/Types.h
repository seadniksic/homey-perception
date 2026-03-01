#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

namespace homey {

struct RenderContext {
    std::mutex render_lock;
    std::condition_variable frame_available;
    std::queue<std::function<void()>> render_queue;
};

struct ApplicationContext {
    std::mutex exception_lock;
    std::exception_ptr exception_ptr;
    std::atomic<bool> has_thrown;
};

}

