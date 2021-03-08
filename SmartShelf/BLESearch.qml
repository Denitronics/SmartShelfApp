import QtQuick 2.5
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Datamodels 1.0
import QtQuick.Particles 2.15

Item {

    id: windowSearchBLE
    Layout.fillHeight: true
    Layout.fillWidth: true

    property bool deviceSelected: false

    ColumnLayout {

        anchors.fill: parent
        anchors.topMargin: 10
        spacing: 10

        Rectangle {

            id: availableDevices
            Layout.preferredWidth: parent.width - 20
            Layout.preferredHeight: parent.height / 3 * 2
            Layout.alignment: Qt.AlignHCenter
            color: "transparent"
            border.color: "#E0E0E0"

            ListView {

                anchors.fill: parent
                model: bleController.bleDevicesModel
                interactive: {
                    if (model.size >= 4)
                    {
                        false
                    }
                    else
                    {
                        true
                    }
                }

                delegate: Rectangle {

                        id: itemBluetoothDevice
                        width: availableDevices.width
                        height: availableDevices.height / 4//(model.size + 1)
                        color: "transparent"
                        border.color: "#E0E0E0"

                        Text {
                            property BLEDeviceItem currentBLEDevice: model.object

                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            text: currentBLEDevice.bleDeviceName + ":\r\n "+currentBLEDevice.bleDeviceAddress
                            font.bold: true
                            font.pointSize: 12

                            MouseArea {
                                anchors.fill: parent

                                onPressed: {
                                    focus = true
                                    itemBluetoothDevice.color = "#E0E0E0"
                                    deviceSelected = true
                                }
                                onFocusChanged:
                                {
                                    if (focus === false)
                                    {
                                        itemBluetoothDevice.color = "transparent"
                                    }
                                }
                            }
                        }
                    }
            }
        }

        Item {

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height / 16

            Image {
                id: background
                anchors.fill: parent
                visible: bleController.searchDevicesIconVisible
                source: "icons/busy_dark.png"
                fillMode: Image.PreserveAspectFit
                NumberAnimation on rotation { duration: 3000; from:0; to: 360; loops: Animation.Infinite}
            }
        }

        RowLayout {

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height / 4
            Layout.alignment: Qt.AlignHCenter

            spacing: 10

            RoundButton {
                Layout.preferredWidth: windowSearchBLE.width / 3 - 2 * spacing
                Layout.alignment: Qt.AlignCenter
                text: {
                    if (bleController.searchDevicesIconVisible === false)
                    {
                        "Search"
                    }
                    else
                    {
                        "Stop searching"
                    }
                }


                onPressed: {
                    if (bleController.searchDevicesIconVisible === false)
                    {
                        bleController.searchForBLEDevices()
                        deviceSelected = false
                    }
                    else
                    {
                        bleController.stopSearchForBLEDevices()
                    }
                }
            }

            RoundButton {

                Layout.preferredWidth: windowSearchBLE.width / 3
                Layout.alignment: Qt.AlignCenter
                text: "Connect"
                enabled: deviceSelected
            }
        }
    }
}
