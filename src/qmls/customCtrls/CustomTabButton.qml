import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

TabButton {
    id:control

    MyColors {
        id : cs_color
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.checked ? cs_color.button_pressed : cs_color.button_bg
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
//        border.color: cs_color.button_border
//        border.width: 1
        radius: 10

        antialiasing:true
        color:control.checked ? "#ffffff" : "#21be2b"
    }
}
