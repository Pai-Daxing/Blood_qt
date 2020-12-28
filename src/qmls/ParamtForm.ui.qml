import QtQuick 2.4
import QtQuick 2.4
import "customCtrls"
import QtQuick.Controls 2.2

Item {
//    id: paramSet
//    x: 5
//    y: 755
    width: 1270
    height: 700
    visible: false
    property alias title_text: title_text
    property alias collectSpeed: collectSpeed
    property alias drawSpeed: drawSpeed
    property alias target: comboBox_target
    property alias btnOK_param: btnOK_param
    property alias btnDiscard_param: btnDiscard_param
    property alias presvVlmSpeed: presvVlmSpeed
    property alias lineCoeff: lineCoeff
    property alias comboBox_anti: comboBox_anti
    property alias popup_error: popup_error
    Popup{
        id:popup_error
        width: 250
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
                id: mytext
                font.pixelSize: 24
                text: qsTr("参数设置超出范围!")
            }
        }
    }

    Text {
        id: title_text
        x: 575
        y: 6
        width: 130
        height: 37
        color: "#ffffff"
        text: qsTr("参数设置")
        verticalAlignment: Text.AlignTop
        font.bold: true
        font.family: "Tahoma"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 24
    }

    ComboBox {
        id: comboBox_target
        x: 559
        y: 100
        width: 182
        height: 40
        font.wordSpacing: 2
        spacing: 10
        font.pixelSize: 18
        font.bold: true
        font.family: "Tahoma"
        textRole: qsTr("")
        currentIndex: 0

        model: ["400", "300", "200","50","20"]
    }

    MyLabel {
        id: text3
        x: 404
        y: 100
        width: 131
        text: qsTr("采血量")
        font.letterSpacing: (width - text.length * 22) / text.length

    }

    MyLabel {
        id: text4
        x: 404
        y: 183
        width: 131
        text: qsTr("采血速度")
        font.letterSpacing: (width - text.length * 22) / text.length

    }



    MyLabel {
        id: text5
        x: 761
        y: 183
        width: 60
        text: qsTr("rpm")
    }

    MyTextField {
        id: drawSpeed
        x: 559
        y: 183
      //  text: qsTr("")
        inputMask: '000'
    }

    MyLabel {
        id: text6
        x: 404
        y: 340
        width: 131
        text: qsTr("收集速度")
        font.letterSpacing: (width - text.length * 22) / text.length

    }

    MyTextField {
        id: collectSpeed
        x: 559
        y: 340
      //  text: qsTr("")
        inputMask: '000'
    }

    MyLabel {
        id: text7
        x: 761
        y: 340
        width: 60
        text: qsTr("rpm")
    }

    MyLabel {
        id: textbao
        x: 404
        y: 261
        width: 131
        text: qsTr("保养液速度")
        font.letterSpacing: (width - text.length * 22) / text.length

    }
    MyTextField {
        id: presvVlmSpeed
        x: 559
        y: 261
      //  text: qsTr("")
        inputMask: '000'
    }

    MyLabel {
        id: textb
        x: 761
        y: 261
        width: 60
        text: qsTr("rpm")
    }

    MyLabel {
        id: label_anti
        x: 404
        y: 420
        width: 131
        text: qsTr("抗凝比")
        font.letterSpacing: (width - text.length * 22) / text.length

    }

    MyLabel {
        id: bi
        x: 544
        y: 420
        width: 63
        height: 40
        text: qsTr("1 :")
        font.bold: false
    }

    ComboBox {
        id: comboBox_anti
        x: 634
        y: 420
        width: 107
        height: 40
        font.wordSpacing: 2
        spacing: 10
        font.pixelSize: 18
        font.bold: true
        font.family: "Tahoma"
        textRole: qsTr("")
        currentIndex: 0

        model: ["2", "3", "4","5","6","7","8","9","10"]
    }

    MyLabel {
        id: label_Line
        x: 404
        y: 500
        width: 131
        text: qsTr("管探系数")
        font.letterSpacing: (width - text.length * 22) / text.length
    }

    MyTextField {
        id: lineCoeff
        x: 559
        y: 500
      //  text: qsTr("")
        inputMask: '000'
    }

    MyLabel {
        id: text5_Line
        x: 761
        y: 500
        width: 60
        text: qsTr("%")
    }

    CustomButton {
        id: btnOK_param
        x: 950
        y: 620
        width: 100
        height: 80
        text: "保存"

        bgColor: "#404040"
        bHasIcon: true
        btnIcon.source: "/res/pics/save.png"
    }

    CustomButton {
        id: btnDiscard_param
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
