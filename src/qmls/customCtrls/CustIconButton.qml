import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Button{
    id: control
    text: qsTr("Button")

    property alias btnIcon :btnIcon

    font.family: "微软雅黑"
    font.pixelSize: 24
    font.bold: true

    MyColors {
        id : cs_color
    }

    width: 240
    height: 140
    contentItem: Item {
        MyLabel{
            text: control.text
            font.pixelSize: 24
            font.bold: false
            opacity: control.down ? 0.5 : 1.0
            color: cs_color.text
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
        }

        Image {
            id : btnIcon
            opacity: control.down ? 0.5 : 1.0
            visible: control.enabled
            y: (control.height - height)*2/3
            x: control.width *0.5

            source: "/res/pics/left.png"
            sourceSize.width: 90
            sourceSize.height: 90
        }
    }

    background: Canvas {
        id: mycanvas
        anchors.fill: parent
        contextType: "2d"
        scale: control.pressed ? 0.99 : 1.0
        opacity: control.down ? 0.5 : 1.0

        onPaint: {
            context.reset();
            context.fillStyle = "#0073C6";
            context.fillRect(0, 0, width, height);

            if (control.enabled){
                context.moveTo(0, 0);
                context.lineTo(0, parent.height - 5);
                context.lineTo(parent.width - 5, 0);
                context.lineTo(0, 0);

                context.fillStyle = "#008FDC";
                context.fill();
            }
        }
    }
}
