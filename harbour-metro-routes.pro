# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
QT += sql

TARGET = harbour-metro-routes

CONFIG += sailfishapp

SOURCES += src/harbour-metro-routes.cpp \
    src/appsettings.cpp \
    src/databaseconnector.cpp \
    src/databasequery.cpp \
    src/graphm.cpp \
    src/line.cpp \
    src/linemodel.cpp \
    src/routesearch.cpp \
    src/station.cpp \
    src/stationmodel.cpp

DISTFILES += qml/harbour-metro-routes.qml \
    qml/components/TutorialLabel.qml \
    qml/cover/CoverListViewDelegate.qml \
    qml/cover/CoverPage.qml \
    qml/cover/RouteListViewDelegate.qml \
    qml/pages/DisclaimerDialog.qml \
    qml/pages/FirstPage.qml \
    qml/pages/InformationPage.qml \
    qml/pages/SettingsPage.qml \
    qml/pages/StationsListDialog.qml \
    metro_routes_data/guangzhou_foshan_20241228.sqlite \
    metro_routes_data/shenzhen_20241228.sqlite \
    qml/pages/TutorialPage.qml \
    rpm/harbour-metro-routes.changes \
    rpm/harbour-metro-routes.changes.run.in \
    rpm/harbour-metro-routes.spec \
    translations/*.ts \
    harbour-metro-routes.desktop \
    translations/harbour-metro-routes-zh_CN.ts \
    translations/harbour-metro-routes-zh_TW.ts \
    translations/harbour-metro-routes-zh_HK.ts \

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
#TRANSLATIONS += translations/harbour-metro-routes-de.ts
TRANSLATIONS += translations/harbour-metro-routes-zh_CN.ts \
    translations/harbour-metro-routes-zh_TW.ts \
    translations/harbour-metro-routes-zh_HK.ts

HEADERS += \
    src/appsettings.h \
    src/databaseconnector.h \
    src/databasequery.h \
    src/graphm.h \
    src/line.h \
    src/linemodel.h \
    src/routesearch.h \
    src/station.h \
    src/stationmodel.h

#database
db.path = /usr/share/harbour-metro-routes
db.files += $$PWD/metro_routes_data/guangzhou_foshan_20241228.sqlite
dbsz.path = /usr/share/harbour-metro-routes
dbsz.files += $$PWD/metro_routes_data/shenzhen_20241228.sqlite
INSTALLS += db \
    dbsz
