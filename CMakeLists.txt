cmake_minimum_required(VERSION 3.16)

project(CalculatorQt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CalculatorQt
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(CalculatorQt SHARED
                ${PROJECT_SOURCES}
        )
    else()
        add_executable(CalculatorQt
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CalculatorQt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CalculatorQt)
endif()
set_target_properties(CalculatorQt PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CalculatorQt
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CalculatorQt)
endif()

# Deployment steps
if(WIN32)
    add_custom_command(TARGET CalculatorQt POST_BUILD
            COMMAND ${Qt6_DIR}/bin/windeployqt $<TARGET_FILE:CalculatorQt>
            COMMENT "Running windeployqt to bundle Qt libraries"
    )
elseif(UNIX AND NOT APPLE)
    add_custom_command(TARGET CalculatorQt POST_BUILD
            COMMAND linuxdeployqt $<TARGET_FILE:CalculatorQt> -appimage
            COMMENT "Running linuxdeployqt to bundle Qt libraries"
    )
endif()