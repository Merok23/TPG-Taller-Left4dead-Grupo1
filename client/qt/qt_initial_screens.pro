QT += core widgets

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        choosesoldier.cpp \
        creatematch.cpp \
        joinmatch.cpp \
        main.cpp \
        mainwindow.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    choosesoldier.ui \
    creatematch.ui \
    joinmatch.ui \
    mainwindow.ui

HEADERS += \
    choosesoldier.h \
    creatematch.h \
    joinmatch.h \
    mainwindow.h

RESOURCES += \
    assets.qrc
