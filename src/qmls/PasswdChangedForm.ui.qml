import QtQuick 2.4

import "customCtrls" as MyCtrls
import QtQuick.Controls 2.2

import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id:passwdchangeView
    width: 1280
    height: 700
    property alias new_passwd: new_passwd
    property alias passwd_OK: passwd_OK
    property alias change_OK: change_OK
    property alias passwd_exit: passwd_exit
    property alias changePopup: changePopup
    property alias changePopupOK: changePopupOK
    property alias changePopuperror: changePopuperror
    property alias first_pwd: first_pwd

    MyCtrls.MyLabel {
        x: 471
        y: 148
        width: 100
        height: 50
        text: qsTr("原密码:")
        font.bold: false
    }

    TextField{
        id: first_pwd
        x: 584
        y: 148

        font.family: "微软雅黑"

        width: 235
        height: 50
        //   color: "#404040"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        font.pixelSize: 18
        inputMethodHints:Qt.ImhDigitsOnly
        echoMode: TextInput .Password
        //                inputMask: '000.000.000.000'
    }

    MyCtrls.MyLabel {
        x: 471
        y: 214
        width: 100
        height: 50
        text: qsTr("新密码:")
        font.bold: false
    }

    TextField{
        id: new_passwd
        x: 584
        y: 214

        font.family: "微软雅黑"

        width: 235
        height: 50
        //   color: "#404040"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        font.pixelSize: 18
        inputMethodHints:Qt.ImhDigitsOnly
        echoMode: TextInput .Password

        //                inputMask: '000.000.000.000'
    }

    MyCtrls.MyLabel {
        x: 471
        y: 280
        width: 100
        height: 50
        text: qsTr("确认密码:")
        font.bold: false
    }

    TextField{
        id: passwd_OK
        x: 584
        y: 280
        //     text:"88888888"

        font.family: "微软雅黑"

        width: 235
        height: 50
        //   color: "#404040"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        font.pixelSize: 18
        inputMethodHints:Qt.ImhDigitsOnly //仅允许文本输入
        echoMode: TextInput .Password //输入的变成星号

        //                inputMask: '000.000.000.000'
    }

    MyCtrls.ChooseButton {
        id: change_OK    //
        x: 430
        y: 401

        width: 150
        height: 50
        text: "确认"
    }
    MyCtrls.ChooseButton {
        id: passwd_exit    //退出
        x: 717
        y: 401

        width: 150
        height: 50
        text: "退出"
    }
    Popup{
        id:changePopup
        width: 200
        height: 150
        x: 540
        y: 200
        modal: true
        focus: true
        visible: false

        background:Rectangle
        {
        //            width: 400
        //            height: 300
        anchors.fill: parent
        anchors.centerIn: parent
        color: "lightblue"
        radius: 7
        Text {
            id: text
            font.pixelSize: 24
            anchors.bottom: parent.bottom
            anchors.centerIn: parent
            wrapMode: Text.WordWrap

            text: qsTr("两次密码不一致!")
        }
    }
}

Popup{
    id:changePopupOK
    width: 200
    height: 150
    x: 540
    y: 200
    modal: true
    focus: true
    visible: false

    background:Rectangle
    {
    //            width: 400
    //            height: 300
    anchors.fill: parent
    anchors.centerIn: parent
    color: "lightblue"

    radius: 7
    Text {
        id: text1
        font.pixelSize: 24
        anchors.bottom: parent.bottom
        anchors.centerIn: parent
        wrapMode: Text.WordWrap

        text: qsTr("密码修改成功!")
    }
}
}

Popup{
    id:changePopuperror
    width: 200
    height: 150
    x: 540
    y: 200
    modal: true
    focus: true
    visible: false

    background:Rectangle
    {
        //            width: 400
        //            height: 300
        anchors.fill: parent
        anchors.centerIn: parent
        color: "lightblue"

        radius: 7
        Text {
            id: texterror
            font.pixelSize: 24
            anchors.bottom: parent.bottom
            anchors.centerIn: parent
            wrapMode: Text.WordWrap

            text: qsTr("原始密码输入错误!")
        }
    }
}

}
