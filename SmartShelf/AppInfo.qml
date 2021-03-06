import QtQuick 2.5
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Datamodels 1.0

Item {
    id: appInfoScreen

    Layout.fillHeight: true
    Layout.fillWidth: true


    Rectangle {

        id: infoText
        width: appInfoScreen.width - 2 * footer.height
        height: appInfoScreen.height / 4
        anchors.centerIn: appInfoScreen
        anchors.verticalCenterOffset: - height

        border.color: bordersColor
        color: "transparent"


        ListView {

            anchors.fill: parent

            model: appInfoModel

            delegate: Text {
                    property AppInfoItem currentAppInfo: model.object
                    width: parent.width
                    height: infoText.height / model.size
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: currentAppInfo.appInfoType + ": " + currentAppInfo.appInfo
                }
        }
    }
}
