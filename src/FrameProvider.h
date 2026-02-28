#pragma once

#include "Provider.h"
#include "Consumer.h"

#include <vector>
#include <thread>

// fwd declare frameset
namespace rs2 {
class video_frame;
}

namespace homey {
    class FrameProvider : Provider<rs2::video_frame> {

        std::vector<Consumer<rs2::video_frame>*> consumers_;
        std::thread provider_;
        std::atomic<bool> shutdown_;

    public:
        FrameProvider() = default;
        void attach(Consumer<rs2::video_frame>* consumer) override;
        void notify(rs2::video_frame frame) override;
        void start_stream();
        void stream();
        ~FrameProvider();
    };
}

