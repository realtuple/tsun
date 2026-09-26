cmake_minimum_required(VERSION 4.4.3)
project(tsun
  VERSION 0.1.0
  SPDX_LICENSE MIT
  DESCRIPTION "Tsun programming language"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Doxygen)
option(TSUN_ENABLE_DOCS "Enable documentation for Tsun Project" ${Doxygen_FOUND})

if(NOT Doxygen_FOUND AND TSUN_ENABLE_DOCS)
  message(CRITICAL_ERROR "Documentation enabled but doxygen not enabled")
endif()

function(tsun_add_subproject subproject_name)
  string(TOUPPER subproject_name subproject_name_up)
  option(TSUN_ENABLE_${subproject_name_up} "Enable ${subproject_name} subproject" ON)
  if(TSUN_ENABLE_${subproject_name_up}) 
    add_subdirectory(${subproject_name}/)
  endif()
endfunction()

tsun_add_subproject(tsunc)

if(TSUN_ENABLE_DOCS)
  add_subdirectory(docs/)
endif()
