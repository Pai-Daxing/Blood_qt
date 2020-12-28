import QtQuick 2.4
import "customCtrls"
import QtQuick.Controls 2.2

Item {
    width: 1270
    height: 700

    property alias btnQuitSysParam: btnQuitSysParam
    property alias btnSaveSysParam: btnSaveSysParam
    MyLabel {
        id: text8
        x: 477
        y: 227
        width: 110
        text: qsTr("机器编号")
    }

    MyTextField {
        id: m_Code
        x: 595
        y: 227
        text: qsTr("90")
    }

    MyLabel {
        id: text10
        x: 477
        y: 330
        width: 110
        text: qsTr("管探灵敏度")
    }

    MyTextField {
        id: line_Sensor
        x: 599
        y: 330
        text: qsTr("90")
    }


    CustomButton {
        id: btnQuitSysParam
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
        id: btnSaveSysParam
        x: 950
        y: 620
        text: "保存"
        width: 100
        height: 80

        bgColor: "#404040"
        bHasIcon: true
        btnIcon.source: "/res/pics/save.png"
    }
}
