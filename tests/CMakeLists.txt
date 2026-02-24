# Download Catch2
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# add_executable(test_<something> <something>.cpp)
# target_link_libraries(test_<something> PRIVATE homey-lib Catch2::Catch2WithMain)

include(CTest)
include(Catch)

# catch_discover_tests(<test_something>)
