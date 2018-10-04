# image

set(IMAGE_LBR "image")
file(GLOB IMAGE_SRC "sources/*.cpp")
set(LIST_TARGETS "${LIST_TARGETS};${IMAGE_LBR}" CACHE STRING "add target" FORCE)

add_library(${IMAGE_LBR} ${IMAGE_SRC})

target_include_directories(${IMAGE_LBR} PUBLIC "include")
