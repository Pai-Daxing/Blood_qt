import QtQuick 2.6
  import QtQuick.Controls 2.0

  Switch {
      id: control
      text: qsTr("Switch")

      font.pixelSize: 22
      font.family: "微软雅黑"

//      indicator: Rectangle {
//          implicitWidth: 60
//          implicitHeight: 30
//          x: control.leftPadding
//          y: parent.height / 2 - height / 2
//          radius: 6
//          color: control.checked ? "#17a81a" : "#ffffff"
//          border.color: control.checked ? "#17a81a" : "#cccccc"

//          Rectangle {
//              x: control.checked ? parent.width - width : 0
//              width: 26
//              height: 26
//              radius: 13
//              color: control.down ? "#cccccc" : "#ffffff"
//              border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
//          }
//      }

      contentItem: Text {
          text: control.text
          font: control.font
          opacity: enabled ? 1.0 : 0.3
          color: control.checked ? "#17a81a" : m_color.button_front
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
          leftPadding: control.indicator.width + control.spacing
      }

      MyColors {
          id : m_color
      }
  }
