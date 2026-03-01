/**
 * @file    MLPipeline.cpp
 * @author  Sead Niksic
 */

#include "MLPipeline.h"

namespace homey {

MLPipeline::MLPipeline(ApplicationContext& app_ctx)
: app_ctx_(app_ctx) {
   // nn setup
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