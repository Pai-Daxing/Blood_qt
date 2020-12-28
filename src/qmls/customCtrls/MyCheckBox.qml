import QtQuick 2.6
import QtQuick.Controls 2.0

CheckBox {
    id: control
    text: qsTr("CheckBox")
    checked: true

    font.family: "微软雅黑"
    font.pixelSize: 24

    MyColors {
        id : m_color
    }

    indicator: Rectangle {
        implicitWidth: 32
        implicitHeight: 32
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 3
        border.color: control.down ?  m_color.button_pressed: m_color.text_input_bg

        Rectangle {
            width: 20
            height: 20
            x: 6
            y: 6
            radius: 2
            color: m_color.button_pressed
            visible: control.checked
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.down ?  m_color.button_pressed: m_color.text_input_bg
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
