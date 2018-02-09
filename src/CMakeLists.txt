set(SRC_FILES
        StackTrace.cpp)

add_library(hyper ${SRC_FILES})
install(TARGETS hyper DESTINATION .)