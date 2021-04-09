import QtQuick 2.5
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Datamodels 1.0
import QtQuick.Particles 2.15


Item {
    id: shelvesInfo

    ColumnLayout {
        id: layoutShelves
        anchors.fill: parent

        Text {
            id: footerText

            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            Layout.fillWidth: true
            Layout.preferredHeight: layoutShelves.height / 8

            text: "Available shelves:"
            color: textsColor
            font.pointSize: 15
        }

        SwipeView {
            id: view

            currentIndex: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.bottomMargin: layoutShelves.height / 10

            Repeater {
                model: bleController.shelvesModel

                Image {
                    id: shelfLogo
                    property ShelfItem currentShelf: model.object
                    source: currentShelf.shelfIcon

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {

                        }
                    }
                }
            }
        }

        PageIndicator {
            id: indicator

            count: view.count
            currentIndex: view.currentIndex

           // Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
