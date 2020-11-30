cmake_minimum_required(VERSION 3.2)

project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/version.h.in 
	${CMAKE_CURRENT_SOURCE_DIR}/include/version.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(helloworld_cli ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_library(helloworld ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.cpp)
add_executable(test_main ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_version.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/tests/test_hello.cpp)

set_target_properties(helloworld_cli helloworld test_main PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_main PROPERTIES
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(helloworld_cli PRIVATE
     helloworld
)
target_include_directories(test_main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(test_main
    ${Boost_LIBRARIES}
    helloworld
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
	    /W4
    )
    target_compile_options(helloworld PRIVATE
            /W4
    )
    target_compile_options(test_main PRIVATE
            /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_main PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif()
															install(TARGETS helloworld_cli RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT boris.testov@gmail.com)
include(CPack)
enable_testing()
add_test(test_main test_main)
