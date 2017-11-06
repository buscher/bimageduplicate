SOURCES += main.cpp \
bfolderscanner.cpp \
bdeletedialog.cpp
HEADERS += bfolderscanner.h \
bdeletedialog.h
FORMS += bdeletedialog.ui

TEMPLATE = app

TARGET = bimageduplicate

DESTDIR = ../bin

OBJECTS_DIR = .lib

MOC_DIR = .moc

QT += widgets
