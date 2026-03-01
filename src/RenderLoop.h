#pragma once

#include "Types.h"

#include <opencv2/opencv.hpp>

inline void render_loop(homey::RenderContext& ctx, bool terminate) {

    while (!terminate) {
        std::unique_lock<std::mutex> lk(ctx.render_lock);
        ctx.frame_available.wait(lk, [&ctx] {
            return !ctx.render_queue.empty();
        });

        auto render_command = ctx.render_queue.front();
        render_command();

        ctx.render_queue.pop();

        // Wait for a key press indefinitely
        cv::waitKey(1);
    }

    // Destroy all the created windows
    cv::destroyAllWindows();

}
