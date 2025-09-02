import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.metro.routes.appsettings 1.0

Dialog {
    AppSettings{
        id: settings
    }

    property var db_name

    SilicaFlickable {
        Component.onCompleted: {
            db_name = settings.get_db_name()
            settings.close_current_database()
        }

        anchors.fill: parent
        contentHeight: column.height
        Column {
            id: column
            width: parent.width
            DialogHeader {

            }

            SectionHeader{
                id: sh_using_database
                text: qsTr("Currently using database")
            }

            Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }
                color: Theme.highlightColor
//                text: qsTr("城市")
                text: qsTr("City")
            }

            Label {
                id: lb_database_city
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }
                text: settings.get_database_city()
            }

            Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }
                color: Theme.highlightColor
//                text: qsTr("地铁")
                text: qsTr("Metro")
            }

            Label {
                id: lb_database_name
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }
                width: parent.width - Theme.horizontalPageMargin * 2
                wrapMode: Text.WordWrap
                text: settings.get_database_name()
            }

            Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }
                color: Theme.highlightColor
//                text: qsTr("版本")
                text: qsTr("Version")
            }

            Label {
                id: lb_database_version
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }
                text: settings.get_database_version()
            }

            SectionHeader{
                text: qsTr("Settings")
            }

            ComboBox {
                id: cb_language
                label: qsTr("Station name language")
                currentIndex: settings.get_currentIndex_language()
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("System Language")
                    }
                    MenuItem {
                        text: "中文"
                    }
                    MenuItem {
                        text: "English or other language"
                    }
                }
            }

            ComboBox {
                id: cb_database
                label: qsTr("City")
                currentIndex: settings.get_currentIndex()
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Guangzhou/Foshan")
                        onClicked: db_name = "/usr/share/harbour-metro-routes/guangzhou_foshan_20251228.sqlite"
                    }
                    MenuItem {
                        text: qsTr("Customized database")
                        onClicked: db_name = "/home/defaultuser/Documents/"
                    }
                    MenuItem {
                        text: qsTr("Shenzhen")
                        onClicked: db_name = "/usr/share/harbour-metro-routes/shenzhen_20241228.sqlite"
                    }
                    onActivated: {
                        sh_using_database.text = qsTr("Selected database")
                        settings.open_selected_database(db_name)
                        lb_database_city.text = settings.get_database_city()
                        lb_database_name.text = settings.get_database_name()
                        lb_database_version.text = settings.get_database_version()
                        settings.close_current_database()
                    }
                }
            }
//            ComboBox {
//                label: "fsdjlkf"
//                menu: ContextMenu {
//                    MenuItem {
//                        text: "fsdjl"
//                    }
//                }
//            }
//            Slider {
//                minimumValue: 0
//                maximumValue: 100
//                width: parent.width
//                valueText: sliderValue
//            }
            TextField {
                id: tf_database
                text: db_name
                readOnly: cb_database.currentIndex !== 1 ? true : false
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                visible: cb_database.currentIndex === 1
                text: qsTr("Test database")
                onClicked: {
                    settings.open_selected_database(tf_database.text)
                    lb_database_city.text = settings.get_database_city()
                    lb_database_name.text = settings.get_database_name()
                    lb_database_version.text = settings.get_database_version()
                    settings.close_current_database()
                }
            }

            Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.paddingMedium
                    rightMargin: Theme.paddingMedium
                }
                wrapMode: Text.WordWrap
                text: qsTr("If database information displayed, the database should be available.")
                visible: cb_database.currentIndex === 1
            }
//            Label {
//                anchors {
//                    left: parent.left
//                    right: parent.right
//                    leftMargin: Theme.paddingMedium
//                    rightMargin: Theme.paddingMedium
//                }
//                wrapMode: Text.WordWrap
//                text: qsTr("Please restart app after change settings.")
//            }

            SectionHeader {
                text: qsTr("Tutorial")
            }
            Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.paddingMedium
                    rightMargin: Theme.paddingMedium
                }
                wrapMode: Text.WordWrap
                text: qsTr("How to make a new database of the metro of your city?")
            }
            Button {
                text: qsTr("Tutotial")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: pageStack.push(Qt.resolvedUrl("TutorialPage.qml"))
            }
        }
    }

    onAccepted: {
        settings.set_db_name(tf_database.text)
        settings.set_currentIndex(cb_database.currentIndex)
        settings.set_currentIndex_language(cb_language.currentIndex)
    }
}
