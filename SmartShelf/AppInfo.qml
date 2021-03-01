import QtQuick 2.5
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

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

        ColumnLayout {

            id: layoutAppInfo
            anchors.fill: infoText
            spacing: 0

            Text {
                Layout.preferredWidth: layoutAppInfo.width
                Layout.preferredHeight: layoutAppInfo.height / 4
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true

                color: textsColor
                text: "Application: SmartShelf"

                font.pointSize: 10
            }

            Text {
                Layout.preferredWidth: layoutAppInfo.width
                Layout.preferredHeight: layoutAppInfo.height / 4
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true

                color: textsColor
                text: "Author: Denislav Trifonov"

                font.pointSize: 10
            }

            Text {
                Layout.preferredWidth: layoutAppInfo.width
                Layout.preferredHeight: layoutAppInfo.height / 4
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true

                color: textsColor
                text: "Technology: Bluetooth 4.2"

                font.pointSize: 10
            }

            Text {
                Layout.preferredWidth: layoutAppInfo.width
                Layout.preferredHeight: layoutAppInfo.height / 4
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true

                color: textsColor
                text: "Version: 0.1"

                font.pointSize: 10
            }
        }
    }
}
