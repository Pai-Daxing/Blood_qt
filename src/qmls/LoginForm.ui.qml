import QtQuick 2.4

import "customCtrls" as MyCtrls
import QtQuick.Controls 2.2

import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id:login_popupon
    width: 1280
    height: 700
    property alias login_Ok: login_Ok
    property alias login_exit: login_exit
    property alias login_popupon: login_popupon
    property alias input_name: input_name
    property alias input_passwd: input_passwd
//    property alias myPopup: myPopup

    MyCtrls.MyLabel {
        x: 448
        y: 190
        width: 100
        height: 50
        text: qsTr("用户名:")
        font.bold: false
    }

    TextField{
        id: input_name
        x: 561
        y: 190
        font.family: "微软雅黑"
        text: "BND_BCP_01"
        width: 235
        height: 50
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        font.pixelSize: 18
        readOnly: true
    }

        MyCtrls.MyLabel {
            x: 448
            y: 260
            width: 100
            height: 50
            text: qsTr("密码:")
            font.bold: false
        }

        TextField{
            id: input_passwd
            x: 561
            y: 260
            font.family: "微软雅黑"
            width: 235
            height: 50
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.pixelSize: 18
            inputMethodHints:Qt.ImhDigitsOnly
            echoMode: TextInput .Password
        }

        MyCtrls.ChooseButton {
            id: login_Ok    //
            x: 405
            y: 384
            width: 150
            height: 50
            text: "登录"
        }
        MyCtrls.ChooseButton {
            id: login_exit    //退出
            x: 698
            y: 384

            width: 150
            height: 50
            text: "退出"
        }

//        Popup{
//            id:myPopup
//            width: 200
//            height: 150
//            x: 540
//            y: 200
//            modal: true
//            focus: true
//            visible: false
//            background:Rectangle
//            {
//                radius: 7
//                color: "lightblue"
//                anchors.fill: parent
//                anchors.centerIn: parent
//                Text {
//                    id: mytext
//                    font.pixelSize: 24
//                    anchors.bottom: parent.bottom
//                    anchors.centerIn: parent
//                    wrapMode: Text.WordWrap
//                    text: qsTr("密码输入错误!")
//                }
//            }
//        }
}




