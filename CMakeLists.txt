cmake_minimum_required(VERSION 3.11)
project(drobne VERSION 0.0.1 LANGUAGES CXX)

###########
# Testing #
###########
# include(CTest)
# enable_testing()

###########
# Project #
###########
set(MAIN_SRC 
${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/main.cpp 
${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/program.cpp
)
set(DISPLAY_SRC 
${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/display/console.cpp
)
set(DB_SRC
${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/database/sqlite.cpp
)

add_executable(${PROJECT_NAME} 
${MAIN_SRC}
${DISPLAY_SRC}
${DB_SRC}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
########################
# TODO: add clang-tidy #
########################

##########
# SQLite #
##########
find_package(SQLite3)
target_link_libraries(${PROJECT_NAME} PRIVATE SQLite::SQLite3)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)