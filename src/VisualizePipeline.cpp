#include "VisualizePipeline.h"

#include <opencv2/opencv.hpp>

#include <iostream>
#include <mutex>

namespace homey {

VisualizePipeline::VisualizePipeline(RenderContext& render_context) : ctx_(render_context) {}

void VisualizePipeline::update(rs2::video_frame frame) {

    cv::Mat cv_frame(
        cv::Size(frame.get_width(), frame.get_height()),
        CV_8UC3,
        const_cast<void *>(frame.get_data()),
        cv::Mat::AUTO_STEP
    );

    std::unique_lock<std::mutex> lk(ctx_.render_lock);
    ctx_.render_queue.emplace([cv_frame](){cv::imshow("RGB", cv_frame);});
    lk.unlock();
    ctx_.frame_available.notify_one();
};

}
