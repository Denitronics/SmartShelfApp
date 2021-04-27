import QtQuick 2.5
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Datamodels 1.0
import QtQuick.Particles 2.15


Item {
    id: root

    property ShelfItemModel selectedShelf: null

    StackLayout {
        id: stackViewShelves
        anchors.fill: parent
        currentIndex: 0

        Item {
            id: itemShelves

            Layout.fillHeight: true
            Layout.fillWidth: true

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
                            property ShelfItemModel currentShelfModel: model.object
                            property int shelfItemsCount: model.size
                            source: currentShelfModel.shelfIcon

                            MouseArea {
                                anchors.fill: parent

                                onClicked: {
                                    stackViewShelves.currentIndex = 1
                                    root.selectedShelf = shelfLogo.currentShelfModel
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

        Item {
            id: itemSelectedShelf

            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                id: layoutSelectedShelf
                anchors.fill: parent
                spacing: 0

                Image {
                    id: backButton

                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    source: "icons/navigation_previous_item.png"

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            stackViewShelves.currentIndex = 0
                            root.selectedShelf = null
                        }
                    }
                }

                Text {
                    id: shelfName

                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                    Layout.fillWidth: true
                    Layout.preferredHeight: layoutSelectedShelf.height / 20

                    text: (root.selectedShelf === null)? "Shelf type: " : "Shelf type: " + root.selectedShelf.shelfName
                    color: textsColor
                    font.pointSize: 15
                }


                Text {
                    id: shelfInitialStock

                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                    Layout.fillWidth: true
                    Layout.preferredHeight: layoutSelectedShelf.height / 20

                    text: (root.selectedShelf === null)? "Initial stock: " : "Initial stock: " + root.selectedShelf.getInitialItemsCount()
                    color: textsColor
                    font.pointSize: 15
                }


                Rectangle {
                    id: frameShelfLeftStock
                    Layout.preferredWidth: layoutSelectedShelf.width / 4
                    Layout.preferredHeight: layoutSelectedShelf.height / 3 * 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                    color: "transparent"
                    border.color: textsColor                      

                    ListView {
                        id: selectedShelfView

                        verticalLayoutDirection: ListView.BottomToTop

                        width: frameShelfLeftStock.width
                        height: frameShelfLeftStock.height

                        spacing: 0

                        model: root.selectedShelf

                        delegate: Rectangle {

                            property ShelfItem shelfItem: model.object

                            width: frameShelfLeftStock.width
                            height: {
                                if (root.selectedShelf === null) {
                                    0
                                }
                                else {
                                    frameShelfLeftStock.height / root.selectedShelf.getInitialItemsCount()
                                }
                            }

                            color: "transparent"
                            border.color: textsColor

                            Image {
                                anchors.fill: parent
                                source: shelfItem.shelfIcon
                                visible: shelfItem.itemAvailable
                            }
                        }
                    }
                }
            }
        }
    }
}
