#qt包含的模块
QT       += core gui
QT       += network
QMAKE_CXXFLAGS += -Wno-unused-parameter

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets     #大于4版本以上 包含weight模块

CONFIG += c++11

TARGET = 2100810224_QtAPP   #EXE文件名称


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \            #源文件
    defaultconfig.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \            #头文件
    defaultconfig.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    2100810224_QtAPP_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
