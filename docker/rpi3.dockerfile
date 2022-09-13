FROM balenalib/raspberrypi3-debian:latest

# Install basic building tools
RUN apt-get update && apt-get install -y build-essential cmake

# Install Python, Jupyter and pybind11
COPY docker/env/setup_python.sh /tmp/setup_python.sh
RUN cd /tmp && ./setup_python.sh && rm setup_python.sh

# Install additional Python packages
COPY docker/env/requirements.txt /tmp/requirements.txt
RUN pip3 install -r /tmp/requirements.txt && rm /tmp/requirements.txt
