import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 1180
    height: 760
    visible: true
    title: "Smart Home Energy Monitoring"
    color: "#0f172a"

    property color cardColor: "#172033"
    property color softCardColor: "#1e293b"
    property color textColor: "#e5e7eb"
    property color mutedText: "#94a3b8"
    property color accentColor: "#38bdf8"
    property color dangerColor: "#fb7185"
    property color warningColor: "#facc15"
    property color successColor: "#34d399"

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#0f172a" }
            GradientStop { position: 1.0; color: "#111827" }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 22
        spacing: 16

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 2

                Text {
                    text: "Smart Home Energy Monitoring"
                    color: textColor
                    font.pixelSize: 28
                    font.bold: true
                }

                Text {
                    text: "Simulation Engine • Energy Tracking • Alert System"
                    color: mutedText
                    font.pixelSize: 14
                }
            }

            Rectangle {
                width: 150
                height: 42
                radius: 12
                color: backend.running ? "#064e3b" : "#3f1d1d"
                border.color: backend.running ? successColor : dangerColor

                Text {
                    anchors.centerIn: parent
                    text: backend.running ? "Đang mô phỏng" : "Đã dừng"
                    color: "white"
                    font.bold: true
                }
            }

            Button {
                text: backend.running ? "Tạm dừng" : "Chạy mô phỏng"
                onClicked: backend.toggleSimulation()
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            SummaryCard {
                title: "Thiết bị đang bật"
                value: backend.activeDevices + " / " + backend.totalDevices
                subtitle: "Tổng số thiết bị quản lý"
            }

            SummaryCard {
                title: "Công suất hiện tại"
                value: backend.totalCurrentPower.toFixed(0) + " W"
                subtitle: backend.totalCurrentPower > 5000 ? "Vượt ngưỡng an toàn" : "Trong giới hạn an toàn"
                highlight: backend.totalCurrentPower > 5000 ? dangerColor : accentColor
            }

            SummaryCard {
                title: "Điện năng đã dùng"
                value: backend.totalEnergyUsed.toFixed(2) + " kWh"
                subtitle: "Cập nhật theo tick mô phỏng"
            }

            SummaryCard {
                title: "Chi phí tạm tính"
                value: backend.totalCost.toFixed(0) + " đ"
                subtitle: backend.electricityPrice.toFixed(0) + " đ/kWh"
            }

            SummaryCard {
                title: "Cảnh báo"
                value: backend.warningDevices.toString()
                subtitle: "Thiết bị cần kiểm tra"
                highlight: backend.warningDevices > 0 ? warningColor : successColor
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 16

            Rectangle {
                Layout.preferredWidth: 520
                Layout.fillHeight: true
                radius: 18
                color: cardColor
                border.color: "#334155"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 12

                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            text: "Danh sách thiết bị"
                            color: textColor
                            font.pixelSize: 20
                            font.bold: true
                            Layout.fillWidth: true
                        }

                        Text {
                            text: backend.devices.length + " thiết bị"
                            color: mutedText
                            font.pixelSize: 13
                        }
                    }

                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true

                        ListView {
                            width: parent.width
                            model: backend.devices
                            spacing: 10

                            delegate: Rectangle {
                                width: ListView.view.width - 8
                                height: 86
                                radius: 14
                                color: modelData.isOn ? "#10382f" : softCardColor
                                border.color: modelData.isOn ? successColor : "#334155"

                                RowLayout {
                                    anchors.fill: parent
                                    anchors.margins: 12
                                    spacing: 12

                                    Rectangle {
                                        width: 44
                                        height: 44
                                        radius: 12
                                        color: modelData.isOn ? successColor : "#475569"

                                        Text {
                                            anchors.centerIn: parent
                                            text: modelData.type.substring(0, 1)
                                            color: "#0f172a"
                                            font.bold: true
                                            font.pixelSize: 18
                                        }
                                    }

                                    ColumnLayout {
                                        Layout.fillWidth: true
                                        spacing: 2

                                        Text {
                                            text: modelData.name
                                            color: textColor
                                            font.pixelSize: 15
                                            font.bold: true
                                            elide: Text.ElideRight
                                            Layout.fillWidth: true
                                        }

                                        Text {
                                            text: modelData.roomName + " • " + modelData.type
                                            color: mutedText
                                            font.pixelSize: 12
                                        }

                                        Text {
                                            text: "Công suất: " + modelData.currentPower.toFixed(0) + " W | Điện: " + modelData.totalConsumption.toFixed(2) + " kWh | Chạy: " + modelData.currentSessionHours.toFixed(1) + "h"
                                            color: mutedText
                                            font.pixelSize: 12
                                            elide: Text.ElideRight
                                            Layout.fillWidth: true
                                        }
                                    }

                                    Button {
                                        text: modelData.isOn ? "Tắt" : "Bật"
                                        Layout.preferredWidth: 72
                                        onClicked: backend.toggleDevice(modelData.id)
                                    }
                                }
                            }
                        }
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 16

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 330
                    radius: 18
                    color: cardColor
                    border.color: "#334155"

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 12

                        Text {
                            text: "Biểu đồ tiêu thụ 24 giờ gần nhất"
                            color: textColor
                            font.pixelSize: 20
                            font.bold: true
                        }

                        Text {
                            text: "Dữ liệu lấy từ EnergyHistory.hourlyConsumption, cập nhật mỗi 1 giờ mô phỏng."
                            color: mutedText
                            font.pixelSize: 12
                        }

                        Rectangle {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            radius: 12
                            color: "#0b1220"
                            border.color: "#1e293b"

                            Row {
                                id: chartRow
                                anchors.left: parent.left
                                anchors.right: parent.right
                                anchors.bottom: parent.bottom
                                anchors.top: parent.top
                                anchors.margins: 18
                                spacing: 4
                                layoutDirection: Qt.LeftToRight
                                clip: true

                                Repeater {
                                    model: backend.chartData

                                    Column {
                                        width: Math.max(14, (chartRow.width - 24 * 4) / 24)
                                        height: chartRow.height
                                        spacing: 4

                                        Item {
                                            width: parent.width
                                            height: parent.height - 24

                                            Rectangle {
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                anchors.bottom: parent.bottom
                                                width: parent.width * 0.72
                                                height: Math.max(3, Math.min(parent.height, modelData.value * 68))
                                                radius: 4
                                                color: modelData.value > 0 ? accentColor : "#334155"
                                            }
                                        }

                                        Text {
                                            width: parent.width
                                            text: modelData.value > 0 ? modelData.value.toFixed(1) : ""
                                            color: mutedText
                                            font.pixelSize: 9
                                            horizontalAlignment: Text.AlignHCenter
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 18
                    color: cardColor
                    border.color: "#334155"

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 10

                        RowLayout {
                            Layout.fillWidth: true

                            Text {
                                text: "Cảnh báo hệ thống"
                                color: textColor
                                font.pixelSize: 20
                                font.bold: true
                                Layout.fillWidth: true
                            }

                            Button {
                                text: "Xóa cảnh báo"
                                onClicked: backend.clearAlerts()
                            }
                        }

                        Text {
                            visible: backend.alerts.length === 0
                            text: "Chưa có cảnh báo. AlertSystem sẽ hiện cảnh báo khi quá tải hoặc thiết bị chạy quá lâu."
                            color: mutedText
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }

                        ScrollView {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            clip: true

                            ListView {
                                width: parent.width
                                model: backend.alerts
                                spacing: 8

                                delegate: Rectangle {
                                    width: ListView.view.width - 8
                                    height: 92
                                    radius: 14
                                    color: modelData.isCritical ? "#3f1d1d" : "#3d3412"
                                    border.color: modelData.isCritical ? dangerColor : warningColor

                                    ColumnLayout {
                                        anchors.fill: parent
                                        anchors.margins: 12
                                        spacing: 3

                                        RowLayout {
                                            Layout.fillWidth: true

                                            Text {
                                                text: modelData.isCritical ? "NGHIÊM TRỌNG" : "CẢNH BÁO"
                                                color: modelData.isCritical ? dangerColor : warningColor
                                                font.pixelSize: 11
                                                font.bold: true
                                            }

                                            Text {
                                                text: modelData.timestamp
                                                color: mutedText
                                                font.pixelSize: 11
                                                horizontalAlignment: Text.AlignRight
                                                Layout.fillWidth: true
                                            }
                                        }

                                        Text {
                                            text: modelData.title
                                            color: textColor
                                            font.pixelSize: 15
                                            font.bold: true
                                            elide: Text.ElideRight
                                            Layout.fillWidth: true
                                        }

                                        Text {
                                            text: modelData.message
                                            color: "#d1d5db"
                                            font.pixelSize: 12
                                            wrapMode: Text.WordWrap
                                            maximumLineCount: 2
                                            elide: Text.ElideRight
                                            Layout.fillWidth: true
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    component SummaryCard: Rectangle {
        property string title: ""
        property string value: ""
        property string subtitle: ""
        property color highlight: accentColor

        Layout.fillWidth: true
        Layout.preferredHeight: 112
        radius: 18
        color: cardColor
        border.color: "#334155"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 14
            spacing: 4

            Text {
                text: title
                color: mutedText
                font.pixelSize: 12
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Text {
                text: value
                color: highlight
                font.pixelSize: 23
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Text {
                text: subtitle
                color: mutedText
                font.pixelSize: 11
                elide: Text.ElideRight
                Layout.fillWidth: true
            }
        }
    }
}
