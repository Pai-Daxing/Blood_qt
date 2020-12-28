import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "customCtrls"

Item {
    width: 1280
    height: 5000
    property alias selfTest: selfTest
    property alias retrySafeT: retrySafeT
    property alias btnDraw: btnDraw
    property alias startDraw: startDraw
    property alias btnCfmACD: btnCfmACD
    property alias btnCfmLine: btnCfmLine

    property alias standBy: standBy
    property alias safeTest: safeTest
    property alias draw: draw
    property alias result: result

    property alias btnQuitself: btnQuitself


    //192.168.1.15
    //    property alias image: image
    property alias safeChk_img: safeChk_img
    property alias selfTest_msg: selfTest_msg
    property alias safeTest_err: safeTest_err
    property alias safeTest_msg: safeTest_msg
    property alias selfTest_animated: selfTest_animated

    property alias pumpSpeed: label_pumpSpeed
    property alias pumpSpeed2: label_pumpSpeed2
    property alias preserSpeed: label_preserSpeed
    property alias collectionVlm: label_collectionVlm


    property alias timeLen: label_timeLen
    //property alias acdVlm: label_ACDVlm
    //property alias naclVlm: label_NaClVlm
    property alias bldVlm: label_bldVlm
    property alias statusLabel: label_Status

    property alias textInput_dpm: textInput_dpm  //压力dpm
    property alias textInput_dpm_false: textInput_dpm_false

    property alias rbcVlm: rbcVlm
    property alias rbcVlmPgbar: rbcVlmPgbar
    property alias label_bldVlm: label_bldVlm
    property alias myLabel6: myLabel6
    property alias myLabel_rbc: myLabel_rbc
    property alias myLabel_rbc1: myLabel_rbc1

    property alias pgBar: pgBar

    property alias myLabel: myLabel

    property alias btnUpload: btnUpload
    property alias btnOK: btnOK
    property alias add: add
    property alias reduce: reduce
    property alias stop: stop
    property alias add1: add1
    property alias reduce1: reduce1
    property alias stop1: stop1
    property alias buttonfillfailed: buttonfillfailed
    property alias centrifugeSpeed1: centrifugeSpeed1
     property alias skip: skip

    property alias enrichment: enrichment
    property alias enriadd: enriadd
    property alias enrireduce: enrireduce
    property alias enristop: enristop
    property alias enrivlm: label_enrivlm
    property alias centrifugeSpeed: centrifugeSpeed
    property alias over: over

    property alias result_enrivlm: result_enrivlm
    property alias result_bldVlm: result_bldVlm
    property alias result_timeLen: result_timeLen

   // property alias label_donorCode: label_donorCode
   // property alias label_disposableCode: label_disposableCode
    //property alias label_ACDCode: label_ACDCode
    //property alias label_presvCode: label_presvCode
    //property alias label_operatorCode: label_operatorCode
    //property alias label_dpmVlm_e: label_dpmVlm_e
   // property alias label_plsmVlm_e: label_plsmVlm_e
    //property alias label_presvVlm1: label_presvVlm1
    //    property alias label_endTime: label_endTime
    //property alias label_ACDVlm1: label_ACDVlm1
    //    property alias label_NaClVlm1: label_NaClVlm1
    //property alias label_RBCVlm_e: label_RBCVlm_e
   // property alias label_statelabel: label_statelabel

    property alias blood_code: blood_code
    property alias consu_code: consu_code
    property alias idpageView: idpageView
    property alias anti_code: anti_code
    property alias maintenance_code: maintenance_code
    property alias btnQuitId: btnQuitId
//  property alias btnSaveId: btnSaveId
    property alias title_ID: title_ID
    property alias label_blood_code: label_blood_code
    property alias user_code: user_code
    property alias colu_code: colu_code


    MyColors {
        id: m_color
    }
    Item {
        id: selfTest
        x: 5
        y: 8
        width: 1270
        height: 723

        MyLabel {
            id: selfTest_msg
            x: 406
            y: 284
            width: 458
            height: 49
            horizontalAlignment: Text.AlignHCenter
            text: ""
        }






        AnimatedImage {
            id: selfTest_animated
            x: 170
            y: 212
            width: 230
            height: 300
            visible: false

            source: "/res/pics/open_cover.gif"
        }
    }

    Item {
        id: standBy
        x: 5
        y: 744
        width: 1270
        height: 680

        CustomButton {
            id: startDraw
            x: 515
            y: 226
            width: 240
            height: 240
            bgColor: "#404040"
            text: "开始"
            btnIcon.source: "/res/pics/start.png"
            btnIcon.sourceSize.width: 200
            btnIcon.sourceSize.height: 200
            bHasIcon: true
        }
    }

    Item {
        id: safeTest
        x: 5
        y: 1457
        width: 1270
        height: 680

        MyLabel {
            id: safeChk_msg
            x: 406
            y: 190
            width: 458
            height: 49
            horizontalAlignment: Text.AlignHCenter
            text: ""
        }

        MyLabel {
            id: safeTest_msg
            x: 406
            y: 106
            width: 458
            height: 49
            horizontalAlignment: Text.AlignHCenter
        }

        AnimatedImage {
            id: safeChk_img
            x: 410
            y: 190
            width: 450
            height: 300
            visible: false
            source: "qrc:/res/pics/filling.gif"
        }

        MyLabel {
            id: safeTest_err
            x: 406
            y: 296
            width: 458
            height: 152
            horizontalAlignment: Text.AlignHCenter
            color: "red"
            text: ""
        }

        CustomButton {
            id: retrySafeT
            x: 570
            y: 492
            width: 130
            height: 130
            visible: false
            text: "重试"
        }

        CustomButton {
            id: buttonfillfailed
            x: 570
            y: 492
            width: 130
            height: 130
            visible: false
            text: "冲液失败"
        }
        CustomButton {
            id: btnDraw
            text: "确认"
            visible: false
            x: 980
            y: 620
            width: 100
            height: 80

            bgColor: "#404040"
            bHasIcon: true
            btnIcon.source: "/res/pics/save.png"
        }
        CustomButton {
            id: btnCfmACD
            text: "确认"
            visible: false
            x: 980
            y: 620
            width: 100
            height: 80

            bgColor: "#404040"
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }

        CustomButton {
            id: btnCfmLine
            text: "确认"
            visible: false
            x: 980
            y: 620
            width: 100
            height: 80

            bgColor: "#404040"
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }

        CustomButton {
            id: btnQuitself
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
        id: draw
        x: 5
        y: 2159
        width: 1280
        height: 700

        Rectangle {
            anchors.fill: parent
            color: m_color.bg
            anchors.rightMargin: 0
            anchors.bottomMargin: -36
            anchors.leftMargin: 0
            anchors.topMargin: 0

            MyLabel {
                id: label_Status
                x: 547
                y: 64
                width: 176
                height: 51
                text: "浓缩设置"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 48
                font.bold: false
            }

            Row {
                x: 209
                y: 376
                spacing: 20

                MyLabel {
                    id: myLabel3
                    font.bold: false
                    font.pixelSize: 36
                    text: "泵1速度"
                    horizontalAlignment: Text.AlignLeft
                }

                MyLabel {
                    id: label_pumpSpeed
                    font.bold: false
                    font.pixelSize: 36
                    horizontalAlignment: Text.AlignHCenter
                    text: "0"
                }

                MyLabel {
                    id: myLabel8
                    width: 44
                    height: 40
                    font.bold: false
                    font.pixelSize: 36
                    text: "rpm"
                }
            }

            Row {
                x: 209
                y: 535
                MyLabel {
                    id: myLabel5
                    text: "泵2速度"
                    font.pixelSize: 36
                    horizontalAlignment: Text.AlignLeft
                    font.bold: false
                }

                MyLabel {
                    id: label_preserSpeed
                    text: "0"
                    font.pixelSize: 36
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: false
                }

                MyLabel {
                    id: myLabel9
                    width: 44
                    height: 40
                    text: "rpm"
                    font.pixelSize: 36
                    font.bold: false
                }
                spacing:20
            }

            Row{
                x: 209
                y: 286
                width: 360
                height: 50
                spacing: 30
                CustomButton{
                    id:add
                    text: " "
                    bgColor: "#404040"
                    visible: true
                    bHasIcon: true
                    btnIcon.source: "/res/pics/add1.png"

                }

                CustomButton{
                    id:stop
                    bgColor: "#404040"
                    visible: true
                    bHasIcon: true
                    property int status: 1
                    text: " "
                    btnIcon.source: "/res/pics/pause.png"

                }

                CustomButton{
                    id:reduce
                    bgColor: "#404040"
                    visible: true
                    bHasIcon: true
                    text: " "
                    btnIcon.source: "/res/pics/reduce1.png"

                }
            }
            Row{
                x: 209
                y: 449
                width: 360
                height: 50
                spacing: 30
                CustomButton{
                    id:add1
                    text: " "
                    bgColor: "#404040"
                    visible: true
                    bHasIcon: true
                    btnIcon.source: "/res/pics/add1.png"

                }

                CustomButton{
                    id:stop1
                    bgColor: "#404040"
                    visible: true
                    bHasIcon: true
                    property int status: 1
                    text: " "
                    btnIcon.source: "/res/pics/pause.png"

                }

                CustomButton{
                    id:reduce1
                    bgColor: "#404040"
                    visible: true
                    bHasIcon: true
                    text: " "
                    btnIcon.source: "/res/pics/reduce1.png"

                }
            }

            Button {
                id: skip
                x: 1077
                y: 617
                width: 100
                height: 57
                visible: true
                style:ButtonStyle{
                background: Rectangle {
                    color: "#404040"
                }
                }
                Text{
                    x:0
                    y:0
                    font.pointSize: 24
                    anchors.centerIn: parent
                    text:"下一步"
                    color: "#ffffff"
                }
            }

            Row {
                x: 650
                y: 412
                width: 380
                height: 40
                spacing: 10
                MyLabel {
                    id: myLabel33
                    width: 180
                    height: 40
                    text: "离心机转速"
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 36
                    font.bold: false
                }

                MyLabel {
                    id: centrifugeSpeed1
                    width: 100
                    height: 40
                    text: "0"
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 36
                    font.bold: false
                }

                MyLabel {
                    id: myLabel34
                    width: 80
                    height: 40
                    text: "rpm"
                    font.pixelSize: 36
                    font.bold: false
                }
            }

        Row {
            x: 651
            y: 514
            width: 368
            height: 40
            spacing: 10

            MyLabel {
                id: myLabel4
                width: 180
                height: 40
                text: "采集量"
                font.bold: false
                font.pixelSize: 36
                horizontalAlignment: Text.AlignLeft
            }

            MyLabel {
                id:label_collectionVlm
                font.bold: false
                font.pixelSize: 36
                horizontalAlignment: Text.AlignHCenter
                text: "0"
            }

            MyLabel {
                id: myLabel10
                width: 44
                height: 40
                font.bold: false
                font.pixelSize: 36
                text: "ml"
            }
        }

        Row {
            x: 656
            y: 313
            spacing: 20

            MyLabel {
                id: myLabel2
                width: 150
                font.bold: false
                font.pixelSize: 36
                text: "时间"
                horizontalAlignment: Text.AlignLeft
            }

            MyLabel {
                id: label_timeLen
                font.bold: false
                text: "0"

                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 40
                color: "yellow"
            }
        }

        ProgressBar{
            id: textInput_dpm
            orientation: Qt.Vertical; //设置竖直滚动条
            x: 1131
            y: 151

            minimumValue: 0
            maximumValue: 60

            width: 16
            height: 123
            visible: true
            clip: false
            indeterminate: false
            value: 40
            style: ProgressBarStyle{
                background: Rectangle{
                    //      border.width: 1;
                    border.color: control.hovered?"green":"#25b1e8";
                    color:"lightgray";
                }
                progress: Rectangle{
                    color: "#25b1e8"
                }
                //                            Gradient:Gradient{
                //                                GradientStop{position: 30;color: "#25b1e8"}
                //                                GradientStop{position: -30;color: "#DC143C"}

                //                            }
            }

        }

        ProgressBar{
            id: textInput_dpm_false
            orientation: Qt.Vertical; //设置竖直滚动条
            x: 1131
            y: 272
            rotation: 180

            minimumValue: 0
            maximumValue: 60

            width: 16
            height: 121
            visible: true
            clip: false
            indeterminate: false
            value: 40
            style: ProgressBarStyle{
                background: Rectangle{
                    //      border.width: 1;
                    border.color: control.hovered?"green":"#25b1e8";
                    color:"lightgray";
                }
                progress: Rectangle{
                    color: "#25b1e8"
                }
                //                            Gradient:Gradient{
                //                                GradientStop{position: 30;color: "#25b1e8"}
                //                                GradientStop{position: -30;color: "#DC143C"}

                //                            }
            }

        }

        MyLabel {
            id: myLabel_60
            x:1150
            y:144
            width: 15
            height: 15

            text: "60"
            font.pixelSize: 10
            font.bold: false
        }
        MyLabel {
            id: myLabel_0
            x:1149
            y:277
            width: 15
            height: 0

            text: "0"
            font.pixelSize: 10
            font.bold: false
        }
        MyLabel {
            id: myLabel_low60
            x:1153
            y:380
            width: 15
            height: 15

            text: "-60"
            font.pixelSize: 10
            font.bold: false
        }


        MyLabel {
            id: myLabel0
            //      width: 180
            x: 1109
            y: 419
            width: 75
            height: 40
            text: "压力"
            font.pixelSize: 36
            horizontalAlignment: Text.AlignLeft
            font.bold: false
        }


        ProgressBar {
            id: pgBar
            visible: false

            x: 260
            y: 144          //144
            width: 694
            height: 70
            value: 0

            minimumValue: 0
            maximumValue: 400

            //        indeterminate: true
            style: ProgressBarStyle {
                background: Rectangle {
                    radius: 2
                    color: m_color.bg
                    border.color: m_color.draw_border
                    border.width: 3
                    implicitWidth: 200
                    implicitHeight: 24
                }
                progress: Rectangle {
                    color: m_color.progress
                    border.color: m_color.draw_border
                }
            }
        }



        Row {
            x: 260
            y: 144
            width: 694
            height: 70
            spacing: 2
            MyLabel {
                id: myLabel
                width: 300
                height: 70

                visible: false

                text: "采集量"
                font.pixelSize: 56
                font.bold: false
            }

            MyLabel {
                id: label_bldVlm
                width: 250
                height: 70
                horizontalAlignment: Text.AlignHCenter

                visible: false

                text: "0"

                font.pixelSize: 60
                color: "#FF7839"
            }

            MyLabel {
                id: myLabel6
                width: 100
                height: 70

                visible: false

                font.pixelSize: 56
                font.bold: false
                horizontalAlignment: Text.AlignLeft
                color: "#FF7839"
                text: "ml"
            }
        }
        ProgressBar {
            id: rbcVlmPgbar

            x: 260
            y: 144          //144
            width: 694
            height: 70
            value: 0


            visible: false

            minimumValue: 0
            maximumValue: 400

            //        indeterminate: true
            style: ProgressBarStyle {
                background: Rectangle {
                    radius: 2
                    color: m_color.bg
                    border.color: m_color.draw_border
                    border.width: 3
                    implicitWidth: 200
                    implicitHeight: 24
                }
                progress: Rectangle {
                    color: m_color.progress
                    border.color: m_color.draw_border
                }
            }
        }

        Row {
            x: 260
            y: 144
            width: 694
            height: 70
            spacing: 2
            MyLabel {
                id: myLabel_rbc
                width: 300
                height: 70

                visible: false
                text:""
                //text: "红细胞量"

                font.pixelSize: 56
                font.bold: false
            }

            MyLabel {
                id: rbcVlm
                width: 250
                height: 70
                horizontalAlignment: Text.AlignHCenter
                text: "0"
                visible: false
                font.pixelSize: 60
                color: "#FF7839"
            }

            MyLabel {
                id: myLabel_rbc1
                visible: false
                width: 100
                height: 70
                font.pixelSize: 56
                font.bold: false
                horizontalAlignment: Text.AlignLeft
                color: "#FF7839"
                text: "ml"
            }
        }

        Rectangle {
            x: 1109
            y: 459
            width: 9
            height: 0
            color: "#ffffff"
        }
    }
    Item {
        id:enrichment
        x: 5
        y: 2895
        //        y: 2770
        width: 1280
        height: 700

        Rectangle {
            anchors.fill: parent
            color: m_color.bg
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0

        Button {
            id: over
            x: 1077
            y: 617
            width: 100
            height: 57
            visible: true
            style:ButtonStyle{
            background: Rectangle {
                color: "#404040"
            }
            }
            Text{
                x:0
                y:0
                anchors.centerIn: parent
                font.pointSize: 24
                text:"完成"
                color: "#ffffff"
            }
        }

        MyLabel {
            id: label_Status2
            x: 547
            y: 64
            width: 176
            height: 51
            text: "浓缩"
            font.pixelSize: 48
            horizontalAlignment: Text.AlignHCenter
            font.bold: false
        }

        Row {
            x: 224
            y: 288
            MyLabel {
                id: myLabel11
                text: "泵1速度"
                font.pixelSize: 36
                horizontalAlignment: Text.AlignLeft
                font.bold: false
            }

            MyLabel {
                id: label_pumpSpeed2
                text: "0"
                font.pixelSize: 36
                horizontalAlignment: Text.AlignHCenter
                font.bold: false
            }

            MyLabel {
                id: myLabel23
                width: 44
                height: 40
                text: "rpm"
                font.pixelSize: 36
                font.bold: false
            }
            spacing: 20
        }

        Row{
            x: 608
            y: 283
            width: 360
            height: 50
            spacing: 30
            CustomButton{
                id:enriadd
                text: " "
                bgColor: "#404040"
                visible: true
                bHasIcon: true
                btnIcon.source: "/res/pics/add1.png"

            }

            CustomButton{
                id:enristop
                bgColor: "#404040"
                visible: true
                bHasIcon: true
                property int status: 1
                text: " "
                btnIcon.source: "/res/pics/pause.png"

            }

            CustomButton{
                id:enrireduce
                bgColor: "#404040"
                visible: true
                bHasIcon: true
                text: " "
                btnIcon.source: "/res/pics/reduce1.png"

            }
        }

        Row {
            x: 436
            y: 387
            MyLabel {
                id: myLabel25
                text: "浓缩量"
                font.pixelSize: 36
                horizontalAlignment: Text.AlignLeft
                font.bold: false
            }

            MyLabel {
                id: label_enrivlm
                text: "0"
                font.pixelSize: 36
                horizontalAlignment: Text.AlignHCenter
                font.bold: false
            }

            MyLabel {
                id: myLabel30
                width: 44
                height: 40
                text: "ml"
                font.pixelSize: 36
                font.bold: false
            }
            spacing: 20
        }

        Row {
            x: 413
            y: 481
            width: 380
            height: 40
            MyLabel {
                id: myLabel31
                width: 180
                height: 40
                text: "离心机转速"
                font.pixelSize: 36
                horizontalAlignment: Text.AlignLeft
                font.bold: false
            }

            MyLabel {
                id: centrifugeSpeed
                width: 100
                height: 40
                text: "0"
                font.pixelSize: 36
                horizontalAlignment: Text.AlignHCenter
                font.bold: false
            }

            MyLabel {
                id: myLabel32
                width: 80
                height: 40
                text: "rpm"
                font.pixelSize: 36
                font.bold: false
            }
            spacing: 10
        }
    }

}
    Item {
        id: result
//        x: 5
//        y: 2895
        x: 5
        y: 3600
        width: 1270
        height: 680


        CustomButton {
            id: btnOK
            x: 1094
            y: 620
            width: 100
            height: 80
            text: "确认"
            bgColor: "#404040"
            visible: true
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }

        CustomButton {
            id: btnUpload
            x: 967
            y: 620
            width: 100
            height: 80
            text: "上传"
            bgColor: "#404040"
            visible: true
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }

        Row {
            x: 209
            y: 119
            width: 300
            height: 40
            spacing: 20
            MyLabel {
                id: myLabel12
                width: 180
                text: "浓缩量"
                font.pixelSize: 30
                horizontalAlignment: Text.AlignLeft
                font.bold: false
            }

            MyLabel {
                id: result_enrivlm//label_donorCode
                text: "000"
                font.pixelSize: 36
                horizontalAlignment: Text.AlignLeft
                font.bold: false
            }
        }
        Row {
            x: 211
            y: 180
            spacing: 20
            MyLabel {
                id: myLabel14
                text: "采集量"
                width: 180
                font.pixelSize: 30
                horizontalAlignment: Text.AlignLeft
                font.bold: false
            }

            MyLabel {
                id: result_bldVlm//label_disposableCode
                text: "000"
                font.pixelSize: 36
                horizontalAlignment: Text.AlignLeft
                font.bold: false
            }

        }

        Row {
            x: 714
            y: 119
            spacing: 20
            MyLabel {
                id: myLabel21
                width: 180
                text: "总时长"
                font.pixelSize: 30
                horizontalAlignment: Text.AlignLeft
                font.bold: false
            }

            MyLabel {
                id: result_timeLen
                text: "0"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 40
                font.bold: false
            }

            MyLabel {
                id: myLabel24
                width: 44
                height: 40
                text: "s"
                font.pixelSize: 36
                font.bold: false
            }
        }

        MyLabel {
            id: label_Status1
            x: 547
            y: 8
            width: 176
            height: 62
            text: "数据统计"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 48
            font.bold: false
        }
//        Row {
//            x: 211
//            y: 237
//            spacing: 20
//            MyLabel {
//                id: myLabel14
//                width: 180
//                text: ""
//                font.pixelSize: 30
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }

//            MyLabel {
//                id: label_ACDCode
//                text: "000"
//                font.pixelSize: 36
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }
//        }
//        Row {
//            x: 211
//            y: 291
//            spacing: 20
//            MyLabel {
//                id: myLabel15
//                width: 180
//                text: "保养液条码"
//                font.pixelSize: 30
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }

//            MyLabel {
//                id: label_presvCode
//                text: "000"
//                font.pixelSize: 36
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }
//        }
//        Row {
//            x: 211
//            y: 352
//            spacing: 20
//            MyLabel {
//                id: myLabel16
//                width: 180
//                text: "操作者"
//                font.pixelSize: 30
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }

//            MyLabel {
//                id: label_operatorCode
//                text: "000"
//                font.pixelSize: 36
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }
//        }

//        Row {
//            x: 714
//            y: 180
//            spacing: 20
//            MyLabel {
//                id: myLabel28
//                width: 180
//                text: "全血量"
//                font.pixelSize: 30
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }

//            MyLabel {
//                id: label_dpmVlm_e
//                text: "0"
//                font.pixelSize: 36
//                horizontalAlignment: Text.AlignHCenter
//                font.bold: false
//            }

//            MyLabel {
//                id: myLabel29
//                width: 44
//                height: 40
//                text: "ml"
//                font.pixelSize: 36
//                font.bold: false
//            }
//        }

//        Row {
//            x: 714
//            y: 237
//            spacing: 20
//            MyLabel {
//                id: myLabel17
//                width: 180
//                text: "血浆"
//                font.pixelSize: 30
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }

//            MyLabel {
//                id: label_plsmVlm_e
//                text: "0"
//                font.pixelSize: 36
//                horizontalAlignment: Text.AlignHCenter
//                font.bold: false
//            }

//            MyLabel {
//                id: myLabel18
//                width: 44
//                height: 40
//                text: "ml"
//                font.pixelSize: 36
//                font.bold: false
//            }
//        }

//        Row {
//            x: 211
//            y: 417
//            spacing: 20
//            MyLabel {
//                id: myLabel19
//                width: 180
//                text: "保养液"
//                font.pixelSize: 30
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }

//            MyLabel {
//                id: label_presvVlm1
//                text: "0"
//                font.pixelSize: 36
//                horizontalAlignment: Text.AlignHCenter
//                font.bold: false
//            }

//            MyLabel {
//                id: myLabel20
//                width: 44
//                height: 40
//                text: "ml"
//                font.pixelSize: 36
//                font.bold: false
//            }
//        }


        //        Row {
        //            x: 712
        //            y: 186
        //            spacing: 20
        //            MyLabel {
        //                id: myLabel25
        //                width: 180
        //                text: "结束时间"
        //                font.pixelSize: 30
        //                horizontalAlignment: Text.AlignLeft
        //                font.bold: false
        //            }

        //            MyLabel {
        //                id: label_endTime
        //                text: "0"
        //                horizontalAlignment: Text.AlignHCenter
        //                font.pixelSize: 40
        //                font.bold: false
        //            }
        //        }

//        Row {
//            x: 714
//            y: 352
//            spacing: 20
//            MyLabel {
//                id: label_ACDName1
//                width: 180
//                text: "抗凝剂"
//                font.pixelSize: 30
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }

//            MyLabel {
//                id: label_ACDVlm1
//                text: "0"
//                font.pixelSize: 36
//                horizontalAlignment: Text.AlignHCenter
//                font.bold: false
//            }

//            MyLabel {
//                id: myLabel22
//                width: 44
//                height: 40
//                text: "ml"
//                font.pixelSize: 36
//                font.bold: false
//            }
//        }

//        Row {
//            x: 714
//            y: 417
//            spacing: 20
//            MyLabel {
//                id: label_state
//                width: 180
//                text: "状态"
//                font.pixelSize: 30
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }

//            MyLabel {
//                id: label_statelabel
//                text: "0"
//                font.pixelSize: 36
//                horizontalAlignment: Text.AlignHCenter
//                font.bold: false
//            }
//        }

        //        Row {
        //            x: 714
        //            y: 448
        //            spacing: 20
        //            MyLabel {
        //                id: myLabel23
        //                width: 180
        //                text: "洗涤盐水"
        //                font.pixelSize: 30
        //                horizontalAlignment: Text.AlignLeft
        //                font.bold: false
        //            }

        //            MyLabel {
        //                id: label_NaClVlm1
        //                text: "0"
        //                font.pixelSize: 36
        //                horizontalAlignment: Text.AlignHCenter
        //                font.bold: false
        //            }

        //            MyLabel {
        //                id: myLabel24
        //                width: 44
        //                height: 40
        //                text: "ml"
        //                font.pixelSize: 36
        //                font.bold: false
        //            }
        //        }


//        Row {
//            x: 714
//            y: 297
//            spacing: 20
//            MyLabel {
//                id: myLabel26
//                width: 180
//                text: "悬浮红细胞"
//                font.pixelSize: 30
//                horizontalAlignment: Text.AlignLeft
//                font.bold: false
//            }

//            MyLabel {
//                id: label_RBCVlm_e
//                text: "0"
//                font.pixelSize: 36
//                horizontalAlignment: Text.AlignHCenter
//                font.bold: false
//            }

//            MyLabel {
//                id: myLabel27
//                width: 44
//                height: 40
//                text: "ml"
//                font.pixelSize: 36
//                font.bold: false
//            }
//        }
    }


    Item {
        id:idpageView
        x: 5
        y: 4100
        width: 1280
        height: 700


        MyLabel {
            id: label_blood_code
            x: 449
            y: 154
            width: 100
            height: 50
            text: qsTr("献血码")
            font.bold: false
        }

        Column{
            id: colu_code
            x: 562
            y: 154
            spacing: 50

            TextField{
                id: blood_code

                font.family: "微软雅黑"


                width: 235
                height: 50
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 18
                focus: true

            }

            TextField{
                id: consu_code

                font.family: "微软雅黑"

                text: ""
                width: 235
                height: 50
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 18
                focus: true

                //                inputMask: '000.000.000.000'
            }

            TextField{
                id: anti_code

                font.family: "微软雅黑"

                text: ""
                width: 235
                height: 50
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 18
                focus: true

                //                inputMask: '000.000.000.000'
            }

            TextField{
                id: maintenance_code

                font.family: "微软雅黑"

                text: ""
                width: 235
                height: 50
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 18
                focus: true
                //                inputMask: '000.000.000.000'
            }

            TextField{
                id: user_code

                font.family: "微软雅黑"

                text: ""
                width: 235
                height: 50
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 18
                focus: true
                //                inputMask: '000.000.000.000'
            }
        }

        //        TextField{
        //            id: blood_code
        //            x: 562
        //            y: 154

        //            font.family: "微软雅黑"


        //            width: 235
        //            height: 50
        //            verticalAlignment: Text.AlignVCenter
        //            horizontalAlignment: Text.AlignHCenter
        //            font.bold: true
        //            font.pixelSize: 18
        //            focus: true

        //        }

        MyLabel {
            x: 449
            y: 254
            width: 100
            height: 50
            text: qsTr("耗材条码")
            font.bold: false
        }

        //            TextField{
        //                id: consu_code
        //                x: 562
        //                y: 254

        //                font.family: "微软雅黑"

        //                text: ""
        //                width: 235
        //                height: 50
        //                verticalAlignment: Text.AlignVCenter
        //                horizontalAlignment: Text.AlignHCenter
        //                font.bold: true
        //                font.pixelSize: 18
        //                focus: true

        //    //                inputMask: '000.000.000.000'
        //            }

        MyLabel {
            x: 449
            y: 354
            width: 100
            height: 50
            text: qsTr("抗凝剂条码")
            font.bold: false
        }

        //            TextField{
        //                id: anti_code
        //                x: 562
        //                y: 354

        //                font.family: "微软雅黑"

        //                text: ""
        //                width: 235
        //                height: 50
        //                verticalAlignment: Text.AlignVCenter
        //                horizontalAlignment: Text.AlignHCenter
        //                font.bold: true
        //                font.pixelSize: 18
        //                focus: true

        //    //                inputMask: '000.000.000.000'
        //            }

        MyLabel {
            x: 449
            y: 454
            width: 100
            height: 50
            text: qsTr("保养液条码")
            font.bold: false
        }

        //            TextField{
        //                id: maintenance_code
        //                x: 562
        //                y: 454

        //                font.family: "微软雅黑"

        //                text: ""
        //                width: 235
        //                height: 50
        //                verticalAlignment: Text.AlignVCenter
        //                horizontalAlignment: Text.AlignHCenter
        //                font.bold: true
        //                font.pixelSize: 18
        //                focus: true
        //    //                inputMask: '000.000.000.000'
        //            }

        MyLabel {
            x: 449
            y: 554
            width: 100
            height: 50
            text: qsTr("操作者条码")
            font.bold: false
        }

        //            TextField{
        //                id: user_code
        //                x: 562
        //                y: 554

        //                font.family: "微软雅黑"

        //                text: ""
        //                width: 235
        //                height: 50
        //                verticalAlignment: Text.AlignVCenter
        //                horizontalAlignment: Text.AlignHCenter
        //                font.bold: true
        //                font.pixelSize: 18
        //                focus: true
        //    //                inputMask: '000.000.000.000'
        //            }


        CustomButton {
            id: btnQuitId
            x: 1100
            y: 620
            width: 100
            height: 80
            text: "退出"

            bgColor: "#404040"
            bHasIcon: true
            btnIcon.source: "/res/pics/exit.png"
        }

        //            CustomButton {
        //                id: btnSaveId
        //                x: 950
        //                y: 620
        //                text: "保存"
        //                width: 100
        //                height: 80

        //                bgColor: "#404040"
        //                bHasIcon: true
        //                btnIcon.source: "/res/pics/save.png"
        //            }

        Text {
            id: title_ID
            x: 614
            y: 30
            width: 130
            height: 37
            color: "#ffffff"
            text: qsTr("ID设置")
            verticalAlignment: Text.AlignTop
            font.bold: true
            font.family: "Tahoma"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }
    }

}
}
