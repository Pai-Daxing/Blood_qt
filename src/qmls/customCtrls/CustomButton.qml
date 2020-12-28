import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Button{
    id: control
    text: qsTr("Button")
    property alias btnIcon :btnIcon
    property bool bHasIcon: false
    property var  bgColor: "#008FDC"

    font.family: "微软雅黑"
    font.pixelSize: 24

    MyColors {
        id : m_color
    }

    implicitWidth: 100
    implicitHeight: 50

    contentItem: Item {
        Image {
            id : btnIcon
            visible: bHasIcon
            opacity: control.down ? 0.5 : 1.0

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 3

            source: "/res/pics/save.png"
            sourceSize.width: 50
            sourceSize.height: 50
        }

        MyLabel{
            anchors.horizontalCenter: btnIcon.horizontalCenter
            anchors.top: btnIcon.bottom
            anchors.topMargin: 3
            anchors.fill: (bHasIcon)?undefined:parent

            text: control.text
            font: control.font
            opacity: control.down ? 0.5 : 1.0
            color: m_color.text
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        opacity: control.down ? 0.5 : 1.0
        radius: 2
        color: bgColor
        scale: control.pressed ? 0.99 : 1.0
    }
}
