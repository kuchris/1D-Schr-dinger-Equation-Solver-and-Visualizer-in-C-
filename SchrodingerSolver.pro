QT += widgets charts
TEMPLATE = app
TARGET = SchrodingerSolver
INCLUDEPATH += ./eigen-3.4.0 \
               ./fftw-3.3.5
LIBS += c:/Users/kuchris/Desktop/test/fftw-3.3.5/libfftw3-3.lib
QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
LIBS += MSVCRT.lib
SOURCES += main.cpp \
    mainwindow.cpp \
    schrodingersolver.cpp \
    CustomChartView.cpp
HEADERS += mainwindow.h \
    schrodingersolver.h \
    CustomChartView.h
FORMS += mainwindow.ui
