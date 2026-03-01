/**
 * @file    FrameProvider.cpp
 * @author  Sead Niksic
 */

#include "FrameProvider.h"
#include "Types.h"

#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <thread>
#include <random>
#include <exception>

namespace homey {

    FrameProvider::FrameProvider(ApplicationContext& app_ctx) : app_ctx_(app_ctx) {}

    void FrameProvider::attach(Consumer<FrameBundle>* consumer) {
        consumers_.push_back(consumer);
    };

    void FrameProvider::start_worker() {
        provider_ = std::move(std::thread(&FrameProvider::worker, this));
    }

    /**
     * @brief worker thread that pulls frames from realsense and updates consumers
     */
    void FrameProvider::worker() {

        rs2::context ctx;
        auto devices = ctx.query_devices();
        if (devices.size() == 0) {
            std::cerr << "No RealSense devices found!" << std::endl;
        }
        std::cout << "Found " << devices.size() << " device(s)" << std::endl;

        rs2::pipeline pipe;
        rs2::config cfg;

        cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
        cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

        pipe.start(cfg);

        try {

            while (true) {

                if (shutdown_) {
                    std::cout << "Frame provider thread senses shutdown signal" << std::endl;
                    break;
                }

                rs2::frameset frames = pipe.wait_for_frames(); // 5 second timeout
                rs2::video_frame color_frame = frames.get_color_frame();
                rs2::depth_frame depth_frame = frames.get_depth_frame();

                cv::Mat cv_color_frame(
                    cv::Size(color_frame.get_width(), color_frame.get_height()),
                    CV_8UC3,
                    const_cast<void *>(color_frame.get_data()),
                    cv::Mat::AUTO_STEP
                );

                cv::Mat cv_depth_frame(
                    cv::Size(depth_frame.get_width(), depth_frame.get_height()),
                    CV_16UC1,
                    const_cast<void *>(color_frame.get_data())
                );

                FrameBundle frame_bundle;
                frame_bundle.color_frame = cv_color_frame;
                frame_bundle.depth_frame = cv_depth_frame;

                for (const auto& consumer : consumers_) {
                    consumer->update(frame_bundle);
                }
            }

        } catch (const rs2::error& e) {
            std::cerr << "RealSense error: " << e.what() << std::endl;
            std::cerr << "Function: " << e.get_failed_function() << std::endl;
            std::cerr << "Args: " << e.get_failed_args() << std::endl;

            std::unique_lock<std::mutex> lk(app_ctx_.main_mutex);
            app_ctx_.exception_ptr = std::current_exception();
            app_ctx_.has_thrown = true;
            lk.unlock();
            app_ctx_.main_update.notify_one();
        }
    }

    FrameProvider::~FrameProvider() {
        shutdown_ = true;
        provider_.join();
    }
}