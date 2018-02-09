set(SRC_FILES
        _.cpp)

add_library(hyper ${SRC_FILES})
install(TARGETS hyper DESTINATION .)