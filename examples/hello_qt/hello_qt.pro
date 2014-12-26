TEMPLATE = app
TARGET = qt_ui
QT += core \
    gui
HEADERS += ui/qt_ui.h \
    qt_common.h \
    thread/qt_thread_display.h \
    thread/qt_thread_key.h \
    thread/qt_thread_led.h \
    ui/ui_qt_ui.h
SOURCES += qt_common.cpp \
    ui/qt_ui.cpp \
    thread/qt_thread_display.cpp \
    thread/qt_thread_key.cpp \
    thread/qt_thread_led.cpp \
    main.cpp
FORMS += ui/qt_ui.ui
RESOURCES += 
