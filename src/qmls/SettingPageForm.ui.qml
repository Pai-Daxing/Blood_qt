import QtQuick 2.4
import "customCtrls"
import QtQuick.Controls 2.2

Item {
    width: 1280
    height: 6000

    property alias title_text: title_text
    property alias btnMaintian: btnMaintian

    //mainSetting
    property alias mainSetting: mainSetting
    property alias btnParam: btnParam
    property alias btnLog: btnLog
    property alias btnSetTime: btnSetTime
    property alias btnVersion: btnVersion
    property alias btnSca: btnSca
    //sysconfig
    property alias sysconfigView: sysconfigView
    property alias btnexit_config: btnexit_config
    property alias switch_Bcode: switch_Bcode
    property alias switch_Ccode: switch_Ccode
    property alias switch_Acode: switch_Acode
    property alias switch_Pcode: switch_Pcode
    property alias switch_Ucode: switch_Ucode

    //Maintain
    property alias mainTain: mainTain
//    property alias btnScaled: btnScaled
    property alias btnRestore: btnRestore
    property alias btnOK_Maintain: btnOK_Maintain
    property alias btnNetSet: btnNetSet
    property alias btnDebug: btnDebug
    property alias btnSysParam: btnSysParam
    property alias btnChangedPasswd: btnChangedPasswd

    //verion
    property alias versionView: versionView
    property alias btnQuitVer: btnQuitVer
    property alias textInput_third: textInput_third
    property alias textInput_second: textInput_second
    property alias ma_number: ma_number

    //Wifi
    property alias btnWifi: btnWifi
    property alias wifiView: wifiView
    property alias btnQuitWifi: btnQuitWifi
    property alias scan: scan
    property alias comboBox_wifi: comboBox_wifi
    property alias connect: connect
    property alias input_name: input_name
    property alias input_password: input_password
    property alias connectOK: connectOK

    property alias input_ip: input_ip
    property alias input_netmask: input_netmask

    //bootself
    property alias btnBootSelf: btnBootSelf
    property alias bootselfView: bootselfView
    property alias bootselfexit: bootselfexit
    property alias bootself: bootself
    property alias bootselfok: bootselfok

    property alias setselfCoverOpen: setselfCoverOpen
    property alias setselfCoverClose: setselfCoverClose
    property alias setselfAirDs: setselfAirDs
    property alias setselfVlvs: setselfVlvs
    property alias setselfPumps: setselfPumps
    property alias setselfline: setselfline
    property alias setselfCF: setselfCF
    property alias setselfDPM: setselfDPM
    property alias setselfScales: setselfScales
    property alias setselfleak: setselfleak

    property alias setselfTest_err: setselfTest_err
    property alias setselfTest_animated: setselfTest_animated
        property alias setretrySelfT: setretrySelfT
    property alias setselfTest: setselfTest
    property alias setselfTestexit: setselfTestexit

    property alias btnsysconfig: btnsysconfig


    Text {
        id: title_text
        x: 575
        y: 6
        width: 130
        height: 37
        color: "#ffffff"
        text: qsTr("设置")
        verticalAlignment: Text.AlignTop
        font.bold: true
        font.family: "Tahoma"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 24
    }
    Item {
        id: mainSetting
        x: 5
        y: 44
        width: 1270
        height: 700
        visible: true

        CustIconButton {
            id: btnLog
            x: 188
            y: 36
            width: 280
            height: 180
            text: "日志"
            btnIcon.source: "/res/pics/log.png"
        }

        CustIconButton {
            id: btnParam
            x: 492
            y: 36
            width: 280
            height: 180
            text: "参数设置"
            btnIcon.source: "/res/pics/setting.png"
        }

        CustIconButton {
            id: btnMaintian
            x: 798
            y: 236
            width: 280
            height: 180
            text: "维护"
            btnIcon.source: "/res/pics/maintain.png"
        }

//        CustIconComboBox {
//            id: comboBox_Lang
//            x: 798
//            y: 460
//            width: 280
//            height: 126

//            model: [qsTr("中文"), "English"]
//        }
        CustIconButton {
            id: btnSca
            x: 798
            y: 436
            width: 280
            height: 126
            text: "校准"
            btnIcon.source: "/res/pics/sca.png"
        }

        CustIconButton {
            id: btnVersion
            x: 492
            y: 436
            width: 280
            height: 126
            text: "关于本机"
            btnIcon.source: "/res/pics/version.png"
        //    enabled: false
        }

        CustIconButton {
            id: btnSetTime
            x: 188
            y: 436
            width: 280
            height: 126
            text: "设置时间"
            btnIcon.source: "/res/pics/timer.png"
        }

        CustIconButton {
            id: btnWifi
            x: 188
            y: 236
            width: 280
            height: 180
            text: "无线网络与连接"
            btnIcon.source: "/res/pics/wifi.png"
        }

        CustIconButton {
            id: btnBootSelf
            x: 495
            y: 236
            width: 280
            height: 180
            text: "本机自检"
            btnIcon.source: "/res/pics/bootself.png"
        }

        CustIconButton {
            id: btnsysconfig
            x: 798
            y: 36
            width: 280
            height: 180
            text: "系统配置"
            btnIcon.source: "/res/pics/sysconfig.png"
        }
    }

    Item {
        id: sysconfigView
        x: 5
        y: 755
        width: 1270
        height: 700
        visible: false

        GroupBox {
            x: 90
            y: 89
            width: 350
            height: 500

            Frame {
                anchors.bottomMargin: 13
                anchors.topMargin: 15
                anchors.fill: parent

                background: Rectangle {
                    anchors.fill: parent
                    color: "#565656"
                }
                Column{
                    x: 9
                    y: 10
                    spacing: 22

                    MySwitch {
                        id: switch_Bcode
                        text: "献血码"
                        width: 274
                        height: 60
                        checked: true
                    }

                    MySwitch {
                        id: switch_Ccode
                        text: "耗材条码"
                        width: 274
                        height: 60
                        checked: true
                    }


                    MySwitch {
                        id: switch_Acode
                        text: "抗凝剂条码"
                        width: 274
                        height: 60
                        checked: true
                    }

                    MySwitch {
                        id: switch_Pcode
                        text: "保养液条码"
                        width: 274
                        height: 60
                        checked: true
                    }

                    MySwitch {
                        id: switch_Ucode
                        text: "操作者条码"
                        width: 274
                        height: 60
                        checked: true
                    }
                }
            }
        }

        CustomButton {
            id: btnexit_config
            x: 1100
            y: 620
            width: 100
            height: 80
            text: "退出"

            bgColor: "#404040"
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }

    }

    Item {
        id: mainTain
        x: 5
        y: 1455
        width: 1270
        height: 700
        visible: false
        CustomButton {
            id: btnNetSet
            x: 766
            y: 193
            width: 180
            height: 121
            text: "网络设置"
        }

        CustomButton {
            id: btnScaled
            x: 542
            y: 193
            width: 180
            height: 120
      //      text: "电子秤校准"
            visible: true
        }

        CustomButton {
            id: btnSysParam
            x: 322
            y: 347
            width: 180
            height: 120
            text: "系统参数"
        }

        CustomButton {
            id: btnRestore
            x: 766
            y: 347
            width: 180
            height: 120
            text: "恢复默认参数"
        }

        CustomButton {
            id: btnOK_Maintain
            x: 1100
            y: 620
            width: 100
            height: 80
            text: "退出"

            bgColor: "#404040"
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }

        CustomButton {
            id: btnDebug
            x: 322
            y: 193
            width: 180
            height: 120
            text: "调试"
        }

        CustomButton {
            id: btnChangedPasswd
            x: 542
            y: 347
            width: 180
            height: 120
            text: "密码重置"
        }
    }
    Item {
        id:versionView
        x: 5
        y: 2168
        width: 1270
        height: 700
        visible: false

        Row {
            x: 526
            y: 158
            width: 353
            height: 40
            spacing: 10

            MyLabel {
                id: lang
                width: 110
                text: qsTr("语言设置:")
                font.bold: false
            }

            ComboBox {
                id: comboBox_lang
                width: 182
                height: 40
                font.wordSpacing: 2
                spacing: 10
                font.pixelSize: 18
                font.bold: true
                font.family: "Tahoma"
                textRole: qsTr("")
                currentIndex: 0

                model: ["中文", "英文"]
            }


        }

        Row {
            x: 526
            y: 234
            width: 353
            height: 40
            spacing: 10

            MyLabel {
                id: machine_number
                width: 110
                text: qsTr("本机编号:")
                font.bold: false
            }


            TextInput {
                id: ma_number
                width: 200
                height: 40
                color: "#ffffff"
                text: qsTr("BND_BCP_01")
                font.bold: true
                font.family: "Tahoma"
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 22
                horizontalAlignment: Text.AlignHCenter
                readOnly: true
            }
        }
        Row {
            x: 526
            y: 307
            width: 353
            height: 40
            spacing: 10

            MyLabel {
                id: textVer1
                width: 110
                text: qsTr("主版本号:")
                font.bold: false
            }


            TextInput {
                id: textInput_first
                width: 120
                height: 40
                color: "#ffffff"
                //    text: qsTr("0")
                text:textInput_second.text+textInput_third.text
                font.bold: true
                font.family: "Tahoma"
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 22
                horizontalAlignment: Text.AlignHCenter
                readOnly: true
            }
        }
        Row {
            x: 526
            y: 380
            width: 353
            height: 40
            spacing: 10

            MyLabel {
                id: textVer2
                width: 110
                text: qsTr("上位机版本号:")
                font.bold: false
            }


            TextInput {
                id: textInput_second
                width: 90
                height: 40
                color: "#ffffff"
                text: qsTr("V_10")
                font.bold: true
                font.family: "Tahoma"
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 22
                horizontalAlignment: Text.AlignHCenter
                readOnly: true
            }
        }
//        Row {
//            x: 526
//            y: 401
//            width: 353
//            height: 40
//            spacing: 10

            MyLabel {
                id: textVer3
                x: 526
                y: 450
                width: 110
                height: 40
                text: qsTr("下位机版本号:")
                font.bold: false
            }

            MyLabel {
                id: v
                x: 647
                y: 450
                width: 71
                height: 40
                text: qsTr("V_")
                font.bold: true
                font.family: "Tahoma"
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 22
                horizontalAlignment: Text.AlignHCenter
           //     readOnly: true
            }


            TextInput {
                id: textInput_third
                x: 667
                y: 450
                width: 90
                height: 40
                color: "#ffffff"
                text: "0"
                font.bold: true
                font.family: "Tahoma"
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 22
                horizontalAlignment: Text.AlignHCenter
                readOnly: true
            }
 //       }



        CustomButton {
            id: btnQuitVer
            x: 1100
            y: 620
            width: 100
            height: 80
            text: "退出"

            bgColor: "#404040"
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }

    }

    Item {
        id:wifiView
        x: 5
        y: 2874
        width: 1270
        height: 700
        visible: false
        GroupBox {

            x: 131
            y: 120
            width: 450
            height: 455
            label: MyLabel {
                font.bold: false
                horizontalAlignment: Text.AlignLeft
                text: qsTr("wifi设置")
            }

            Frame {
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.fill: parent
        ChooseButton {
            //  anchors.centerIn: parent
            id: scan    //扫描
            x:252
            y:21
            width:150
            height:50
            text: "扫描"
        }

//        Button {
//            //  anchors.centerIn: parent
//            id: connect    //连接
//            x:296
//            y:289
//            width:78
//            height:36
//            Text {
//                anchors.centerIn: parent
//                font.family: "Microsoft Yahei"
//                font.bold: true
//                color: "#0f748b"
//                text: "连接"
//            }
//        }

        ChooseButton{
            id: connect    //连接
            x:252
            y:287
            width:150
            height:50
            text: "连接"
        }

        ComboBox {
            id: comboBox_wifi
            x: 10
            y: 25
            width: 230
            height: 41
            model:""
        }

        MyLabel {
            x: 24
            y: 212
            width: 100
            text: qsTr("密码:")
            font.bold: false
        }

        TextField{
            id: input_password
            x: 130
            y: 212

            font.family: "微软雅黑"

            width: 210
            height: 40
            color: "#404040"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.pixelSize: 18

//               inputMask: '000.000.000.000'
        }

        MyLabel {
            x: 24
            y: 134
            width: 100
            text: qsTr("用户名:")
            font.bold: false
        }

        TextField{
            id: input_name
            x: 130
            y: 134
            text: comboBox_wifi.currentText

            font.family: "微软雅黑"

            width: 210
            height: 40
            color: "#404040"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.pixelSize: 18

//                inputMask: '000.000.000.000'
        }
            }
        }
        GroupBox {

            x: 696
            y: 120
            width: 450
            height: 455
            label: MyLabel {
                font.bold: false
                horizontalAlignment: Text.AlignLeft
                text: qsTr("网络信息")
            }

            Frame {
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.fill: parent
        Row {
            x: 30
            y: 25
            width: 322
            height: 40
            spacing: 10

            MyLabel {
                width: 100
                text: qsTr("本机名:")
                font.bold: false
            }
            TextField{
                id: input_ip

                font.family: "微软雅黑"

                width: 210
                height: 40
                color: "#404040"
                text: qsTr("0.0.0.0")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 18

//                inputMask: '000.000.000.000'
            }


        }

        Row {
            x: 30
            y: 125
            width: 322
            height: 40
            spacing: 10

            MyLabel {
                width: 100
                text: qsTr("ip地址:")
                font.bold: false
            }
            TextField{
                id: input_netmask

                font.family: "微软雅黑"

                width: 210
                height: 40
                color: "#404040"
                text: qsTr("0.0.0.0")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 18

            }


        }

            }
        }

        Popup{
            id:connectOK
            width: 300
            height: 100
            x: 535
            y: 300
            modal: true
            focus: true
            visible: false

            Rectangle
            {
                //            width: 400
                //            height: 300
                anchors.fill: parent
                anchors.centerIn: parent
                radius: 7
                Text {
                    id: text1
                    font.pixelSize: 24
                    text: qsTr("设置成功!请重启保证连接!")
                }
            }
        }

//        CustomButton {
//            id: btnOK_wifi
//            x: 950
//            y: 620
//            width: 100
//            height: 80
//            text: "确认"

//            bgColor: "#404040"
//            bHasIcon: true
//            btnIcon.source: "/res/pics/save.png"
//        }

        CustomButton {
            id: btnQuitWifi
            x: 1100
            y: 620
            width: 100
            height: 80
            text: "退出"

            bgColor: "#404040"
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }

    }

    Item {
        id:bootselfView
        x: 5
        y: 3580
        width: 1270
        height: 700
        visible: false

        MyLabel {
            id: bootself_info
            x: 485
            y: 121
            width: 300
            height: 99
            horizontalAlignment: Text.AlignHCenter
            color: "red"
            text:"注意:开机自检前.请保证耗材未安装.离心机盖关闭."
            visible: true

        }

        CustomButton {
            id: bootself
            x: 515
            y: 226
            width: 240
            height: 240
            bgColor: "#404040"
            text: "本机自检"
            btnIcon.source: "/res/pics/start.png"
            btnIcon.sourceSize.width: 200
            btnIcon.sourceSize.height: 200
            bHasIcon: true
        }



        CustomButton {
            id: bootselfexit
            x: 1100
            y: 620
            width: 100
            height: 80
            text: "退出"

            bgColor: "#404040"
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }
}

    Item {
        id: setselfTest
        x: 5
        y: 4286
        width: 1270
        height: 700
//////////////////线框////////////////////////////////
        Rectangle{
            x: 12
            y: 324//模拟线段
            width:540 //长
            height:2  //高
           color:"#ffffff" //颜色
           rotation:90 //顺时针旋转的角度
        }

        Rectangle{
            x: 281
            y: 55//模拟线段
            width:80 //长
            height:2  //高
           color:"#ffffff" //颜色
        }

        Rectangle{
            x: 281
            y: 115//模拟线段
            width:80 //长
            height:2  //高
           color:"#ffffff" //颜色
        }

        Rectangle{
            x: 281
            y: 175//模拟线段
            width:80 //长
            height:2  //高
           color:"#ffffff" //颜色
        }

        Rectangle{
            x: 281
            y: 235//模拟线段
            width:80 //长
            height:2  //高
           color:"#ffffff" //颜色
        }

        Rectangle{
            x: 281
            y: 295//模拟线段
            width:80 //长
            height:2  //高
           color:"#ffffff" //颜色
        }

        Rectangle{
            x: 281
            y: 355//模拟线段
            width:80 //长
            height:2  //高
           color:"#ffffff" //颜色
        }

        Rectangle{
            x: 281
            y: 415//模拟线段
            width:80 //长
            height:2  //高
           color:"#ffffff" //颜色
        }

        Rectangle{
            x: 281
            y: 475//模拟线段
            width:80 //长
            height:2  //高
           color:"#ffffff" //颜色
        }

        Rectangle{
            x: 281
            y: 535//模拟线段
            width:80 //长
            height:2  //高
           color:"#ffffff" //颜色
        }

        Rectangle{
            x: 281
            y: 595//模拟线段
            width:80 //长
            height:2  //高
           color:"#ffffff" //颜色
        }
/////////////////////////////////////////////////////
        MyLabel {
            id: setselfCoverOpen
            x: 361
            y: 32
            width: 365
            height: 49
            horizontalAlignment: Text.AlignLeft
            text:"请打开盖开关"
        }

        MyLabel {
            id: setselfCoverClose
            x: 361
            y: 92
            width: 365
            height: 49
            horizontalAlignment: Text.AlignLeft
            text : "请关闭盖开关"
        }

        MyLabel {
            id: setselfAirDs
            x: 361
            y: 152
            width: 365
            height: 49
            horizontalAlignment: Text.AlignLeft
            text : "空探自检"
        }

        MyLabel {
            id: setselfVlvs
            x: 361
            y: 212
            width: 365
            height: 49
            horizontalAlignment: Text.AlignLeft
            text : "阀门自检"
        }

        MyLabel {
            id: setselfPumps
            x: 361
            y: 272
            width: 365
            height: 49
            horizontalAlignment: Text.AlignLeft
            text : "泵自检"
        }

        MyLabel {
            id: setselfline
            x: 361
            y: 332
            width: 365
            height: 49
            horizontalAlignment: Text.AlignLeft
            text : "红细胞探测器自检"
        }

        MyLabel {
            id: setselfCF
            x: 361
            y: 392
            width: 365
            height: 49
            horizontalAlignment: Text.AlignLeft
            text : "离心机自检"
        }

        MyLabel {
            id: setselfDPM
            x: 361
            y: 452
            width: 365
            height: 49
            horizontalAlignment: Text.AlignLeft
            text : "DPM自检"
        }

        MyLabel {
            id: setselfScales
            x: 361
            y: 512
            width: 365
            height: 49
            horizontalAlignment: Text.AlignLeft
            text : "电子秤自检"
        }

        MyLabel {
            id: setselfleak
            x: 361
            y: 572
            width: 365
            height: 49
            horizontalAlignment: Text.AlignLeft
            text : "漏液自检"
        }


        MyLabel {
            id: setselfTest_err
            x: 781
            y: 124
            width: 458
            height: 141
            horizontalAlignment: Text.AlignLeft
            color: "red"
            text: ""
            font.pointSize: 20
        }

        CustomButton {
            id: bootselfok
            x: 857
            y: 94
            width: 240
            height: 240
            bgColor: "#404040"
            text:"自检成功"
            btnIcon.source: "/res/pics/succeed.png"
            btnIcon.sourceSize.width: 200
            btnIcon.sourceSize.height: 200
            bHasIcon: true
            visible: false
        }

        CustomButton {
            id: setretrySelfT
            x: 919
            y: 355
            //            x:10
//            y:10
            width: 130
            height: 130
            visible: false
            text: "重试"
        }

        AnimatedImage {
            id: setselfTest_animated
            x: 791
            y: 78
            width: 373
            height: 271
            visible: true

            source: "/res/pics/open_cover.gif"
        }

        CustomButton {
            id: setselfTestexit
            x: 1100
            y: 620
            width: 100
            height: 80
            text: "退出"

            bgColor: "#404040"
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }
    }
}
