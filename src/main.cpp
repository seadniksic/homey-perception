/**
 * @file    main.cpp
 * @brief   Entry point for homey perception system
 * @author  Sead Niksic
 */

#include "FrameProvider.h"
#include "VisualizePipeline.h"
#include "MLPipeline.h"
#include "Types.h"
#include "RenderLoop.h"

#include <opencv2/opencv.hpp>

#include <csignal>

bool terminate = false;

int main() {

    // register single handler (ctrl + c) for graceful shutdown
    std::signal(SIGINT, [](int signal_num) {
        std::cout << "Shutting Down Gracefully"  << std::endl;
        terminate = true;
    });

    try {
        homey::ApplicationContext app_ctx;

        homey::FrameProvider provider(app_ctx);
        homey::VisualizePipeline viz_pipeline(app_ctx);
        homey::MLPipeline ml_pipeline(app_ctx);

        provider.attach(&viz_pipeline);
        provider.start_worker();

        render_loop(app_ctx, terminate);
        return EXIT_SUCCESS;

    } catch (const std::exception &e) {
        std::cout << "Exception thrown: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}