//import QtQuick 2.12
import QtQuick 2.5
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 320
    height: 600
    title: qsTr("")
    color: "lightskyblue"

    flags: Qt.FramelessWindowHint // remove title bar from the application

    property string screenName: "Home screen"
    property string textsColor: "gray"
    property string bordersColor: "gray"
    property int headerFooterSize: height / 15

    RowLayout {
        id: menuButtons

        height: mainWindow.height / 15
        Layout.fillWidth: true

        spacing: 1

        Button {
            Layout.fillHeight: true
            Layout.preferredWidth: mainWindow.width / 4

            text: "Home"
            onClicked: {
                stackLayoutApp.currentIndex = 0
                screenName = qsTr("Home screen")
            }           
        }

        Button {
            Layout.fillHeight: true
            Layout.preferredWidth: mainWindow.width / 4

            text: "Connect"
            onClicked: {
                stackLayoutApp.currentIndex = 1
                screenName = qsTr("Connect with SmartShelf")
            }            
        }

        Button {
            Layout.fillHeight: true
            Layout.preferredWidth: mainWindow.width / 4

            text: "About"
            onClicked: {
                stackLayoutApp.currentIndex = 2
                screenName = qsTr("Information")
            }
        }

        Button {
            Layout.fillHeight: true
            Layout.preferredWidth: mainWindow.width / 4

            text: "Exit"
            onClicked: {
                Qt.quit()
            }
        }
    }

    StackLayout {

        id: stackLayoutApp
        width: mainWindow.width
        height: mainWindow.height - (2 * headerFooterSize)
        anchors.top: menuButtons.bottom

        Item {

            id: homeScreen

            width: mainWindow.width
            height: mainWindow.height * 9 / 10

            anchors.verticalCenterOffset: mainWindow.height / 10

            Image {
                id: logoImage
                anchors.centerIn: homeScreen
                anchors.verticalCenterOffset: - height / 5
                source: "icons/shelf-logo.jpg"
            }

            Text {
                width: homeScreen.width
                height: mainWindow.height / 10
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: homeScreen
                anchors.verticalCenterOffset: logoImage.height / 2
                color: textsColor
                text: "Smart Shelf"

                font.pointSize: 30
            }

        }

        Rectangle {
            id: searchDevicesScreen

            Layout.fillWidth: true
            Layout.fillHeight: true

            border.color: bordersColor
            color: "transparent"
        }

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

                    Text {
                        width: layoutAppInfo.width
                        height: layoutAppInfo.height / 4
                        font.bold: true

                        anchors.horizontalCenter: parent.horizontalCenter

                        color: textsColor
                        text: "Application: SmartShelf"

                        font.pointSize: 10
                    }

                    Text {
                        width: layoutAppInfo.width
                        height: layoutAppInfo.height / 4
                        font.bold: true

                        anchors.horizontalCenter: parent.horizontalCenter

                        color: textsColor
                        text: "Author: Denislav Trifonov"

                        font.pointSize: 10
                    }

                    Text {
                        width: layoutAppInfo.width
                        height: layoutAppInfo.height / 4
                        font.bold: true

                        anchors.horizontalCenter: parent.horizontalCenter

                        color: textsColor
                        text: "Technology: Bluetooth 4.2"

                        font.pointSize: 10
                    }

                    Text {
                        width: layoutAppInfo.width
                        height: layoutAppInfo.height / 4
                        font.bold: true

                        anchors.horizontalCenter: parent.horizontalCenter

                        color: textsColor
                        text: "Version: 0.1"

                        font.pointSize: 10
                    }
                }
            }
        }
    }

    // Footer - screen name
    Rectangle {
        id: footer

        width: homeScreen.width
        height: mainWindow.height / 15
        anchors.bottom: parent.bottom

        color: "lightgray"

        Text {
            id: footerText

            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent

            text: screenName
            color: textsColor
            font.pointSize: 15
        }
    }
}

