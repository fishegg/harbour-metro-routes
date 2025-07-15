import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"
import harbour.metro.routes.dbc 1.0
import harbour.metro.routes.stationmodel 1.0

ApplicationWindow {
    initialPage: Component { FirstPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
    _defaultPageOrientations: Orientation.All

    property string version: "1.5"

    property int load_status: StationModel.Null
    //stationmodel.getfulllistdata()
    //load_status = stationmodel.getmapdata()
    StationModel {
        id: stationmodel
    }
}
