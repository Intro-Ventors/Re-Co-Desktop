QT +=                                                       \
    core                                                    \
    gui                                                     \

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG +=                                                   \
    c++2a                                                   \
    file_copies

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000            # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=                                                  \
    Source/Main.cpp                                         \
    Source/GUI/MainWindow.cpp                               \
    Source/GUI/SplashScreen.cpp                             \
    Source/GUI/About.cpp                                    \
    Source/GUI/Login.cpp                                    \
    Source/GUI/ScreenWidget.cpp                             \
    Source/GUI/Authentication.cpp                           \
    Source/GUI/ApplicationGUI.cpp                           \
                                                            \
    Source/Scipper/Instance.cpp                             \
    Source/Scipper/RScreenCapture.cpp                       \
    Source/Scipper/Window.cpp                               \
    Source/Scipper/Monitor.cpp                              \
    Source/Scipper/FrameCapture.cpp                         \
                                                            \
    Source/WebRTC/Connection.cpp                            \
    Source/WebRTC/Reactor.cpp                               \
                                                            \
    ThirdParty/lodepng/lodepng.cpp                          \
    ThirdParty/QR-Code-generator/cpp/qrcodegen.cpp

HEADERS +=                                                  \
    Source/GUI/MainWindow.hpp                               \
    Source/GUI/SplashScreen.hpp                             \
    Source/GUI/About.hpp                                    \
    Source/GUI/Login.hpp                                    \
    Source/GUI/ScreenWidget.hpp                             \
    Source/GUI/Authentication.hpp                           \
    Source/GUI/ApplicationGUI.hpp                           \
                                                            \
    Source/WebRTC/Connection.hpp                            \
    Source/WebRTC/Reactor.hpp                               \
    Source/WebRTC/Stream.hpp                                \
                                                            \
    Source/Scipper/Instance.hpp                             \
    Source/Scipper/RScreenCapture.hpp                       \
    Source/Scipper/Window.hpp                               \
    Source/Scipper/Monitor.hpp                              \
    Source/Scipper/FrameCapture.hpp

FORMS +=                                                    \
    Source/GUI/Forms/MainWindow.ui                          \
    Source/GUI/Forms/About.ui                               \
    Source/GUI/Forms/Login.ui                               \
    Source/GUI/Forms/Screen.ui                              \
    Source/GUI/Forms/Authentication.ui                              

RESOURCES +=                                                \
    Assets.qrc

INCLUDEPATH +=                                              \
    ThirdParty/screen_capture_lite/include                  \
    ThirdParty/lodepng                                      \
    ThirdParty/libdatachannel/include                       \
    ThirdParty/QR-Code-generator/cpp

RC_ICONS = "Assets/2D/Re-Co Logo.ico"

LIBS +=                                                     \
    -L"ThirdParty/libdatachannel/build"                     \
    -ldatachannel

win32:debug {
    LIBS +=                                                 \ 
        -L"ThirdParty/screen_capture_lite/src_cpp/Debug"    \
        -lscreen_capture_lite_shared

    COPIES += ScreenCaptureLiteSharedDebug
    ScreenCaptureLiteSharedDebug.files = $$files(ThirdParty/screen_capture_lite/Debug/screen_capture_lite_shared.dll)
    ScreenCaptureLiteSharedDebug.path = $$PWD/debug

    COPIES += libdatachannelSharedDebug
    libdatachannelSharedDebug.files = $$files(ThirdParty/libdatachannel/build/datachannel.dll)
    libdatachannelSharedDebug.path = $$PWD/debug
}

win32:release {
    LIBS +=                                                 \
        -L"ThirdParty/screen_capture_lite/src_cpp/Release"  \
        -lscreen_capture_lite_shared

    COPIES += ScreenCaptureLiteSharedRelease
    ScreenCaptureLiteSharedRelease.files = $$files(ThirdParty/screen_capture_lite/Release/screen_capture_lite_shared.dll)
    ScreenCaptureLiteSharedRelease.path = $$PWD/release

    COPIES += libdatachannelSharedRelease
    libdatachannelSharedRelease.files = $$files(ThirdParty/libdatachannel/build/datachannel.dll)
    libdatachannelSharedRelease.path = $$PWD/release
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
