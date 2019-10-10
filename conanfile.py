#!/usr/bin/env python
# -*- coding: utf-8 -*-

from conans import ConanFile, CMake, tools
import os


class SimpleConan(ConanFile):
    name = "simple"
    version = "1.1.0"
    url = "https://github.com/IFL-CAMP/simple.git"
    description = "S.I.M.P.L.E. - Smart Intuitive Messaging Platform with Less Effort. A Cross-Platform C++ Library to Exchange Data Across Network."
    license = "https://github.com/IFL-CAMP/simple/blob/master/LICENSE"

    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "with_opencv": [True, False],
        }
    default_options = (
        "shared=False",
        "with_opencv=False",
        )

    requires = ("zmq/[>=4.3.2]@camposs/stable",
               "cppzmq/4.4.1@camposs/stable",
               "flatbuffers/[>=1.11.0]@camposs/stable",
               )

    # all sources are deployed with the package
    exports_sources = "examples/*", "include/*", "msgs/*", "src/*", "tests/*", "CMakeLists.txt", "simpleConfig.cmake", "LICENSE"

    def requirements(self):
        if self.options.with_opencv:
            self.requires("opencv/[>=4.1.0]@camposs/stable")

    def configure(self):
        if self.options.shared:
            self.options['flatbuffers'].shared = True
            self.options['zmq'].shared = True
            if self.options.with_opencv:
                self.options['opencv'].shared = True

    def cmake_configure(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_SHARED_LIBS"] = self.options.shared
        # cmake.definitions["BUILD_TESTS"] = True
        cmake.definitions["BUILD_EXAMPLES"] = 'ON'
        cmake.definitions["BUILD_EXAMPLES"] = 'ON'
        cmake.definitions["SIMPLE_BUILD_OPENCV_EXAMPLES"] = 'ON' if self.options.with_opencv else 'OFF'
        cmake.definitions["FLATBUFFERS_BIN_DIR"] = os.path.join(self.deps_cpp_info["flatbuffers"].rootpath, "bin")
        cmake.configure()
        return cmake

    def build(self):
        cmake = self.cmake_configure()
        cmake.build()

    def package(self):
        cmake = self.cmake_configure()
        cmake.install()
        self.copy(pattern="LICENSE")

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
