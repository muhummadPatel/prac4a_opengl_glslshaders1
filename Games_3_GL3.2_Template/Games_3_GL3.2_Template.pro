HEADERS       = glheaders.h \
                glwidget.h \ 
    stlModel.h \
    objModel.h

SOURCES       = glwidget.cpp \
                main.cpp \
    stlModel.cpp \
    objModel.cpp
QT += core gui opengl widgets

#for mac
LIBS += -lGLEW -L/usr/local/lib

#for Linux
#LIBS += -lGLEW

RESOURCES += resources.qrc
#QMAKE_CXXFLAGS += -DSHOULD_LOAD_SHADERS
CONFIG += -std=c++11
# install
target.path = boom
INSTALLS += target

DISTFILES +=
