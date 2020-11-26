cmake_minimum_required(VERSION 3.0)
project(panda-encode-base2n VERSION 1.0.3 LANGUAGES CXX)
enable_testing()

set(LIB_TYPE STATIC)

file(GLOB_RECURSE libSource RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/panda/*.cc")
add_library(base2n ${LIB_TYPE} ${libSource})
target_include_directories(base2n PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)
set_target_properties(base2n PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

find_package(panda-lib REQUIRED)
target_link_libraries(base2n panda::panda-lib)

add_library(panda::encode::base2n ALIAS base2n)

########################tests#######################################
file(GLOB_RECURSE testSource RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "tests/*.cc")
list(FILTER testSource EXCLUDE REGEX "tests/main.cc")

add_library(tests STATIC EXCLUDE_FROM_ALL ${testSource})
target_link_libraries(tests PUBLIC base2n)

find_package(Catch2)
target_link_libraries(tests PUBLIC Catch2::Catch2)

########################ctests######################################
add_executable(runtests ${testSource} "tests/main.cc")
target_link_libraries(runtests tests)
add_test(test-all runtests)

########################install#####################################
install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(TARGETS base2n EXPORT base2n-targets ARCHIVE DESTINATION lib)

install(EXPORT base2n-targets
    FILE panda-encode-base2n-targets.cmake
    NAMESPACE panda::encode::
    DESTINATION lib/cmake/panda-encode-base2n
)

install(FILES panda-encode-base2n-config.cmake DESTINATION lib/cmake/panda-encode-base2n)
