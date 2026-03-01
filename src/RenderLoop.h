#pragma once

#include "Types.h"

#include <opencv2/opencv.hpp>

inline void render_loop(homey::ApplicationContext& app_ctx, homey::RenderContext& render_ctx, bool terminate) {

    while (!terminate) {
        std::unique_lock<std::mutex> lk(render_ctx.render_lock);
        render_ctx.frame_available.wait(lk, [&render_ctx, &app_ctx] {
            return !render_ctx.render_queue.empty() || app_ctx.has_thrown;
        });

        if (app_ctx.has_thrown) {
            // do graceful shutdown
            std::cout << "rethrowing exception" << std::endl;
            std::rethrow_exception(app_ctx.exception_ptr);
        }

        auto render_command = render_ctx.render_queue.front();
        render_command();

        render_ctx.render_queue.pop();

        // Wait for a key press indefinitely
        cv::waitKey(1);
    }

    // Destroy all the created windows
    cv::destroyAllWindows();

}
