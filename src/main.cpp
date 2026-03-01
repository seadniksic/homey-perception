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

    homey::RenderContext ctx;

    homey::FrameProvider provider;
    homey::VisualizePipeline viz_pipeline(ctx);

    provider.attach(&viz_pipeline);
    provider.start_stream();

    render_loop(ctx, terminate);

    return EXIT_SUCCESS;
}