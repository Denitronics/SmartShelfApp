import QtQuick 2.5
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {

    id: windowSearchBLE
    Layout.fillHeight: true
    Layout.fillWidth: true

    ColumnLayout {

        width: parent.width
        height: parent.height
        spacing: 0

        TextEdit {

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height / 2
            Layout.alignment: Qt.AlignHCenter

            text: "Test"
        }

        RowLayout {

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height / 2
            Layout.alignment: Qt.AlignHCenter

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
