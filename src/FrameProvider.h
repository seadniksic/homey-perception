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
namespace homey {

/**
 * @brief Sends realsense frames to attached consumers
 *
 * Responsible for starting and managing its own internal thread
 * that waits for realsense frames and calls update and all attached
 * consumers.
 *
 */
class FrameProvider : Provider<FrameBundle>, Manager {

    std::vector<Consumer<FrameBundle>*> consumers_;
    std::thread provider_;
    std::atomic<bool> shutdown_;
    ApplicationContext& app_ctx_;

public:
    explicit FrameProvider(ApplicationContext& app_ctx);
    void attach(Consumer<FrameBundle>* consumer) override;
    void start_worker() override;
    void worker() override;
    ~FrameProvider() override;
};

}

