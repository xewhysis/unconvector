cmake_minimum_required(VERSION 3.16)

project(unconvector VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ТОЛЬКО файлы, которые лежат в папке unconvector
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(unconvector
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        # Все файлы классов - ТОЛЬКО локальные
        ${CMAKE_CURRENT_SOURCE_DIR}/BigInteger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/BigInteger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BigFraction.h
        ${CMAKE_CURRENT_SOURCE_DIR}/BigFraction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Parser.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Formatter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Formatter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseConverter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseConverter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ResultWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ResultWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test.h
    )
else()
    if(ANDROID)
        add_library(unconvector SHARED
            ${PROJECT_SOURCES}
            ${CMAKE_CURRENT_SOURCE_DIR}/BigInteger.h
            ${CMAKE_CURRENT_SOURCE_DIR}/BigInteger.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/BigFraction.h
            ${CMAKE_CURRENT_SOURCE_DIR}/BigFraction.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Parser.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Formatter.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Formatter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/BaseConverter.h
            ${CMAKE_CURRENT_SOURCE_DIR}/BaseConverter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ResultWindow.h
            ${CMAKE_CURRENT_SOURCE_DIR}/ResultWindow.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/test.h
        )
    else()
        add_executable(unconvector
            ${PROJECT_SOURCES}
            ${CMAKE_CURRENT_SOURCE_DIR}/BigInteger.h
            ${CMAKE_CURRENT_SOURCE_DIR}/BigInteger.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/BigFraction.h
            ${CMAKE_CURRENT_SOURCE_DIR}/BigFraction.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Parser.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Formatter.h
            ${CMAKE_CURRENT_SOURCE_DIR}/Formatter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/BaseConverter.h
            ${CMAKE_CURRENT_SOURCE_DIR}/BaseConverter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ResultWindow.h
            ${CMAKE_CURRENT_SOURCE_DIR}/ResultWindow.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/test.h
        )
    endif()
endif()

target_link_libraries(unconvector PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.unconvector)
endif()

set_target_properties(unconvector PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS unconvector
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(unconvector)
endif()
