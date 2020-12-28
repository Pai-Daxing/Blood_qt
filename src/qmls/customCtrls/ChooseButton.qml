import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Button{
    id: control
    text: qsTr("Button")
    property bool bHasIcon: false
    property var  bgColor: "#D3D3D3"

    font.family: "微软雅黑"
    font.pixelSize: 24

    MyColors {
        id : m_color
    }

    implicitWidth: 180
    implicitHeight: 50

    MyLabel{
        anchors.horizontalCenter: control.horizontalCenter
        anchors.verticalCenter: control.verticalCenter
        //            anchors.topMargin: 3
        //            anchors.left: parent.left
        //            anchors.leftMargin: 30
        anchors.fill: (bHasIcon)?undefined:parent

        text: control.text
        font: control.font
        opacity: control.down ? 0.5 : 1.0
        color: "#000000"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        opacity: control.down ? 0.5 : 1.0
        radius: 10
        color: "#D3D3D3"
        scale: control.pressed ? 0.99 : 1.0
    }
}


