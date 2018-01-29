set(SRC_FILES
        Backtrace.cpp
        StackTraceSnapshot.cpp)

add_library(hyper ${SRC_FILES})
install(TARGETS hyper DESTINATION .)