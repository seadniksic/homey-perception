# add_library(homey-lib)

add_executable(homey-perception
        main.cpp
        FrameProvider.cpp
        FrameProvider.h
        Provider.h
        Consumer.h
        VisualizePipeline.cpp
        VisualizePipeline.h
        Types.h
        RenderLoop.h
)

target_link_libraries(homey-perception PRIVATE
        ${OpenCV_LIBS}
        realsense2 )