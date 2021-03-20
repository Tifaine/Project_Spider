QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        gestiondyna.cpp \
        libDyna/src/dynamixel_sdk/group_bulk_read.cpp \
        libDyna/src/dynamixel_sdk/group_bulk_write.cpp \
        libDyna/src/dynamixel_sdk/group_sync_read.cpp \
        libDyna/src/dynamixel_sdk/group_sync_write.cpp \
        libDyna/src/dynamixel_sdk/packet_handler.cpp \
        libDyna/src/dynamixel_sdk/port_handler.cpp \
        libDyna/src/dynamixel_sdk/port_handler_arduino.cpp \
        libDyna/src/dynamixel_sdk/port_handler_linux.cpp \
        libDyna/src/dynamixel_sdk/port_handler_mac.cpp \
        libDyna/src/dynamixel_sdk/port_handler_windows.cpp \
        libDyna/src/dynamixel_sdk/protocol1_packet_handler.cpp \
        libDyna/src/dynamixel_sdk/protocol2_packet_handler.cpp \
        main.cpp

RESOURCES += qml.qrc \
    font.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += libDyna/src/dynamixel_sdk
DEPENDPATH += libDyna/src/dynamixel_sdk
INCLUDEPATH += libDyna/include/dynamixel_sdk
DEPENDPATH += libDyna/include/dynamixel_sdk

HEADERS += \
    gestiondyna.h \
    libDyna/include/dynamixel_sdk/dynamixel_sdk.h \
    libDyna/include/dynamixel_sdk/group_bulk_read.h \
    libDyna/include/dynamixel_sdk/group_bulk_write.h \
    libDyna/include/dynamixel_sdk/group_sync_read.h \
    libDyna/include/dynamixel_sdk/group_sync_write.h \
    libDyna/include/dynamixel_sdk/packet_handler.h \
    libDyna/include/dynamixel_sdk/port_handler.h \
    libDyna/include/dynamixel_sdk/port_handler_arduino.h \
    libDyna/include/dynamixel_sdk/port_handler_linux.h \
    libDyna/include/dynamixel_sdk/port_handler_mac.h \
    libDyna/include/dynamixel_sdk/port_handler_windows.h \
    libDyna/include/dynamixel_sdk/protocol1_packet_handler.h \
    libDyna/include/dynamixel_sdk/protocol2_packet_handler.h \
    libDyna/src/DynamixelSDK.h

DISTFILES += \
    dynamixel_sdk/LICENSE
