/**
 * @file    VisualizePipeline.cpp
 * @author  Sead Niksic
 */

#include "VisualizePipeline.h"

#include <opencv2/opencv.hpp>

#include <mutex>

namespace homey {

VisualizePipeline::VisualizePipeline(ApplicationContext& render_context) : ctx_(render_context) {}

/**
 * @brief Invoked on provider thread and simply passes
 *        frame & render command to render queue
 * @param frame_bundle The bundle of frames from the provider
 */
void VisualizePipeline::update(const FrameBundle& frame_bundle) {

    std::unique_lock<std::mutex> lk(ctx_.main_mutex);
    const cv::Mat& color_frame = frame_bundle.color_frame;
    ctx_.render_queue.emplace([color_frame](){cv::imshow("RGB", color_frame);});
    lk.unlock();
    ctx_.main_update.notify_one();
};

}
