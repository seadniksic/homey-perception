import cv2
import numpy as np
import pyrealsense2 as rs

# Create a context object. This object owns the handles to all connected realsense devices
pipeline = rs.pipeline()

# Configure streams
config = rs.config()
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

# Start streaming
pipeline.start(config)

try:

    while True:
        # This call waits until a new coherent set of frames is available on a device
        # Calls to get_frame_data(...) and get_frame_timestamp(...) on a device will return stable values until wait_for_frames(...) is called
        frames = pipeline.wait_for_frames()
        depth = frames.get_depth_frame()
        color = frames.get_color_frame()

        if not color or not depth:
            continue

        depth_frame = np.asanyarray(depth.get_data())
        color_frame = np.asanyarray(color.get_data())

        depth_colormap = cv2.applyColorMap(cv2.convertScaleAbs(depth_frame, alpha=0.03), cv2.COLORMAP_JET)

        stacked_images = np.hstack((color_frame, depth_colormap))

        cv2.imshow("test", stacked_images)

        cv2.waitKey(1)


except Exception as e:
    print(e)
    pass
finally:
    pipeline.stop()
