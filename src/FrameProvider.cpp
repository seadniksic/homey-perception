#include "FrameProvider.h"

#include <librealsense2/rs.hpp>

#include <iostream>
#include <thread>
#include <chrono>

namespace homey {

    void FrameProvider::attach(Consumer<rs2::video_frame>* consumer) {
        consumers_.push_back(consumer);
    };

    void FrameProvider::notify(rs2::video_frame frame) {

    }

    void FrameProvider::start_stream() {
        provider_ = std::move(std::thread(&FrameProvider::stream, this));
    }

    void FrameProvider::stream() {

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

            // Explicitly configure the streams you need
            std::cout << "Starting Pipeline" << std::endl;
            std::cout << "Pipeline Started" << std::endl;

            while (true) {

                if (shutdown_) {
                    std::cout << "Frame provider thread senses shutdown signal" << std::endl;
                    break;
                }

                rs2::frameset frames = pipe.wait_for_frames(); // 5 second timeout
                rs2::video_frame color_frame = frames.get_color_frame();

                for (const auto& consumer : consumers_) {
                    consumer->update(color_frame);
                }
            }

        } catch (const rs2::error& e) {
            std::cerr << "RealSense error: " << e.what() << std::endl;
            std::cerr << "Function: " << e.get_failed_function() << std::endl;
            std::cerr << "Args: " << e.get_failed_args() << std::endl;
        }
    }

    FrameProvider::~FrameProvider() {
        std::cout << "Destructing frame provider" << std::endl;
        shutdown_ = true;
        provider_.join();
    }
}