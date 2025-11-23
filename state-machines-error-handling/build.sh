#!/bin/bash

docker build -t weather_station .

docker run --rm -it \
    -v "$(pwd)":/app \
    weather_station \
    bash -c "mkdir -p build && \
    cd build && \
    cmake \
    -DTARGET_HOST=ON \
    -DLOG_MIN_SEVERITY_DISPLAY=LOG_DEBUG \
    -DLOG_MIN_SEVERITY_FLASH=LOG_ERROR \
    .. && \
    make -j && \
    ./weather_station"
