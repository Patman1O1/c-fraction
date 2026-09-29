from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
import os

class CFraction(ConanFile):
    name = "c_fraction"
    version = "0.1.0"
    author = "Patman1O1"
    description = ""

    settings = ("os", "arch", "compiler", "build_type")
    exports_sources = ("CMakeLists.txt", "cmake/*", "include/*", "src/*", "tests/*")

    options = {
        "build_shared_libs": [True, False],
        "build_tests": [True, False]
    }

    default_options = {
        "build_shared_libs": False,
        "build_tests": False
    }

    def configure(self) -> None:
        if self.settings.build_type == "Debug":
	        self.options.build_tests.value = True

    def build_requirements(self) -> None:
        self.tool_requires("cmake/[>=4.3.0]")
        if bool(self.options.build_tests):
            self.test_requires("gtest/1.17.0")

    def layout(self) -> None: cmake_layout(self)

    def generate(self) -> None:
        toolchain = CMakeToolchain(self)
        toolchain.variables["BUILD_SHARED_LIBS"] = bool(self.options.build_shared_libs)
        toolchain.variables["BUILD_TESTS"] = bool(self.options.build_tests)
        toolchain.generate()
        CMakeDeps(self).generate()

    def build(self) -> None:
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self) -> None: CMake(self).install()

    def package_info(self) -> None:
        self.cpp_info.set_property("cmake_target_name", "fraction::c_fraction")
        self.cpp_info.libs = ["c_fraction"]
        if not bool(self.options.build_shared_libs):
            self.cpp_info.defines = ["C_FRACTION_STATIC_DEFINE"]
