#include "FrameProvider.h"
#include "VisualizePipeline.h"
#include "Types.h"
#include "RenderLoop.h"

#include <opencv2/opencv.hpp>

#include <condition_variable>
#include <csignal>

bool terminate = false;

int main() {

    std::signal(SIGINT, [](int signal_num) {
        std::cout << "Shutting Down Gracefully"  << std::endl;
        terminate = true;
    });

    try {
        homey::RenderContext render_ctx;
        homey::ApplicationContext app_ctx;

        homey::FrameProvider provider(app_ctx, render_ctx);
        homey::VisualizePipeline viz_pipeline(render_ctx);

        provider.attach(&viz_pipeline);
        provider.start_stream();

        render_loop(app_ctx, render_ctx, terminate);
        return EXIT_SUCCESS;

    } catch (const std::exception &e) {
        std::cout << "Exception thrown: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}