android = $$find(QMAKE_CC, "Android")

count(android, 0){
    message("Buidling for a desktop device")
    QT += qml quick sql widgets gui
}
else {
    message("Building for an android device")
    QT += qml quick sql widgets gui androidextras
}

# required to find the android sources from the Qt code
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

LIBS += -L"$ANDROID_NDK"

CONFIG += c++11 qtquickcompiler

# Windows icon
RC_FILE = resources/icons/acorn.rc

HEADERS += \
    src/model/task.h \
    src/util/local_db.h \
    src/main.h \
    src/util/system.h \
    src/util/notification_client.h \
    src/util/model_provider.h

SOURCES += src/main.cpp \
    src/model/task.cpp \
    src/util/local_db.cpp \
    src/util/system.cpp \
    src/util/notification_client.cpp \
    src/util/model_provider.cpp

RESOURCES += qml.qrc

OTHER_FILES += \
    qml/main.qml \
    qml/Tasks.qml \
    qml/TasksForm.qml \
    android-sources/src/org/achieveaholic/acorn/NotificationClient.java \
    android-sources/AndroidManifest.xml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android-sources/libs/classes.jar \
    android-sources/res/drawable-ldpi/icon.png \
    android-sources/res/drawable-ldpi/icon_notification.png \
    android-sources/res/drawable/icon.png \
    android-sources/res/drawable/icon_notification.png

