import QtQuick 2.0

Rectangle {
    width: parent.width
    height: parent.height / 8
    anchors.topMargin: parent.height / 4

    border.width: 1
    border.color: "#363636"
    radius: 5
    property string headerText: ""

    Text {
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.fill: parent
        text: headerText
        font.bold: true
        font.pointSize: 20
        elide: Text.ElideMiddle
        color: "#363636"
    }
}
