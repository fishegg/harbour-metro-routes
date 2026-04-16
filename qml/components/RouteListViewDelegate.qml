import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.metro.routes.stationmodel 1.0

ListItem {
    id: root
    contentHeight: column.height + Theme.paddingSmall > Theme.itemSizeSmall ?
                       column.height + Theme.paddingSmall:
                       Theme.itemSizeSmall
    Row {
        height: parent.height
        width: parent.width - Theme.horizontalPageMargin
        anchors.verticalCenter: parent.verticalCenter
        Item {
            id: iconitem
            height: parent.height
            width: Theme.iconSizeLarge

            GlassItem {
                id: icon
                z: 2
                anchors.verticalCenter: parent.verticalCenter
//                width: Theme.paddingLarge
//                scale: (action === StationModel.GetOff ||
//                        action === StationModel.Transfer ||
//                        action === StationModel.Exit ||
//                        action === StationModel.ExitTransfer) ?
//                           0.9 :
//                           1
//                height: width
//                radius: width / 2
                radius: 1
                falloffRadius: action === StationModel.OnTrain ? 0.15 : 0.22
                color: line_colour
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Loader {
                z: -1
                width: sourceComponent === component_upperline_glassitem ?
                           Theme.paddingLarge * 0.5 :
                           Theme.paddingLarge * 0.75
                height: root.contentHeight / 2
                anchors {
                    bottom: icon.verticalCenter
                    horizontalCenter: icon.horizontalCenter
                }
                sourceComponent: action !== StationModel.Depart ?
                                     ((action === StationModel.Transfer ||
                                      action === StationModel.ExitTransfer) ?
                                          component_upperline_rectangle :
                                          component_upperline_glassitem) :
                                     undefined
            }
            Loader {
                z: -1
                width: sourceComponent === component_lowerline_glassitem ?
                           Theme.paddingLarge * 0.5 :
                           Theme.paddingLarge * 0.75
                height: root.contentHeight / 2
                anchors {
                    top: icon.verticalCenter
                    horizontalCenter: icon.horizontalCenter
                }
                sourceComponent: action !== StationModel.Arrive ?
                                     ((action === StationModel.GetOff ||
                                       action === StationModel.Exit) ?
                                          component_lowerline_rectangle :
                                          component_lowerline_glassitem) :
                                     undefined
            }

            Component {
                id: component_upperline_rectangle
                Rectangle {
//                    z: -1
//                    visible: action !== StationModel.Depart
//                    width: /*(action === StationModel.Transfer) ?
//                               Theme.paddingMedium :*/
//                               Theme.paddingLarge * 0.5
//                    height: root.contentHeight / 2
    //                ratio: 0.0
    //                radius: 0
    //                falloffRadius: 1
//                    color: Theme.rgba(line_colour, 0.8)
                    gradient: (action === StationModel.Transfer ||
                               action === StationModel.ExitTransfer) ?
                                  gradient_upper_line :
                                  undefined
//                    anchors {
//                        bottom: icon.verticalCenter
//                        horizontalCenter: icon.horizontalCenter
//                    }
                    Gradient {
                        id: gradient_upper_line
                        GradientStop {position: 0; color: Theme.rgba(Theme.highlightColor, 0.5)}
                        GradientStop {position: 0.9; color: Theme.rgba(line_colour, 0.5)}
                        GradientStop {position: 1; color: Theme.rgba(line_colour, 0.5)}
                    }
                }
            }
            Component {
                id: component_upperline_glassitem
                GlassItem {
//                    z: -1
//                    visible: action !== StationModel.Depart
//                    width: /*(action === StationModel.Transfer) ?
//                               Theme.paddingMedium :*/
//                               Theme.paddingLarge * 0.5
//                    height: root.contentHeight / 2
                    ratio: 0.0
                    radius: 0
                    falloffRadius: 1
                    color: line_colour
//                    anchors {
//                        bottom: icon.verticalCenter
//                        horizontalCenter: icon.horizontalCenter
//                    }
                    Gradient {
                        id: gradient_upper_line
                        GradientStop {position: 0; color: Theme.highlightColor}
                        GradientStop {position: 0.9; color: line_colour}
                        GradientStop {position: 1; color: line_colour}
                    }
                }
            }
            Component {
                id: component_lowerline_rectangle
                Rectangle {
//                    z: -1
//                    visible: action !== StationModel.Arrive
//                    width: /*(action === StationModel.GetOffTransfer) ?
//                               Theme.paddingMedium :*/
//                               Theme.paddingLarge * 0.5
//                    height: root.contentHeight / 2// + contextmenu.height
    //                ratio: 0.0
    //                radius: 0
    //                falloffRadius: 1
//                    color: Theme.rgba(line_colour, 0.8)
                    gradient: (action === StationModel.GetOff ||
                               action === StationModel.Exit) ?
                                  gradient_lower_line :
                                  undefined
//                    anchors {
//                        top: icon.verticalCenter
//                        horizontalCenter: icon.horizontalCenter
//                    }
                    Gradient {
                        id: gradient_lower_line
                        GradientStop {position: 0; color: Theme.rgba(line_colour, 0.5)}
                        GradientStop {position: 0.1; color: Theme.rgba(line_colour, 0.5)}
                        GradientStop {position: 1; color: Theme.rgba(Theme.highlightColor, 0.5)}
                    }
                }
            }
            Component {
                id: component_lowerline_glassitem
                GlassItem {
//                    z: -1
//                    visible: action !== StationModel.Arrive
//                    width: /*(action === StationModel.GetOffTransfer) ?
//                               Theme.paddingMedium :*/
//                               Theme.paddingLarge * 0.5
//                    height: root.contentHeight / 2// + contextmenu.height
                    ratio: 0.0
                    radius: 0
                    falloffRadius: 1
                    color: line_colour
//                    anchors {
//                        top: icon.verticalCenter
//                        horizontalCenter: icon.horizontalCenter
//                    }
                    Gradient {
                        id: gradient_lower_line
                        GradientStop {position: 0; color: line_colour}
                        GradientStop {position: 0.1; color: line_colour}
                        GradientStop {position: 1; color: Theme.highlightColor}
                    }
                }
            }
//            GlassItem {
//                id: iconbackground
//                z: (action === StationModel.GetOff ||
//                    action === StationModel.Transfer ||
//                    action === StationModel.ExitTransfer) ?
//                       1 :
//                       -1
//                anchors.centerIn: icon
////                width: (action === StationModel.GetOff ||
////                        action === StationModel.Transfer ||
////                        action === StationModel.Exit ||
////                        action === StationModel.ExitTransfer) ?
////                           Theme.itemSizeMedium :
////                           Theme.itemSizeMedium
////                height: width
//                radius: 1
//                falloffRadius: 0.22
//                color: (action === StationModel.GetOff ||
//                        action === StationModel.Exit) ?
//                           (preference === 1 ?
//                                stationmodel_type1.linecolourat(index + 1) :
//                                stationmodel_type2.linecolourat(index + 1)) :
//                           ((action === StationModel.Transfer ||
//                            action === StationModel.ExitTransfer) ?
//                                (preference === 2 ?
//                                     stationmodel_type1.linecolourat(index - 1) :
//                                     stationmodel_type2.linecolourat(index - 1)) :
//                                line_colour)
//            }
//            GlassItem {
//                id: upperlinebackground
//                z: -1
//                anchors.centerIn: upperline
//                visible: upperline.visible
//                width: upperline.width
//                height: upperline.height
//                ratio: 0
//                radius: 0
//                falloffRadius: 1
//                color: line_colour
//            }
//            GlassItem {
//                id: lowerlinebackground
//                z: -1
//                anchors.centerIn: lowerline
//                visible: lowerline.visible
//                width: lowerline.width
//                height: lowerline.height
//                ratio: 0
//                radius: 0
//                falloffRadius: 1
//                color: line_colour
//            }
        }

        Column {
            id: column
            anchors.verticalCenter: parent.verticalCenter
            width: row.width - iconitem.width
            Label {
                id: namelabel
                width: parent.width
                wrapMode: Text.Wrap
                color: ((action !== StationModel.OnTrain &&
                        action !== StationModel.GetOff &&
                        action !== StationModel.Exit &&
                        action !== StationModel.Arrive) ||
                       root.highlighted) ?
                           Theme.highlightColor:
                           Theme.primaryColor
                font.bold: action === StationModel.OnTrain ? false : true
                text: station_number === "" ?
                          station_name :
                          station_number + " " + station_name
            }
            Loader {
                id: loader
                width: parent.width
                sourceComponent: action !== StationModel.OnTrain ?
                                     actionlabelcomponent :
                                     undefined
            }
        }
    }

    Component {
        id: actionlabelcomponent
        Label {
            id: actionlabel
            wrapMode: Text.Wrap
            //visible: action != StationModel.OnTrain
            color: /*!root.highlighted ?
                       Theme.secondaryColor :
                       Theme.secondaryHighlightColor*/namelabel.color
            font.pixelSize: Theme.fontSizeSmall
            text: action === StationModel.Depart ?
//                      qsTr("在 %1入闸处 入闸<br>乘坐 %2 %3方向 列车").arg(line_name).arg(line_name).arg(towards) :
                      qsTr("Enter from %1 entrance<br>Take %2 towards %3").arg(line_name).arg(line_name).arg(towards) :
                      (action === StationModel.GetOff ?
//                           qsTr("下车") :
                           qsTr("Get off") :
                           (action === StationModel.Transfer ?
//                                qsTr("换乘 %1 %2方向 列车").arg(line_name).arg(towards) :
                                qsTr("Change to %1 towards %2").arg(line_name).arg(towards) :
                                (action === StationModel.Exit ?
//                                     qsTr("下车，出闸") :
                                     qsTr("Get off, exit") :
                                     (action === StationModel.ExitTransfer ?
//                                          qsTr("在 %1入闸处 入闸<br>换乘 %2 %3方向 列车").arg(line_name).arg(line_name).arg(towards) :
                                          qsTr("Enter from %1 entrance<br>Change to %2 towards %3").arg(line_name).arg(line_name).arg(towards) :
                                          (action === StationModel.Arrive ?
//                                               qsTr("下车，到达") :
                                               qsTr("Get off, arrive") :
                                               "")
                                      )
                                 )
                            )
                       )/*{
                if(action == StationModel.Depart)
                    qsTr("乘坐 %1 往%2方向 列车").arg(line).arg(toward)
                else if(action == StationModel.GetoffTransfer)
                    qsTr("下车")
                else if(action == StationModel.Transfer)
                    qsTr("换乘 %1 往%2方向 列车").arg(line).arg(toward)
                else if(action == StationModel.Exit)
                    qsTr("下车，出闸")
                else if(action == StationModel.ExitTransfer)
                    //action + " " + line_name + " 往" + direction + "方向 列车"
                    qsTr("%1入闸，换乘 %2 往%3方向 列车").arg(line).arg(line).arg(toward)
                else if(action == StationModel.Arrive)
                    qsTr("下车，到达")
            }*/
        }
    }

    /*menu: ContextMenu {
        id: contextmenu
        MenuItem {
            text: "haha"
        }
    }*/
}
