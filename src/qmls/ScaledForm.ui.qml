import QtQuick 2.4
import "customCtrls"
import QtQuick.Controls 2.2

Item {
    width: 1270
    height: 700

    property alias btnQuitScaled: btnQuitScaled
//    property alias btnSaveScaled: btnSaveScaled
//    property alias one_Ok: one_Ok
    property alias two_Ok: two_Ok
    property alias input_one: input_one
//    property alias input_two: input_two
    property alias input_three: input_three
//    property alias input_four: input_four
//    property alias three_Ok: three_Ok
    property alias four_Ok: four_Ok
    property alias textInput_scale1: textInput_scale1
    property alias textInput_dpm: textInput_dpm

    GroupBox {

        x: 120
        y: 107
        width: 450
        height: 350
        label: MyLabel {
            font.bold: false
            horizontalAlignment: Text.AlignLeft
            text: qsTr("气压")
        }

        Frame {
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent

                ChooseButton{
                    id: two_Ok
                    x: 252
                    y: 206
                    width: 150
                    height: 50
                    text: "校准"
                }


            Row {
                x: 167
                y: 0
                width: 198
                height: 40
                spacing: 10

                MyLabel {
                    width: 50
                    text: "请输入气压值"
                    font.bold: false
                }
                MyTextField {
                    id: input_one
                    width: 90
                    text: "0"
                }

                MyLabel {
                    id: text1
                    width: 50
                    text: qsTr("Kpa")
                    font.bold: false
                }


            }

            Row {
                x: 96
                y: 112
                width: 269
                height: 40
                spacing: 10

                MyLabel {
                    id: text9
                    width: 110
                    text: qsTr("实时气压检测")
                    font.bold: false
                }

                TextInput {

                    id: textInput_dpm
                    width: 90
                    height: 40
                    color: "#ffffff"
                    text: qsTr("0")
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    font.family: "Tahoma"
                    font.pixelSize: 22
                    horizontalAlignment: Text.AlignHCenter
                    readOnly: true
                }

                MyLabel {
                    id: text10
                    width: 50
                    text: qsTr("Kpa")
                    font.bold: false
                }
            }

        }

    }
    GroupBox {

        x: 687
        y: 107
        width: 450
        height: 350
        label: MyLabel {
            font.bold: false
            horizontalAlignment: Text.AlignLeft
            text: qsTr("血浆秤")
        }

        Frame {
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent
                ChooseButton{
                    id: four_Ok
                    x: 252
                    y: 206
                    width: 150
                    height: 50
                    text: "校准"
                }


            Row {
                x: 167
                y: 0
                width: 198
                height: 40
                spacing: 10

                MyLabel {
                    width: 50
                    text: qsTr("请输入砝码重量")
                    font.bold: false
                }
                MyTextField {
                    id: input_three
                    width: 90
                    text: "0"
                }

                MyLabel {
                    id: text
                    width: 50
                    text: qsTr("g")
                    font.bold: false
                }


            }

            Row {
                x: 96
                y: 112
                width: 269
                height: 40
                spacing: 10

                MyLabel {
                    id: text91
                    width: 110
                    text: qsTr("实时重量监测")
                    font.bold: false
                }

                TextInput {
                    id: textInput_scale1
                    width: 90
                    height: 40
                    color: "#ffffff"
                    text: qsTr("0")
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    font.family: "Tahoma"
                    font.pixelSize: 22
                    horizontalAlignment: Text.AlignHCenter
                    readOnly: true
                }

                MyLabel {
                    id: text101
                    width: 50
                    text: qsTr("g")
                    font.bold: false
                }
            }

        }

    }

    CustomButton {
        id: btnQuitScaled
        x: 1100
        y: 620
        width: 100
        height: 80
        text: "退出"

        bgColor: "#404040"
        bHasIcon: true
        btnIcon.source: "/res/pics/exit.png"
    }


//    CustomButton {
//        id: btnSaveScaled
//        x: 950
//        y: 620
//        text: "保存"
//        width: 100
//        height: 80

//        bgColor: "#404040"
//        bHasIcon: true
//        btnIcon.source: "/res/pics/save.png"
//    }
}
