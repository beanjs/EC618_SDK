#! /bin/bash

export ROOT=`pwd`
export GCC_PATH=/home/wangjun/Desktop/beanjs/beanio-firmware/cache/gcc-arm-none-eabi-8-2018-q4-major
export PROJECT_NAME=example_gpio
export LSPD_MODE=disable

xmake clean
xmake
