/**
 * @file    MLPipeline.cpp
 * @author  Sead Niksic
 */

#include "MLPipeline.h"

#include <torch/script.h>
#include <torch/torch.h>

namespace homey {

MLPipeline::MLPipeline(ApplicationContext& app_ctx)
: app_ctx_(app_ctx) {
   // nn setup
   // torch::jit::script::Module module = torch::jit::load("");
   // assert(module != nullptr);
}

MLPipeline::~MLPipeline() {
   // notify pipeline to shut down
   shutdown_ = true;
   pipeline_.join();
}

void MLPipeline::update(const FrameBundle& frame_bundle) {
   // do update shit

}

void MLPipeline::start_worker() {

   // do update shit

}

void MLPipeline::worker() {
   // do update shit




}


}