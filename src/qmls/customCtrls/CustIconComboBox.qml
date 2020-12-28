//import QtQuick 2.0
//import QtQuick.Controls 2.0

import QtQuick 2.6
import QtQuick.Controls 2.0

ComboBox {
    id: control
    property string title: qsTr("语言")

    font.family: "微软雅黑"
    font.pixelSize: 24

    MyColors {
        id : m_color
    }

    delegate: ItemDelegate {
        width: control.width
        contentItem: Text {
            text: modelData
            color: m_color.text_input
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        highlighted: control.highlightedIndex == index
    }

    indicator: Canvas {
        id: canvas
        opacity: control.down ? 0.5 : 1.0

        x: control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight * 2) / 3
        width: 20
        height: 16
        contextType: "2d"

        Connections {
            target: control
            onPressedChanged: canvas.requestPaint()
        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = control.pressed ? m_color.text_input : m_color.text;
            context.fill();
        }
    }

    contentItem: Text {
        leftPadding: 0
        rightPadding: control.indicator.width + control.spacing
        text: control.displayText

        font.family: "微软雅黑"
        font.pixelSize: 50
        font.bold: false

        color: m_color.text
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
    }

    background: Item {
        Canvas {
            id: mycanvas
            anchors.fill: parent
            contextType: "2d"
            opacity: control.down ? 0.5 : 1.0

            onPaint: {
                context.reset();
                context.fillStyle = "#009ED2";
                context.fillRect(0, 0, width, height);

                context.moveTo(0, 0);
                context.lineTo(0, parent.height - 5);
                context.lineTo(parent.width - 5, 0);
                context.lineTo(0, 0);

                context.fillStyle = "#008CC5";
                context.fill();
            }
        }

        MyLabel{
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 5

            text: control.title
            font.pixelSize: 24
            font.bold: false
            opacity: control.down ? 0.5 : 1.0
            color: m_color.text
            horizontalAlignment: Text.AlignLeft
        }
    }

    popup: Popup {
        y: control.height - 1
        width: control.width
        implicitHeight: listview.contentHeight
        padding: 1

        contentItem: ListView {
            id: listview
            clip: true
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            border.color: m_color.bg
            radius: 2
        }
    }
}
