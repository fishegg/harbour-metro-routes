import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"
import harbour.metro.routes.dbc 1.0
import harbour.metro.routes.stationmodel 1.0

ApplicationWindow {
    id: application_window
    initialPage: Component { FirstPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
    _defaultPageOrientations: Orientation.All

    property string version: "2.0"
    property string db_dir: "/usr/share/harbour-metro-routes/"
    property string guangzhou_foshan_db_file: "guangzhou_foshan_20260213.sqlite"
    property string customized_db_dir: StandardPaths.documents
    property string shenzhen_db_file: "shenzhen_20251228.sqlite"
    property int preference: 1

    property int load_status: StationModel.Null
    //stationmodel.getfulllistdata()
    //load_status = stationmodel.getmapdata()
    StationModel {
        id: stationmodel
    }
    StationModel {
        id: stationmodel_type1
    }
    StationModel {
        id: stationmodel_type2
    }
}
