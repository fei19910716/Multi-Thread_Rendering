cmake_minimum_required(VERSION 3.16)
project(Learn-OpenGL)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(QT_LOCAL_PATH  /Users/fordchen/Qt5.13.0/5.13.0) #这里需要填入自己安装的路径
set(CMAKE_PREFIX_PATH ${QT_LOCAL_PATH}/clang_64/lib/cmake)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5QuickControls2 REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5WebEngine REQUIRED)
find_package(Qt5Concurrent REQUIRED)


find_package(Qt5 COMPONENTS Svg REQUIRED)

include_directories(${QT_LOCAL_PATH}/clang_64/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/LightRenderer/third_party/Ace3DEngine/include)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12" CACHE STRING "Minimum OS X deployment version" FORCE)

get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(DEPLOYQT_EXECUTABLE NAMES windeployqt macdeployqt HINTS "${_qt_bin_dir}")



add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIwONS} ${${Qt5Quick_DEFINITIONS}})
#qt5_add_resources(QT_RESOURCES assets/main.qrc)

file(GLOB SOURCE_FILES *.cpp *.h *.hpp *.c)
file(GLOB UTIL_FILES Util/*.cpp Util/*.h Util/*.hpp Util/*.c)
file(GLOB RENDER_FILES Render/*.cpp Render/*.h Render/*.hpp Render/*.c)

add_executable(Learn-OpenGL ${SOURCE_FILES} ${UTIL_FILES} ${RENDER_FILES})
target_link_libraries(Learn-OpenGL Qt5::Widgets Qt5::OpenGL Qt5::Core Qt5::Gui Qt5::Qml  Qt5::Quick Qt5::QuickControls2 Qt5::Multimedia Qt5::WebEngine Qt5::Svg Qt5::Concurrent ${libs})
qt5_use_modules(Learn-OpenGL Core Widgets Gui OpenGL Qml Quick QuickControls2)