# тести для рефакторингу Gilded Rose 
find_package(GTest CONFIG QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

set(TEST_NAME GildedRoseRefactoringTests)
add_executable(${TEST_NAME}
    GildedRoseRequirementsTests.cc
    GildedRoseLegacyComparisonTests.cc
    FragileGoodsTests.cc
    LegacyGildedRose.h)
target_link_libraries(${TEST_NAME} PRIVATE GildedRoseLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
