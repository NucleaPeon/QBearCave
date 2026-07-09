cmake_minimum_required(VERSION 3.3)

if (APPLE)
    set(CMAKE_C_COMPILER /usr/bin/clang CACHE PATH "CMake C Compiler")
    set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "CMake C++ Compiler")
endif()

project(QBearCave
    VERSION 0.0.0.0
    LANGUAGES C CXX
    DESCRIPTION "Qt-based Precious Metals Organization Application"
)

include(GNUInstallDirs)
include(CTest)
set(QT_DEFAULT_MAJOR_VERSION "5" CACHE STRING "Qt Version defaults to 5 (OS X 10.6 default)")


# Immediately set the version.h header
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h @ONLY)


find_package(Qt${QT_DEFAULT_MAJOR_VERSION} NAMES Qt5 Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
    Network
    Concurrent
    Test
)

find_package(qt5menugen CONFIG REQUIRED 4.0)

if(${QT_DEFAULT_MAJOR_VERSION} STREQUAL "6")
    find_package(Qt6 REQUIRED COMPONENTS
        Core5Compat
    )
endif()

### QT CONFIGURATION ###

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

list(APPEND APP_SOURCES
    mainwindow/mainwindow.cpp
    mainwindow/about.cpp
    mainwindow/preferences.cpp

    main.cpp
)

list(APPEND APP_HEADERS
    mainwindow/mainwindow.h
    mainwindow/about.h
    mainwindow/preferences.h
)

list(APPEND APP_UIS
    mainwindow/mainwindow.ui
    mainwindow/about.ui
    mainwindow/preferences.ui
)

list(APPEND APP_RES
    #mainwindow/mainwindow.qrc
)

list(APPEND APP_OTHER

)


if (APPLE)
    set(MACOSX_BUNDLE_ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/QBearCave.icns )
    set( "${MACOSX_BUNDLE_ICON_FILE}")
    list(APPEND APP_OTHER ${MACOSX_BUNDLE_ICON_FILE})
    list(APPEND APP_SOURCES cocoainitializer.mm)
    list(APPEND APP_HEADERS cocoainitializer.h)
    add_custom_target(OTHER_FILES SOURCES ${APP_OTHER})
    set_property(SOURCE ${MACOSX_BUNDLE_ICON_FILE} PROPERTY MACOSX_PACKAGE_LOCATION
            ${MACOSX_BUNDLE_ICON_FILE})
    file(COPY ${MACOSX_BUNDLE_ICON_FILE} DESTINATION
             ${CMAKE_CURRENT_BINARY_DIR})
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE
            ${OTHER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
            ${APP_HEADERS}
            ${APP_SOURCES}
            ${APP_UIS}
            ${APP_UI_HEADERS}
            ${APP_RES}
    )
    target_sources(${PROJECT_NAME} PRIVATE
            ${APP_OTHER}
    )
    set_source_files_properties(
            ${APP_OTHER}
            PROPERTIES
            MACOSX_PACKAGE_LOCATION Resources/
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
            BUNDLE TRUE
            MACOSX_BUNDLE_GUI_IDENTIFIER org.peondevelopments.qbearcave
            MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
             "-Wl,-F/Library/Frameworks")
    target_link_libraries(${PROJECT_NAME} stdc++
            "-framework Cocoa"
            objc
    )

else()
    add_executable(${PROJECT_NAME}
            ${APP_OTHER}
            main.cpp
            ${APP_HEADERS}
            ${APP_SOURCES}
            ${APP_UIS}
            ${APP_UI_HEADERS}
            ${APP_RES}
            ${CMAKE_CURRENT_SOURCE_DIR}/../QBearCave.png
        )
endif()

add_definitions(-DDB_SQLITE3=YES)
add_definitions(-DDB_MYSQL=NO)
add_definitions(-DDB_MARIADB=NO)
add_definitions(-DDB_POSTGRESQL=NO)


target_link_libraries(${PROJECT_NAME}
    Qt${QT_DEFAULT_MAJOR_VERSION}::Core
    Qt${QT_DEFAULT_MAJOR_VERSION}::Widgets
    Qt${QT_DEFAULT_MAJOR_VERSION}::Network
    Qt${QT_DEFAULT_MAJOR_VERSION}::Gui
    Qt${QT_DEFAULT_MAJOR_VERSION}::Concurrent
    Qt${QT_DEFAULT_MAJOR_VERSION}::Test
)
target_link_libraries(${PROJECT_NAME} qt5menugen)

if(${QT_DEFAULT_MAJOR_VERSION} STREQUAL "6")
    target_link_libraries(${PROJECT_NAME}
        Qt6::Core5Compat
    )
endif()

target_include_directories(${PROJECT_NAME} BEFORE PRIVATE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_autogen/include/)
target_include_directories(${PROJECT_NAME} BEFORE PRIVATE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_autogen/include/${PROJECT_BINARY_DIR}/${PROJECT_NAME}_autogen/include/)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})

if(APPLE)
        find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED COMPONENTS MacExtras)
        target_link_libraries(${PROJECT_NAME}
            Qt${QT_DEFAULT_MAJOR_VERSION}::MacExtras
        )
elseif(MSVC)
        # NOT TESTED
        find_package(Qt${QT_DEFAULT_MAJOR_VERSION} HINTS "$ENV{QT5_DIR}" REQUIRED COMPONENTS
            Core
            Quick
        )
        # These will have to change FIXME
        set(CMAKE_PREFIX_PATH "C:\\Qt\\5.3.1\\5.3\\msvc2013_opengl")
        set(Qt5_DIR "C:/Qt/Qt5.3.2/5.3/msvc2013_64_opengl/")
        find_package(Qt${QT_DEFAULT_MAJOR_VERSION} COMPONENTS WinExtras REQUIRED)
        target_link_libraries(${PROJECT_NAME} Qt${QT_DEFAULT_MAJOR_VERSION}::WinExtras)
endif()
