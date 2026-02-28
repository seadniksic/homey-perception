#include "FrameProvider.h"
#include "VisualizePipeline.h"

#include <opencv2/opencv.hpp>

#include <queue>
#include <condition_variable>
#include <csignal>

std::mutex render_lock;
std::condition_variable frame_available;
std::queue<std::function<void()>> render_queue;
bool terminate = false;

int main() {

    std::signal(SIGINT, [](int signal_num) {
        std::cout << "Shutting Down Gracefully"  << std::endl;
        terminate = true;
    });

    homey::FrameProvider provider;
    homey::VisualizePipeline viz_pipeline;

    provider.attach(&viz_pipeline);
    provider.start_stream();

    while (!terminate) {

        std::unique_lock<std::mutex> lk(render_lock);
        frame_available.wait(lk, [] {
            return !render_queue.empty();
        });

        auto render_command = render_queue.front();
        render_command();
        render_queue.pop();

        // Wait for a key press indefinitely
        cv::waitKey(1);

        // Destroy all the created windows
        cv::destroyAllWindows();

    }

    std::cout << "Exiting main scope" << std::endl;

    return EXIT_SUCCESS;
}