cmake_minimum_required(VERSION 3.9)

project(handycp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

# INTERNAL
add_subdirectory(src)
add_subdirectory(test)

#EXTERNAL
add_subdirectory(lib/googletest)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES PUBLIC_HEADER
    VERSION  ${PROJECT_VERSION} 
    SOVERSION 1 
    PUBLIC_HEADER include/handycp.h)

configure_file(handycp.pc.in handycp.pc @ONLY)

install(TARGETS ${PROJECT_NAME} 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${CMAKE_BINARY_DIR}/handycp.pc 
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
