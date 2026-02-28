#include "FrameProvider.h"

#include <iostream>
#include <thread>
#include <chrono>


rs2::context ctx;
auto devices = ctx.query_devices();
if (devices.size() == 0) {
    std::cerr << "No RealSense devices found!" << std::endl;
    return EXIT_FAILURE;
}
std::cout << "Found " << devices.size() << " device(s)" << std::endl;

try {
    rs2::pipeline pipe;
    rs2::config cfg;

    // Explicitly configure the streams you need
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

    std::cout << "Starting Pipeline" << std::endl;
    pipe.start(cfg);
    std::cout << "Pipeline Started" << std::endl;

    while (true) {

        // std::cout << "Waiting for frame" << std::endl;
        rs2::frameset frames = pipe.wait_for_frames(); // 5 second timeout
        // std::cout << "received frame" << std::endl;

        rs2::depth_frame depth = frames.get_depth_frame();
        rs2::video_frame color = frames.get_color_frame();

        if (!depth || !color) {
            std::cerr << "Missing frame" << std::endl;
            continue;
        }

        int w = depth.get_width(), h = depth.get_height();
        float dist = depth.get_distance(w/2, h/2);
        // std::cout << "The camera is facing an object " << dist << " meters away\r" << std::endl;
    }
} catch (const rs2::error& e) {
    std::cerr << "RealSense error: " << e.what() << std::endl;
    std::cerr << "Function: " << e.get_failed_function() << std::endl;
    std::cerr << "Args: " << e.get_failed_args() << std::endl;
    return EXIT_FAILURE;
}
