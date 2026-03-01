/**
 * @file    VisualizePipeline.h
 * @author  Sead Niksic
 */

#pragma once

#include "Consumer.h"
#include "Types.h"

// fwd declare
namespace rs2 {
    class video_frame;
}

namespace homey {

/**
 * @brief Consumes frames from FrameProvider and passes them to
 *        render queue for main thread to visualize
 */
class VisualizePipeline : public Consumer<rs2::video_frame> {

    ApplicationContext& ctx_;

public:

    explicit VisualizePipeline(ApplicationContext& render_context);
    void update(const rs2::video_frame& frame) override;

};

}
