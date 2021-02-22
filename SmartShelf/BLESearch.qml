import QtQuick 2.5
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {

    id: windowSearchBLE
    width: parent.width
    height: parent.height

    ColumnLayout {

        width: parent.width
        height: parent.height
        spacing: 0

        TextEdit {
            width: parent.width
            height: parent.height / 2

            anchors.horizontalCenter: parent.horizontalCenter

            text: "Test"
        }

        RowLayout {

            width: parent.width
            height: parent.height / 2

            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            RoundButton {
                width: windowSearchBLE.width / 2
                text: "Search"
            }

            RoundButton {

                width: windowSearchBLE.width / 2
                text: "Connect"
            }
        }
    }
}
