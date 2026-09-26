set (TSUNC_SOURCES src/token.cpp)
add_library(libtsunc ${TSUNC_SOURCES})
target_include_directories(libtsunc PUBLIC include/)

set(TSUNC_TOOLS tsunc)
foreach(tool IN LISTS TSUNC_TOOLS)
  add_executable(${tool} tools/${tool}.cpp)
  target_link_libraries(${tool} PUBLIC libtsunc)
endforeach()
