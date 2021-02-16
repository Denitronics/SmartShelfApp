import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 300
    height: 600
    title: qsTr("")
    color: "lightskyblue"

    RowLayout {
        Layout.preferredHeight: mainWindow.height / 10
        Layout.fillWidth: true

        spacing: 1

        Button {
            text: "Home"
            onClicked: {
                stackLayoutApp.currentIndex = 0
            }
        }

        Button {
            text: "Search"
            onClicked: {
                stackLayoutApp.currentIndex = 1
            }
        }

        Button {
            text: "About"
            onClicked: {
                stackLayoutApp.currentIndex = 2
            }
        }
    }

    StackLayout {

        id: stackLayoutApp
        width: mainWindow.width
        height: mainWindow.height * 9 / 10
        //anchors.verticalCenterOffset: - mainWindow.height / 10

        Item {

            id: homeScreen

            width: mainWindow.width
            height: mainWindow.height * 9 / 10

            anchors.verticalCenterOffset: mainWindow.height / 10

            Image {
                id: logoImage
                anchors.centerIn: homeScreen
                anchors.verticalCenterOffset: - height / 5
                source: "icons/shelf-logo.png"
            }

            Text {
                width: homeScreen.width
                height: mainWindow.height / 10
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: homeScreen
                anchors.verticalCenterOffset: logoImage.height * 5 / 6
                color: "black"
                text: "Smart Shelf"

                font.pointSize: 30
            }
        }

        Item {
            id: searchDevicesScreen

            width: mainWindow.width
            height: mainWindow.height * 9 / 10

            anchors.verticalCenterOffset: mainWindow.height / 10
        }

        Item {
            id: appInfoScreen

            width: mainWindow.width
            height: mainWindow.height * 9 / 10

            ColumnLayout {

                Layout.fillWidth: true
                Layout.fillHeight: true

                Text {

                    width: homeScreen.width
                    height: mainWindow.height / 10
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    //anchors.centerIn: homeScreen

                    color: "black"
                    text: "Application: SmartShelf"

                    font.pointSize: 10
                }

                Text {

                    width: homeScreen.width
                    height: mainWindow.height / 10

                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter

                    //anchors.centerIn: homeScreen
                    //anchors.verticalCenterOffset: logoImage.height * 5 / 6

                    color: "black"
                    text: "Version: 0.1"

                    font.pointSize: 10
                }

                Text {
                    width: homeScreen.width
                    height: mainWindow.height / 10

                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    //anchors.centerIn: homeScreen
                    //anchors.verticalCenterOffset: logoImage.height * 5 / 6
                    color: "black"
                    text: "Author: Denislav Trifonov"

                    font.pointSize: 10
                }
            }
        }
    }
}

