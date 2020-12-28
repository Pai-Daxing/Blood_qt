import QtQuick 2.7
import QtQuick.Controls 1.4

Rectangle{
    id: tableCell
    anchors.fill: parent;
    color: styleData.selected ? "transparent" : "#1A4275";

    Text{
        id: textID;
        text:styleData.value ;
        font.family: "微软雅黑";
        font.pixelSize: 16;
        anchors.fill: parent;
        color: "white";
        elide: Text.ElideRight;
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
