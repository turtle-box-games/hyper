# - Disable all exceptions and RTTI for C++

if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs- /EHc- /GR-")

elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUC
        OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")

else()
    message(STATUS "Unknown compiler, cannot set exception and RTTI flags")
endif()