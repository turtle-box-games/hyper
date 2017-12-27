# - Enable warning all for gcc or use /W4 for visual studio

## Strict warning level
if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
    # Use the highest warning level for visual studio.
    set(CMAKE_CXX_WARNING_LEVEL 4)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")

    set(CMAKE_C_WARNING_LEVEL 4)
    if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    else(CMAKE_C_FLAGS MATCHES "/W[0-4]")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    endif(CMAKE_C_FLAGS MATCHES "/W[0-4]")

elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUC)
    # use -Wall for gcc
    if(NOT CMAKE_CXX_FLAGS MATCHES "-Wall$")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    endif(NOT CMAKE_CXX_FLAGS MATCHES "-Wall$")

    if(NOT CMAKE_C_FLAGS MATCHES "-Wall$")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
    endif(NOT CMAKE_C_FLAGS MATCHES "-Wall$")

else()
    message(STATUS "Unknown build tool, cannot set warning flags for your")
endif()