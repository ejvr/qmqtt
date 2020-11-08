find_package(GTest REQUIRED COMPONENTS gtest gmock CONFIG)

if (GTest_FOUND)
    add_subdirectory(tests)
endif()
