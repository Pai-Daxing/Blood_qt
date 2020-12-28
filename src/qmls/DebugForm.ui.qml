import QtQuick 2.4
import "customCtrls"
import QtQuick.Controls 2.2

Item {
    width: 1270
    height: 700
    property alias btnQuitDebug: btnQuitDebug
    property alias comboBox_PresvV: comboBox_PresvV
    property alias comboBox_DPM: comboBox_DPM
    property alias comboBox_plsmV: comboBox_plsmV
    property alias comboBox_leak: comboBox_leak
    property alias comboBox_cover: comboBox_cover
    property alias comboBox_bldairD: comboBox_bldairD
    property alias comboBox_ACDairD: comboBox_ACDairD
    property alias comboBox_PrsvairD: comboBox_PrsvairD
    //    property alias comboBox_ACDV: comboBox_ACDV
    property alias comboBox_RBCV: comboBox_RBCV
    property alias comboBox_bldV: comboBox_bldV
    property alias comboBox_NaClV: comboBox_NaClV
    property alias comboBox_wasteV: comboBox_wasteV
    property alias comboBox_lineSensor: comboBox_lineSensor
    property alias textInput_dpm: textInput_dpm
    property alias textInput_lineD: textInput_lineD
    property alias textInput_scale1: textInput_scale1
    property alias textInput_scale2: textInput_scale2
    property alias textInput_bldP: textInput_bldP
    property alias textInput_ACDP: textInput_ACDP
    property alias textInput_PresvP: textInput_PresvP
    property alias textInput_centri: textInput_centri

    property alias switch_centri: switch_centri
    property alias switch_bldVlv: switch_bldVlv
    property alias switch_RBCVlv: switch_RBCVlv
    property alias switch_plasmaVlv: switch_plasmaVlv
    property alias switch_wasteVlv: switch_wasteVlv
    property alias switch_prsvVlv: switch_prsvVlv
    property alias switch_naclVlv: switch_naclVlv
    property alias switch_BP: switch_BP
    property alias switch_AP: switch_AP
    property alias switch_NP: switch_NP
    property alias switch_BP_Dir: switch_BP_Dir

    property alias input_BP_Speed: input_BP_Speed
    property alias input_AP_Speed: input_AP_Speed
    property alias input_NP_Speed: input_NP_Speed
    Column {
        id: column1
        x: 70
        y: 70
        width: 330
        height: 590
        spacing: 8
        Row {
            spacing: 10
            MyLabel {
                id: text2
                text: qsTr("压力监视器")
                font.bold: false
            }

            TextInput {
                id: textInput_dpm
                width: 90
                height: 40
                color: "#ffffff"
                text: qsTr("0")
                readOnly: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                font.family: "Tahoma"
                font.pixelSize: 22
            }

            MyLabel {
                id: text3
                width: 65
                text: qsTr("kpa")
                font.bold: false
            }
        }

        Row {
            id: row1
            spacing: 10

            MyLabel {
                id: text4
                width: 110
                text: qsTr("管路探测器")
                font.bold: false
            }

            TextInput {
                id: textInput_lineD
                width: 90
                height: 40
                color: "#ffffff"
                text: qsTr("0")
                readOnly: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                font.family: "Tahoma"
                font.pixelSize: 22
            }

            MyLabel {
                id: text5
                width: 45
                text: qsTr("mV")
                font.bold: false
            }
        }

        Row {
            id: row3
            spacing: 10

            MyLabel {
                id: text7
                width: 110
                text: qsTr("血浆重量监测")
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
                id: text8
                width: 45
                text: qsTr("g")
                font.bold: false
            }
        }
        Row {
            spacing: 10
            MyLabel {
                id: text11
                text: qsTr("漏液检测器")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_leak
                width: 146
                height: 40
                enabled: false
                model: [qsTr("未漏液"), qsTr("漏液")]
            }
        }

        Row {
            spacing: 10

            MyLabel {
                id: text12
                width: 110
                text: qsTr("离心机盖")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_cover
                width: 146
                height: 40
                enabled: false
                model: [qsTr("未关闭"), qsTr("关闭")]
            }
        }
        Row {
            spacing: 10
            MyLabel {
                id: text13
                width: 110
                text: qsTr("血液空探")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_bldairD
                width: 146
                height: 40
                enabled: false
                model: [qsTr("空气"), qsTr("液体")]
            }
        }

        Row {
            spacing: 10

            //            x: 92
            //            y: 411
            MyLabel {
                id: text14
                width: 110
                text: qsTr("抗凝空探")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_ACDairD
                width: 146
                height: 40
                enabled: false
                model: [qsTr("空气"), qsTr("液体")]
            }
        }
        Row {
            spacing: 10

            //            x: 92
            //            y: 411
            MyLabel {
                id: text16
                width: 110
                text: qsTr("保养液空探")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_PrsvairD
                width: 146
                height: 40
                enabled: false
                model: [qsTr("空气"), qsTr("液体")]
            }
        }
        Row {
            spacing: 10

            //            x: 92
            //            y: 473
            MyLabel {
                id: text15
                width: 110
                text: qsTr("保养液阀")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_PresvV
                width: 146
                height: 40
                enabled: false
                model: [qsTr("关"), qsTr("开")]
            }
        }

        //        Row {
        //            spacing: 10

        //            //            x: 92
        //            //            y: 532
        //            MyLabel {
        //                id: text16
        //                width: 110
        //                text: qsTr("抗凝剂阀")
        //                font.bold: false
        //            }

        //            CustomComboBox {
        //                id: comboBox_ACDV
        //                width: 146
        //                height: 40
        //                enabled: false
        //                model: [qsTr("关"), qsTr("开")]
        //            }
        //        }
        Row {
            spacing: 10

            //            x: 92
            //            y: 589
            MyLabel {
                id: text17
                width: 110
                text: qsTr("红细胞阀")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_RBCV
                width: 146
                height: 40
                enabled: false
                model: [qsTr("关"), qsTr("开")]
            }
        }
    }

    CustomButton {
        id: btnQuitDebug
        x: 1100
        y: 620
        width: 100
        height: 80
        text: "退出"

        bgColor: "#404040"
        bHasIcon: true
        btnIcon.source: "/res/pics/exit.png"
    }

    GroupBox {

        x: 756
        y: 8
        width: 477
        height: 606
        label: MyLabel {
            font.bold: false
            horizontalAlignment: Text.AlignLeft
            text: qsTr("操作")
        }

        Frame {
            anchors.fill: parent

            background: Rectangle {
                anchors.fill: parent
                color: "#565656"
            }

            Column {
                width: 162
                height: 460
                spacing: 20
                MySwitch {
                    id: switch_centri

                    height: 60
                    text: qsTr("离心机")
                }

                MySwitch {
                    id: switch_bldVlv

                    height: 55
                    text: qsTr("血液阀")
                }

                MySwitch {
                    id: switch_RBCVlv

                    height: 55
                    text: qsTr("悬红阀")
                }

                MySwitch {
                    id: switch_plasmaVlv

                    height: 55
                    text: qsTr("血浆阀")
                }
                MySwitch {
                    id: switch_wasteVlv

                    height: 55
                    text: qsTr("废液阀")
                }
                MySwitch {
                    id: switch_prsvVlv

                    height: 55
                    text: qsTr("保养液阀")
                }
                MySwitch {
                    id: switch_naclVlv

                    height: 55
                    text: qsTr("盐水阀")
                }
            }
            Column {
                x: 175
                y: 0
                width: 189
                height: 460
                spacing: 25

                Row {
                    spacing: 10

                    MyLabel {
                        width: 50
                        text: qsTr("血泵")
                        font.bold: false
                    }
                    MyTextField {
                        id: input_BP_Speed
                        width: 100
                    }
                }
                Row {
                    spacing: 10

                    MyLabel {
                        width: 50
                        text: qsTr("AC泵")
                        font.bold: false
                    }
                    MyTextField {
                        id: input_AP_Speed
                        width: 100
                    }
                }
                Row {
                    spacing: 10

                    MyLabel {
                        width: 50
                        text: qsTr("N泵")
                        font.bold: false
                    }
                    MyTextField {
                        id: input_NP_Speed
                        width: 100
                    }
                }

                MySwitch {
                    id: switch_BP

                    height: 60
                    text: qsTr("血泵启动")
                }

                MySwitch {
                    id: switch_BP_Dir

                    height: 60
                    text: qsTr("顺时针")
                }

                MySwitch {
                    id: switch_AP

                    height: 60
                    text: qsTr("AC泵启动")
                }

                MySwitch {
                    id: switch_NP

                    height: 60
                    text: qsTr("N泵启动")
                }
            }
        }
    }

    Column {
        id: column2
        x: 420
        y: 70
        width: 330
        height: 590
        spacing: 5

        Row {
            id: row2
            spacing: 10

            MyLabel {
                id: text6
                width: 110
                text: qsTr("DPM")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_DPM
                width: 146
                height: 40
                enabled: false

                model: [qsTr("未安装"), qsTr("已安装")]
            }
        }
        Row {
            spacing: 10

            MyLabel {
                id: text28
                width: 110
                text: qsTr("红细胞")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_lineSensor
                width: 146
                height: 40
                enabled: false
                model: [qsTr("未发现红细胞"), qsTr("发现红细胞")]
            }
        }
        Row {
            spacing: 10

            MyLabel {
                id: text9
                width: 110
                text: qsTr("支杆重量监测")
                font.bold: false
            }

            TextInput {
                id: textInput_scale2
                width: 90
                height: 40
                color: "#ffffff"
                text: qsTr("0")
                font.bold: true
                font.family: "Tahoma"
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 22
                horizontalAlignment: Text.AlignHCenter
                readOnly: true
            }

            MyLabel {
                id: text10
                width: 50
                text: qsTr("g")
                font.bold: false
            }
        }

        Row {
            spacing: 10

            MyLabel {
                width: 110
                text: qsTr("血泵")
                font.bold: false
            }

            TextInput {
                id: textInput_bldP
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
                id: text19
                width: 50
                text: qsTr("rpm")
                font.bold: false
            }
        }
        Row {
            spacing: 10

            //            x: 470
            //            y: 370
            MyLabel {
                id: text22
                width: 110
                text: qsTr("离心机")
                font.bold: false
            }

            TextInput {
                id: textInput_centri
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
                id: text23
                width: 50
                text: qsTr("rpm")
                font.bold: false
            }
        }

        Row {
            spacing: 10

            MyLabel {
                id: text29
                width: 110
                text: qsTr("保养液泵")
                font.bold: false
            }

            TextInput {
                id: textInput_PresvP
                width: 90
                height: 40
                color: "#ffffff"
                text: qsTr("0")
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 22
                readOnly: true
                font.family: "Tahoma"
            }

            MyLabel {
                id: text30
                width: 50
                text: qsTr("rpm")
                font.bold: false
            }
        }

        Row {
            spacing: 10

            MyLabel {
                id: text20
                width: 110
                text: qsTr("抗凝泵")
                font.bold: false
            }

            TextInput {
                id: textInput_ACDP
                width: 90
                height: 40
                color: "#ffffff"
                text: qsTr("0")
                font.bold: true
                font.family: "Tahoma"
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 22
                horizontalAlignment: Text.AlignHCenter
                readOnly: true
            }

            MyLabel {
                id: text21
                width: 50
                text: qsTr("rpm")
                font.bold: false
            }
        }

        Row {
            spacing: 10

            MyLabel {
                id: text27
                width: 110
                text: qsTr("废液阀")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_wasteV
                width: 146
                height: 40
                enabled: false
                model: [qsTr("关"), qsTr("开")]
            }
        }

        Row {
            spacing: 10

            MyLabel {
                id: text26
                width: 110
                text: qsTr("盐水阀")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_NaClV
                width: 146
                height: 40
                enabled: false
                model: [qsTr("关"), qsTr("开")]
            }
        }

        Row {
            spacing: 10

            MyLabel {
                id: text25
                width: 110
                text: qsTr("血浆阀")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_plsmV
                width: 146
                height: 40
                enabled: false
                model: [qsTr("关"), qsTr("开")]
            }
        }

        Row {
            spacing: 10

            MyLabel {
                id: text24
                width: 110
                text: qsTr("血液阀")
                font.bold: false
            }

            CustomComboBox {
                id: comboBox_bldV
                width: 146
                height: 40
                enabled: false
                model: [qsTr("关"), qsTr("开")]
            }
        }
    }
}
