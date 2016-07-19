project(GestureEmail)
cmake_minimum_required(VERSION 2.8.8)

#set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(QT5_DIR "" CACHE "")
#option()
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT5_DIR})
#SET(CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\Windows Kits\\8.0\\Lib\\win8\\um\\x64")
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:\\Program Files (x86)\\Microsoft SDKs\\Windows\\v7.0A\\Lib")

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/opt/Qt5.2.0/5.2.0/gcc_64/")

# Widgets finds its own dependencies.
find_package(Qt5Widgets)
find_package(Qt5Network)

#include_directories(${Qt5Widgets_INCLUDES}
#    /opt/Qt5.2.0/5.2.0/gcc_64/include/QtGui
#    /opt/Qt5.2.0/5.2.0/gcc_64/include/QtCore
#    /opt/Qt5.2.0/5.2.0/gcc_64//include/Qt5Widgets
#)
#add_definitions(${Qt5Widgets_DEFINITIONS})
#set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -I/opt/Qt5.2.0/5.2.0/gcc_64/include -L/opt/Qt5.2.0/5.2.0/gcc_64/lib -DQT5")
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/opt/Qt5.2.0/5.2.0/gcc_64/")



#include(${QT_USE_FILE})
set(GestureEmail_SRCS
	main.cpp
    mainwindow.cpp
    mainwindow.h
    logindialog.cpp
    logindialog.h
    recGestureWidget.cpp
    recGestureWidget.h
    OneDollar/GeometricRecognizer.cpp
    OneDollar/GeometricRecognizer.h
    OneDollar/GeometricRecognizerTypes.h
    OneDollar/GestureTemplate.h
    OneDollar/PathWriter.h
    OneDollar/SampleGestures.h
    SmtpClient/SmtpMime
    SmtpClient/emailaddress.cpp
    SmtpClient/emailaddress.h
    SmtpClient/mimeattachment.cpp
    SmtpClient/mimeattachment.h
    SmtpClient/mimecontentformatter.cpp
    SmtpClient/mimecontentformatter.h
    SmtpClient/mimefile.cpp
    SmtpClient/mimefile.h
    SmtpClient/mimehtml.cpp
    SmtpClient/mimehtml.h
    SmtpClient/mimeinlinefile.cpp
    SmtpClient/mimeinlinefile.h
    SmtpClient/mimemessage.cpp
    SmtpClient/mimemessage.h
    SmtpClient/mimemultipart.cpp
    SmtpClient/mimemultipart.h
    SmtpClient/mimepart.cpp
    SmtpClient/mimepart.h
    SmtpClient/mimetext.cpp
    SmtpClient/mimetext.h
    SmtpClient/quotedprintable.cpp
    SmtpClient/quotedprintable.h
    SmtpClient/smtpclient.cpp
    SmtpClient/smtpclient.h
    SmtpClient/smtpexports.h
    Imap/imapaddress.cpp
    Imap/imapaddress.h
    Imap/imap.cpp
    Imap/imap.h
    Imap/imapmailbox.cpp
    Imap/imapmailbox.h
    Imap/imapmessage.cpp
    Imap/imapmessage.h
)
set(GestureEmail_UIS

)
set(GestureEmail_RCCS

)

#qt5_wrap_cpp(22_MOCS ${22_MOC_SRCS})
qt5_wrap_ui(GestureEmail_UIS_SRCS ${GestureEmail_UIS})
qt5_add_resources(GestureEmail_RCC_SRCS ${GestureEmail_RCCS})
add_definitions(-DQT_NO_DEBUG)
add_executable(GestureEmail
    ${GestureEmail_SRCS}
    ${GestureEmail_UIS_SRCS}
    ${GestureEmail_RCC_SRCS})
target_link_libraries(GestureEmail Qt5::Widgets Qt5::Network)
