cmake_minimum_required( VERSION 2.8.8 )

project( dUpload )

set( CMAKE_AUTOMOC TRUE )
set( CMAKE_INCLUDE_CURRENT_DIR TRUE )

find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Multimedia REQUIRED )
find_package( Qt5MultimediaWidgets REQUIRED )
find_package( Qt5Network REQUIRED )
find_package( Qt5OpenGL REQUIRED )
find_package( Qt5WebKit REQUIRED )
find_package( Qt5Widgets REQUIRED )

file( GLOB dUpload_INCLUDES "src/*.h" )
file( GLOB dUpload_SOURCES "src/*.cpp" )
file( GLOB dUpload_UI "ui/*.ui" )

QT5_ADD_RESOURCES( dUpload_RESOURCES "resources/dUpload.qrc" )
QT5_WRAP_UI( dUpload_UI_SOURCES ${dUpload_UI} )

if( WIN32 )
	add_definitions( -DQT_DLL -DQ_WS_WIN )
	list( APPEND dUpload_RESOURCES "resources/dUpload.rc" )
#	set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/" )
endif( WIN32 )

add_executable( dUpload WIN32 MACOSX_BUNDLE ${dUpload_INCLUDES} ${dUpload_SOURCES} ${dUpload_UI_SOURCES} ${dUpload_RESOURCES} )

qt5_use_modules( dUpload Core Gui Multimedia MultimediaWidgets Network WebKit Widgets )

if( WIN32 )
	target_link_libraries( dUpload ${Qt5Core_QTMAIN_LIBRARIES} )
endif( WIN32 )

if( APPLE )
	#SET( MACOSX_BUNDLE_ICON_FILE Speedcrunch.icns )
	#SET( MACOSX_BUNDLE_SHORT_VERSION_STRING 0.7-beta2 )
	#SET( MACOSX_BUNDLE_VERSION 0.7-beta2 )
	#SET( MACOSX_BUNDLE_LONG_VERSION_STRING Version 0.7-beta2 )
	#SET( CMAKE_OSX_ARCHITECTURES ppc;i386 ) #Comment out if not universal binary

	set_target_properties( dUpload PROPERTIES MACOSX_BUNDLE_INFO_PLIST "resources/Info.plist" )
endif( APPLE )
