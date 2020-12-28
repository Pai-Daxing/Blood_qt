import QtQuick 2.0
import "customCtrls"
import UiAdaptor 1.0
import QtQuick.Controls 2.0

Item {
    id:view
    height: 70
    property alias timeLabel: timeLabel
    property alias timeLabel1: timeLabel1

    property alias statusLabel: statusLabel

    MyColors{id:m_color}
    Rectangle {
        id : bg
        color: m_color.bg

        anchors.fill: parent
        MyLabel {
            id : statusLabel
            anchors.left: parent.left
            anchors.leftMargin: 10

            width: 120
            height: view.height
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 56
            font.bold: false
            //            font.family:"微软雅黑"
            text: qsTr("运行")
        }

        UiAdaptor{
            id: uiAdaptor_upper

            onTimerUpdate:
            {
                timeLabel1.text = str;
            }
////////////////////该部分显示逻辑有误 注意查验/////////////
            onNetconnect: {
                netyes.visible = true
                netno.visible = false

                timeLabel1.visible = true
                timeLabel.visible = false
            }

            onNetconnectfaild: {
                netyes.visible = false
                netno.visible = true

                timeLabel.visible = true
                timeLabel1.visible = false
            }
/////////////////////////////////////////////////////////
        }

        MyLabel {
            id : timeLabel
            anchors.right: parent.right
            anchors.rightMargin: 2
            width: 180
            height: 70
            horizontalAlignment: Text.AlignHCenter
            text: ""
            Timer {
                interval: 500; running: true; repeat: true
                // 年份 月份 号 大月份
                onTriggered: timeLabel.text = Qt.formatDateTime(new Date(), "hh:mm:ss\nyyyy/MM/dd")  //这是一个定时器
            }
        }

        MyLabel {
            id : timeLabel1
            anchors.right: parent.right
            anchors.rightMargin: 2
            width: 180
            height: 70
            horizontalAlignment: Text.AlignHCenter
            text: ""
        }

        Image {
            id: netyes
            visible: false
            x:1050
            y:10
            source: "/res/pics/netno.png"
        }

        Image {
            id: netno
            visible: false
            x:1050
            y:10
            source: "/res/pics/net.png"
        }

    }
}
