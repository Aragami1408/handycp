cmake_minimum_required(VERSION 3.9)

project(handycp)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

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
