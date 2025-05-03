import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.metro.routes.appsettings 1.0

Dialog {
    AppSettings{
        id: settings
    }

    property var database: settings.get_database()

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height
        Column {
            id: column
            width: parent.width
            DialogHeader {

            }

            SectionHeader{
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
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }
                text: settings.get_database_city(database)
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
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }
                width: parent.width - Theme.horizontalPageMargin * 2
                wrapMode: Text.WordWrap
                text: settings.get_database_name(database)
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
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }
                text: settings.get_database_version(database)
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
                        text: "简体中文"
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
                        onClicked: tf_database.text = "/usr/share/harbour-metro-routes/guangzhou_foshan_20241228.sqlite"
                    }
                    MenuItem {
                        text: qsTr("Customized database")
                    }
                    MenuItem {
                        text: qsTr("Shenzhen")
                        onClicked: tf_database.text = "/usr/share/harbour-metro-routes/shenzhen_20241228.sqlite"
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
                text: database
                readOnly: cb_database.currentIndex !== 1 ? true : false
                visible: true
            }
//            Button {
//                id: bt_database
//                anchors.left: parent.left
//                anchors.leftMargin: Theme.paddingMedium
//                text: qsTr("Test Database")
//                visible: cb_database.currentIndex > 0 ? true : false
//                onClicked: {
//                    lb_database_test.text = settings.test_database(tf_database.text)
//                }
//            }
//            Label {
//                id: lb_database_test
//                anchors {
//                    left: parent.left
//                    right: parent.right
//                    leftMargin: Theme.paddingMedium
//                    rightMargin: Theme.paddingMedium
//                }
//                wrapMode: Text.WordWrap
//                text: ""
//                visible: cb_database.currentIndex > 0 ? true : false
//            }
//            Label {
//                anchors {
//                    left: parent.left
//                    right: parent.right
//                    leftMargin: Theme.paddingMedium
//                    rightMargin: Theme.paddingMedium
//                }
//                wrapMode: Text.WordWrap
//                text: qsTr("If database information displayed, the database should be available.")
//                visible: cb_database.currentIndex > 0 ? true : false
//            }
            Label {
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.paddingMedium
                    rightMargin: Theme.paddingMedium
                }
                wrapMode: Text.WordWrap
                text: qsTr("Please restart app after change settings.")
            }

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
        settings.set_database(tf_database.text)
        settings.set_currentIndex(cb_database.currentIndex)
        settings.set_currentIndex_language(cb_language.currentIndex)
    }
}
