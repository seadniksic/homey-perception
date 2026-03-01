## homey-perception

--- 

Perception software for the small home robot assistant I'm building. Also functions
as a standalone system with limited software dependencies and a single hardware dependency (Intel Realsense Camera).

It streams frames from a realsense camera and performs standard (ImageNet) object detection, displaying the result.

**High Level Project Goals:**
- [x]  Consume and visualize realsense frames via flexible / modular pubsub architecture
- [ ]  Run Object Detection in C++ (libtorch) using custom quantized models
- [ ]  Use depth frames to construct 3D map of surrounding environment
- [ ]  Add ML semantic information into map
- [ ]  Compute and store embeddings / locations of map items in local vector DB
- [ ]  Provide interface to query map with natural language

### Installation
First install required dependencies. This guide will assume you're installing on Debian/Ubuntu Linux. 

**Intel Realsense SDK**

Register public key
```
# Ensure the directory exists
sudo mkdir -p /etc/apt/keyrings

# Download and dearmor
curl -sSf https://librealsense.realsenseai.com/Debian/librealsenseai.asc | \
gpg --dearmor | sudo tee /etc/apt/keyrings/librealsenseai.gpg > /dev/null
```
Make sure apt HTTPS support is installed: `sudo apt-get install apt-transport-https`

Add the server to the list of repositories:
```
echo "deb [signed-by=/etc/apt/keyrings/librealsenseai.gpg] https://librealsense.realsenseai.com/Debian/apt-repo `lsb_release -cs` main" | \
sudo tee /etc/apt/sources.list.d/librealsense.list
sudo apt-get update
```

Install required packages
```
sudo apt-get install librealsense2-dkms librealsense2-utils librealsense2-dev librealsense2-dbg libfastcdr-dev libfastrtps-dev libopencv-dev
```

### Building and running the project

Clone, configure, and build

```
git clone git@github.com:seadniksic/homey-perception.git
cd homey-perception && mkdir build && cd build
cmake .. && cmake --build .
./homey-perception
```
