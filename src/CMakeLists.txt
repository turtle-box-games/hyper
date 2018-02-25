include(DisableExceptionsRtti)

set(SRC_FILES
        Error.cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUC
        OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Disable standard library.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")
    # Enable effective C++ linting.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++")
endif()

add_library(hyper ${SRC_FILES})
install(TARGETS hyper DESTINATION .)