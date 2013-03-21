TEMPLATE = app
TARGET = QuadGCS
QT += core \
    gui \
    xml \
    xmlpatterns \
    network \
    svg \
    opengl
HEADERS += hud.h \
    fpv.h \
    quadgcs.h
SOURCES += hud.cpp \
    fpv.cpp \
    main.cpp \
    quadgcs.cpp
FORMS += 
#RESOURCES += QuadGCS.qrc
CONFIG += link_pkgconfig
PKGCONFIG += QtGStreamer-0.10 \
    QtGStreamerUi-0.10
