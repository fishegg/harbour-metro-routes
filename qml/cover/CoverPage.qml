/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.metro.routes.stationmodel 1.0
import "../components"

CoverBackground {
    id: coverbackground
    //Component.onCompleted: coverlistmodel.update()
    /*Label {
        id: label
        anchors.centerIn: parent
        text: qsTr("My Cover")
    }*/
    property int page: 1

    CoverPlaceholder {
        visible: coverlistview.count === 0
        icon.source: "image://theme/harbour-metro-routes"
        text: qsTr("Metro Routes")
    }

    ListView {
        id: coverlistview
        anchors.centerIn: parent
        width: parent.width - Theme.paddingMedium * 2
        height: parent.height - Theme.paddingMedium * 2
        //anchors.fill: parent

        /*Rectangle {
            anchors.centerIn: parent
            width: coverlistview.width
            height: coverlistview.height
            color: "white"
        }*/

        model: ListModel {
            id: coverlistmodel
            function update() {
                //console.log("count"+stationmodel.rowCount())
                clear()
                var previous_append = -1
                if (preference === StationModel.LessTimeTransfer) {
                    for (var i=0; i<stationmodel_type1.rowCount(); i++) {
                        if(stationmodel_type1.data(i,StationModel.ActionRole) === StationModel.Depart ||
                                stationmodel_type1.data(i,StationModel.ActionRole) === StationModel.Transfer ||
                                stationmodel_type1.data(i,StationModel.ActionRole) === StationModel.ExitTransfer ||
                                stationmodel_type1.data(i,StationModel.ActionRole) === StationModel.Arrive)
                        {
                            var count = (i === stationmodel_type1.rowCount() - 1 ?
                                             i - previous_append :
                                             i - previous_append - 1)
                            previous_append = i
                            append({//"number": stationmodel_type1.data(i,StationModel.NumRole),
                                       "station_name": stationmodel_type1.data(i,StationModel.StnNameRole),
                                       //"station_number": stationmodel_type1.data(i,StationModel.StnNumRole),
                                       "line_name": stationmodel_type1.data(i,StationModel.LineRole),
                                       "line_colour": stationmodel_type1.data(i,StationModel.LineColourRole),
                                       "towards": stationmodel_type1.data(i,StationModel.TowardsRole),
                                       "action": stationmodel_type1.data(i,StationModel.ActionRole),
                                       "count": count,
                                       "original_index": i
                                   })
                        }
                    }
                }
                else {
                    for (i=0; i<stationmodel_type2.rowCount(); i++) {
                        if(stationmodel_type2.data(i,StationModel.ActionRole) === StationModel.Depart ||
                                stationmodel_type2.data(i,StationModel.ActionRole) === StationModel.Transfer ||
                                stationmodel_type2.data(i,StationModel.ActionRole) === StationModel.ExitTransfer ||
                                stationmodel_type2.data(i,StationModel.ActionRole) === StationModel.Arrive)
                        {
                            count = (i === stationmodel_type2.rowCount() - 1 ?
                                             i - previous_append :
                                             i - previous_append - 1)
                            previous_append = i
                            append({//"number": stationmodel_type2.data(i,StationModel.NumRole),
                                       "station_name": stationmodel_type2.data(i,StationModel.StnNameRole),
                                       //"station_number": stationmodel_type2.data(i,StationModel.StnNumRole),
                                       "line_name": stationmodel_type2.data(i,StationModel.LineRole),
                                       "line_colour": stationmodel_type2.data(i,StationModel.LineColourRole),
                                       "towards": stationmodel_type2.data(i,StationModel.TowardsRole),
                                       "action": stationmodel_type2.data(i,StationModel.ActionRole),
                                       "count": count,
                                       "original_index": i
                                   })
                        }
                    }
                }
            }
        }

        delegate: CoverListViewDelegate {
            id: listviewdelegate
        }
    }

    CoverActionList {
        id: coverAction
        enabled: /*coverlistmodel.count > 4*/coverlistview.contentHeight > coverbackground.height - Theme.paddingMedium * 2

        CoverAction {
            iconSource: page === 1 ?
                            "image://theme/icon-cover-next":
                            "image://theme/icon-cover-previous"
            onTriggered: {
                if(page === 1) {
                    page = 2
                    coverlistview.positionViewAtEnd()
                }
                else if(page === 2) {
                    page = 1
                    coverlistview.positionViewAtBeginning()
                }
            }
        }
    }

    //onStatusChanged: console.log("content height="+coverlistview.contentItem.height)
//    Connections {
//        target: stationmodel
//        onRowsInserted: {
//            coverlistmodel.update()
//            //coverlistview.height = coverlistview.height * 0.75
//            //coverlistview.clip = true
//            //console.log("content height="+coverlistview.contentItem.height+"height="+coverlistview.height)
//            if(coverlistmodel.count > 3) {
//                //coverlistview.height = coverlistview.height * 0.75
//                coverlistview.clip = true
//            }
//            else {
//                coverlistview.clip = false
//            }
//        }
//    }

    Connections {
        target: application_window
        onPreferenceChanged: {
            coverlistmodel.update()
            if(coverlistmodel.count > 3) {
                coverlistview.clip = true
            }
            else {
                coverlistview.clip = false
            }
        }
    }

    Connections {
        target: stationmodel_type1
        onRowsInserted: {
            coverlistmodel.update()
            if(coverlistmodel.count > 3) {
                coverlistview.clip = true
            }
            else {
                coverlistview.clip = false
            }
        }
    }

    Connections {
        target: stationmodel_type2
        onRowsInserted: {
            coverlistmodel.update()
            if(coverlistmodel.count > 3) {
                coverlistview.clip = true
            }
            else {
                coverlistview.clip = false
            }
        }
    }
}


