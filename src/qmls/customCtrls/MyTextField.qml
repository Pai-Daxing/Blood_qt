import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

TextField{
    id: control

    MyColors {
        id : m_color
    }

    font.family: "微软雅黑"

    width: 182
    height: 40
    color: m_color.text_input
    text: qsTr("90")
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    font.bold: true
    font.pixelSize: 18

    inputMask: '0000'
}
