#!/usr/bin/env python
# -*- coding: utf-8 -*-

from conans import ConanFile, CMake, tools
import os


class SimpleConan(ConanFile):
    name = "simple"
    version = "0.9"
    url = "https://github.com/IFL-CAMP/simple.git"
    description = "S.I.M.P.L.E. - Smart Intuitive Messaging Platform with Less Effort. A Cross-Platform C++ Library to Exchange Data Across Network."
    license = "https://github.com/IFL-CAMP/simple/blob/master/LICENSE"

    generators = "cmake"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False]}
    default_options = "shared=False"

    requires = "zmq/[>=4.2.3]@camposs/stable", "flatbuffers/[>=1.8.0]@camposs/stable"

    # all sources are deployed with the package
    exports_sources = "examples/*", "include/*", "msgs/*", "tests/*", "CMakeLists.txt", "simpleConfig.cmake", "LICENSE"


    def build(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_SHARED_LIBS"] = self.options.shared
        # cmake.definitions["BUILD_TESTS"] = True
        cmake.definitions["BUILD_EXAMPLES"] = True
        cmake.definitions["FLATBUFFERS_BIN_DIR"] = os.path.join(self.deps_cpp_info["flatbuffers"].rootpath, "bin")
        cmake.configure()
        cmake.build()
        cmake.install()

    def package(self):
        self.copy(pattern="LICENSE")

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
