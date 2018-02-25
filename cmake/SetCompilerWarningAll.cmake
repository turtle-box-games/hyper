# - Enable all warnings for gcc/clang or use /W4 for visual studio

## Strict warning level
if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
    # Use the highest warning level for visual studio.
    set(CMAKE_CXX_WARNING_LEVEL 4)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()

    set(CMAKE_C_WARNING_LEVEL 4)
    if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    endif()

elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUC
        OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # use -Wall for gcc/clang.
    if(NOT CMAKE_CXX_FLAGS MATCHES "-Wall")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    endif()

    if(NOT CMAKE_C_FLAGS MATCHES "-Wall")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
    endif()

else()
    message(STATUS "Unknown compiler, cannot set warning flags")
endif()