import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.metro.routes.dbq 1.0

Page {
    property string github_url: "https://github.com/fishegg/harbour-metro-routes"
    DatabaseQuery {
        id:dbq
    }

    Flickable {
        anchors.fill: parent
        contentHeight: column.height
        Image {
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: column.top
                bottomMargin: height
            }
            source: "image://theme/harbour-metro-routes"
        }
        Column {
            id: column
            /*anchors {
                left: parent.left
                right: parent.right
                leftMargin: Theme.horizontalPageMargin
                rightMargin: Theme.horizontalPageMargin
            }*/
            width: parent.width
            spacing: Theme.paddingMedium
            PageHeader {
//                title: qsTr("软件信息")
                title: qsTr("App information")
            }

            Row {
                id: name_row
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingLarge
                Image {
                    //anchors.horizontalCenter: parent.horizontalCenter
                    source: "image://theme/harbour-metro-routes"
                }
                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    Label {
//                        text: qsTr("地铁查询工具")
                        text: qsTr("Metro Routes")
                        font.pixelSize: Theme.fontSizeLarge
                    }
                    Label {
//                        text: qsTr("非官方地铁路线查询工具")
                        text: qsTr("Unofficial Metro Guide")
                        font.pixelSize: Theme.fontSizeSmall
                        color: Theme.secondaryColor
                    }
                }
            }
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: version
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Github"
                onClicked: Qt.openUrlExternally(github_url)
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
}
