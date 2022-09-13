FROM arm64v8/ubuntu:latest

RUN apt-get update && apt-get install -y build-essential cmake

COPY docker/scripts/setup_juce.sh /tmp/setup_juce.sh
RUN /tmp/./setup_juce.sh && rm /tmp/setup_juce.sh

COPY docker/env/setup_python.sh /tmp/setup_python.sh
RUN cd /tmp && ./setup_python.sh && rm setup_python.sh

COPY docker/env/requirements.txt /tmp/requirements.txt
RUN pip3 install -r /tmp/requirements.txt && rm /tmp/requirements.txt
