cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
 project(12_homework VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
 project(12_homework VERSION 0.0.3)
endif()

find_package(Threads)
find_package(Boost COMPONENTS system REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

add_executable(bulk_server main.cpp server.cpp session.cpp event_processor.cpp commands.h commands.cpp consumer.h consumer_out.h consumer_out.cpp consumer_file.h consumer_file.cpp producer.h producer.cpp)

set_target_properties( bulk_server  PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

target_include_directories(bulk_server PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(bulk_server ${CMAKE_THREAD_LIBS_INIT}  ${Boost_LIBRARIES})

target_compile_options(bulk_server PRIVATE -Wall -Wextra -pedantic -Werror )

install(TARGETS bulk_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ddzuba@yandex.ru)
include(CPack)

