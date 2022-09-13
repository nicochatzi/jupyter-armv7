FROM balenalib/raspberrypi3-debian:latest

# Install basic building tools
RUN apt-get update && apt-get install -y build-essential cmake

# Install Python, Jupyter and pybind11
COPY docker/env/setup_python_base.sh /tmp/setup_python_base.sh
RUN cd /tmp && ./setup_python_base.sh && rm setup_python_base.sh

# Additional packages required for python
# this could serve as the entry point for user-added packages
COPY docker/env/setup_python_ext.sh /tmp/setup_python_ext.sh
RUN cd /tmp && ./setup_python_ext.sh && rm setup_python_ext.sh

# Install additional Python packages
COPY docker/env/requirements.txt /tmp/requirements.txt
RUN pip3 install -r /tmp/requirements.txt && rm /tmp/requirements.txt
