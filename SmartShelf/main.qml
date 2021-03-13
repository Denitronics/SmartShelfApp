//import QtQuick 2.12
import QtQuick 2.5
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Datamodels 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 320
    height: 600
    title: qsTr("")
    color: "lightskyblue"

    //flags: Qt.FramelessWindowHint // remove title bar from the application

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

            text: "Shelves"
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

        SmartShelf {
            id: smartShelf
        }

        AppInfo {
            id: appInfoScreen
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

