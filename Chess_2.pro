QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    main.cpp

HEADERS += \
    board.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/0_0_1.png \
    img/0_0_2.png \
    img/0_1_2.png \
    img/0_1_3.png \
    img/0_2_1.png \
    img/1_0_5.png \
    img/1_4.png \
    img/2_1.png \
    img/3_1.png \
    img/4_1.png \
    img/5_1.png \
    img/6_1.png
