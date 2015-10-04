cmake_minimum_required( VERSION 2.8.11 )

project( dUpload )

set( CMAKE_AUTOMOC TRUE )
set( CMAKE_INCLUDE_CURRENT_DIR TRUE )

find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Multimedia REQUIRED )
find_package( Qt5MultimediaWidgets REQUIRED )
find_package( Qt5Network REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5WinExtras REQUIRED )

file( GLOB dUpload_INCLUDES "src/*.h" )
file( GLOB dUpload_SOURCES "src/*.cpp" )
file( GLOB dUpload_UI "ui/*.ui" )

QT5_ADD_RESOURCES( dUpload_RESOURCES "resources/dUpload.qrc" )
QT5_WRAP_UI( dUpload_UI_SOURCES ${dUpload_UI} )

if( WIN32 )
	add_definitions( -DQT_DLL -DQ_WS_WIN )
    add_definitions( -DUNICODE -D_UNICODE )
	list( APPEND dUpload_RESOURCES "resources/dUpload.rc" )
#	set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/" )
endif( WIN32 )

add_executable( dUpload WIN32 MACOSX_BUNDLE ${dUpload_INCLUDES} ${dUpload_SOURCES} ${dUpload_UI_SOURCES} ${dUpload_RESOURCES} )

target_link_libraries( dUpload Qt5::Core Qt5::Gui Qt5::Multimedia Qt5::MultimediaWidgets Qt5::Network Qt5::Widgets Qt5::WinExtras )

if( APPLE )
	#SET( MACOSX_BUNDLE_ICON_FILE Speedcrunch.icns )
	#SET( MACOSX_BUNDLE_SHORT_VERSION_STRING 0.7-beta2 )
	#SET( MACOSX_BUNDLE_VERSION 0.7-beta2 )
	#SET( MACOSX_BUNDLE_LONG_VERSION_STRING Version 0.7-beta2 )
	#SET( CMAKE_OSX_ARCHITECTURES ppc;i386 ) #Comment out if not universal binary

	set_target_properties( dUpload PROPERTIES MACOSX_BUNDLE_INFO_PLIST "resources/Info.plist" )
endif( APPLE )
