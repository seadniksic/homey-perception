/**
 * @file    MLPipeline.h
 * @author  Sead Niksic
 */

#pragma once

#include "Consumer.h"
#include "Manager.h"
#include "Types.h"

#include <thread>

namespace homey {

/**
 * @brief Owns an internal thread for ML processing
 *
 * Responsible for starting and managing its own internal thread
 * that receives frames from the realsense and runs ML processing
 *
 */
class MLPipeline : public Consumer<FrameBundle>, Manager {

    std::thread pipeline_;
    std::atomic<bool> shutdown_;
    ApplicationContext& app_ctx_;

public:
    explicit MLPipeline(ApplicationContext& app_ctx);
    void update(const FrameBundle& frame_bundle) override;
    void start_worker() override;
    void worker() override;
    ~MLPipeline() override;

};

}

