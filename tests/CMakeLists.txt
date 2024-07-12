cmake_minimum_required(VERSION 3.16)
project(tests LANGUAGES CXX)

# TODO: Re-enable this
# add_subdirectory(about)
add_subdirectory(updater/version)
add_subdirectory(utils)

enable_testing(true)
