import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    SilicaFlickable{
        anchors.fill: parent
        contentHeight: column.height

        Column{
            id: column
            width: parent.width

            PageHeader{
                title: qsTr("Tutorial on making database")
            }

            TutorialLabel {}
        }

    }
}
