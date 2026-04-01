cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(LeadG)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

file(GLOB MACRO_FILES "macros/*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${CMAKE_BINARY_DIR}/)

file(GLOB DATA_FILES "data/*.dat")
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_BINARY_DIR}/)

add_executable(leadG leadG.cc ${sources})
target_link_libraries(leadG ${Geant4_LIBRARIES})

add_custom_target(LeadG DEPENDS leadG)
