cmake_minimum_required(VERSION 3.12)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(matrix VERSION 0.0.1)
endif()

configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


target_sources(${PROJECT_NAME}
PRIVATE
    src/main.cpp
    src/version.h
)


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

if(UNIX)
    set(CPACK_GENERATOR DEB)
    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
    set(CPACK_PACKAGE_CONTACT teletajp@yandex.ru)
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)
endif()