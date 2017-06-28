import qbs.base 1.0

Project {
    Application {
        Depends { name: "cpp" }
        Depends {
            name: "Qt"
            submodules: ["core", "network", "test"]
        }
        name: "qmqtt_test"
        cpp.cxxLanguageVersion: "c++11"
        cpp.includePaths: [
            "src/mqtt",
            "tests/gtest/gtest/googletest/googletest/include",
            "tests/gtest/gtest/googletest/googletest",
            "tests/gtest/gtest/googletest/googlemock/include",
            "tests/gtest/gtest/googletest/googlemock",
        ]
        files: [
            "src/mqtt/*.cpp",
            "src/mqtt/*.h",
            "tests/gtest/tests/*.cpp",
            "tests/gtest/tests/*.h",
            "tests/gtest/gtest/googletest/googletest/src/gtest-all.cc",
            "tests/gtest/gtest/googletest/googlemock/src/gmock-all.cc",
        ]
        excludeFiles: "tests/gtest/tests/route*tests.cpp"
    }
}
