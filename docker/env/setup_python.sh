#!/bin/bash

apt-get install -y \
    libzmq3-dev \
    python3 \
    python3-venv \
    python3-dev \
    python3-pip

pip3 install --upgrade --force-reinstall --no-cache-dir jupyter
pip3 install "pybind11[global]"
pip3 install pytest

# numpy dependencies
pip3 install opencv-contrib-python
apt-get install -y \
    libatlas-base-dev \
    libhdf5-dev \
    libhdf5-serial-dev \
    libatlas-base-dev \
    libjasper-dev \
    libqtgui4  \
    libqt4-test