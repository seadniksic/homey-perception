#pragma once

#include "Consumer.h"

#include <librealsense2/rs.hpp>

namespace homey {

class VisualizePipeline : public Consumer<rs2::video_frame> {

public:

    VisualizePipeline() = default;
    void update(const rs2::video_frame frame) override {};

};

}
