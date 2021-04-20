cmake_minimum_required(VERSION 3.9)

project(handycp 
    VERSION 1.0.1 
    DESCRIPTION "Some pretty handy stuff for Competitive Programming" 
    LANGUAGES CXX
)

include(GNUInstallDirs)

add_library(${PROJECT_NAME} SHARED
    src/bstree.cpp
    src/stats.cpp
    src/linkedlist.cpp
    src/sorts.cpp
    src/search.cpp
)


set_target_properties(${PROJECT_NAME} 
    PROPERTIES VERSION 
    ${PROJECT_VERSION} 
    SOVERSION 1 
    PUBLIC_HEADER 
    include/handycp.h
)

configure_file(handycp.pc.in handycp.pc @ONLY)

target_include_directories(${PROJECT_NAME} PRIVATE include)

install(TARGETS ${PROJECT_NAME} 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/mylib.pc 
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
