#pragma once

#include "Consumer.h"
#include "Types.h"

#include <librealsense2/rs.hpp>

#include <queue>

namespace homey {

class VisualizePipeline : public Consumer<rs2::video_frame> {

    RenderContext& ctx_;


public:

    explicit VisualizePipeline(RenderContext& render_context);
    void update(rs2::video_frame frame) override;

};

}
