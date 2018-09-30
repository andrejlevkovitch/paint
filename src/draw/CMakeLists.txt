# draw

set(DRAW_LBR "draw")
file(GLOB DRAW_SRC "sources/*.cpp")
set(LIST_TARGETS "${LIST_TARGETS};${DRAW_LBR}" CACHE STRING "add target" FORCE)

add_library(${DRAW_LBR} ${DRAW_SRC})
target_include_directories(${DRAW_LBR} PUBLIC "include")
