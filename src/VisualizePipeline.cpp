/**
 * @file    VisualizePipeline.cpp
 * @author  Sead Niksic
 */

#include "VisualizePipeline.h"

#include <librealsense2/hpp/rs_frame.hpp>
#include <opencv2/opencv.hpp>

#include <mutex>

namespace homey {

VisualizePipeline::VisualizePipeline(ApplicationContext& render_context) : ctx_(render_context) {}

/**
 * @brief Invoked on provider thread and simply passes
 *        frame & render command to render queue
 * @param frame The video frame to render
 */
void VisualizePipeline::update(const rs2::video_frame& frame) {

    cv::Mat cv_frame(
        cv::Size(frame.get_width(), frame.get_height()),
        CV_8UC3,
        const_cast<void *>(frame.get_data()),
        cv::Mat::AUTO_STEP
    );

    std::unique_lock<std::mutex> lk(ctx_.main_mutex);
    ctx_.render_queue.emplace([cv_frame](){cv::imshow("RGB", cv_frame);});
    lk.unlock();
    ctx_.main_update.notify_one();
};

}
