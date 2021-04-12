cmake_minimum_required(VERSION 3.9)

project(handycp CXX VERSION 1.0.1)

add_library(${PROJECT_NAME} SHARED
    src/bstree.cpp
    src/tstree.cpp
    src/stats.cpp
    src/linkedlist.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1 PUBLIC_HEADER include/handycp.h)

target_include_directories(${PROJECT_NAME} PRIVATE include)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/mylib.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

configure_file(handycp.pc.in handycp.pc @ONLY)
