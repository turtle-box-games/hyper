include(DisableExceptionsRtti)

set(SRC_FILES
        Error.cpp)

# Disable standard library.
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUC
        OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")
endif()

add_library(hyper ${SRC_FILES})
install(TARGETS hyper DESTINATION .)