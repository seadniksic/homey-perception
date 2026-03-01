/**
 * @file    FrameProvider.h
 * @author  Sead Niksic
 */

#pragma once

#include "Provider.h"
#include "Consumer.h"
#include "Manager.h"
#include "Types.h"

#include <vector>
#include <thread>

// fwd declare rs2 types
namespace rs2 {
class video_frame;
}

namespace homey {

/**
 * @brief Sends realsense frames to attached consumers
 *
 * Responsible for starting and managing its own internal thread
 * that waits for realsense frames and calls update and all attached
 * consumers.
 *
 */
class FrameProvider : Provider<rs2::video_frame>, Manager {

    std::vector<Consumer<rs2::video_frame>*> consumers_;
    std::thread provider_;
    std::atomic<bool> shutdown_;
    ApplicationContext& app_ctx_;

public:
    explicit FrameProvider(ApplicationContext& app_ctx);
    void attach(Consumer<rs2::video_frame>* consumer) override;
    void start_worker() override;
    void worker() override;
    ~FrameProvider() override;
};

}

