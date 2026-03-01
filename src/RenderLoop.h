/**
 * @file    RenderLoop.h
 * @author  Sead Niksic
 */

#pragma once

#include "Types.h"

#include <opencv2/opencv.hpp>

/**
 * @brief Main loop of main thread
 *
 * Runs render commands from sub threads (all rendering must happen on the main
 * thread) to show output windows and handles exceptions & shutdown signals.
 *
 * @param app_ctx Holds all application context (including the render queue)
 *                such that sub threads can safely pass information to the
 *                main thread.
 * @param terminate flag that is set whenever SIGINT (ctrl + c) is invoked
 */
inline void render_loop(homey::ApplicationContext& app_ctx, bool terminate) {

    while (!terminate) {
        std::unique_lock<std::mutex> lk(app_ctx.main_mutex);
        app_ctx.main_update.wait(lk, [&app_ctx] {
            return !app_ctx.render_queue.empty() || app_ctx.has_thrown;
        });

        if (app_ctx.has_thrown) {
            // do graceful shutdown
            std::cout << "rethrowing exception" << std::endl;
            std::rethrow_exception(app_ctx.exception_ptr);
        }

        auto render_command = app_ctx.render_queue.front();
        render_command();

        app_ctx.render_queue.pop();

        // Wait for a key press indefinitely
        cv::waitKey(1);
    }

    // Destroy all the created windows
    cv::destroyAllWindows();

}
