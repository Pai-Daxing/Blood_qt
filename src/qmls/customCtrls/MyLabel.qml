import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Label{
    id: control
    text: qsTr("text")

    font.family: "微软雅黑"

    MyColors {
        id : cs_color
    }

    width: 110
    height: 40
    font.bold: true
    color: cs_color.text
    horizontalAlignment: Text.AlignRight
    font.pixelSize: 22
    verticalAlignment: Text.AlignVCenter
}
