cmake_minimum_required(VERSION 3.17)
project(bthreads C)

set(CMAKE_C_STANDARD 99)

add_executable(bthreads main.c source/bthread.c source/bthread.h source/bthread_private.h source/tqueue.c source/tqueue.h)

