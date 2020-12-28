import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import QtQuick.VirtualKeyboard.Settings 2.0
import UiAdaptor 1.0
import "content"

ApplicationWindow {
    id:root

    visible: true
    width: 1280
    height: 800

    flags:qsTr("Qt::FramelessWindowHint")
    //    background:Image{
    //        source: "/res/pics/bg.png"
    //    }

    header:UpperView{
        id:upperView
        width: parent.width
    }

    AppView {
    }

    UiAdaptor{
        id: uiAdaptor
    }

    Component.onCompleted: {
    }


//    property real mouseXTMP: 0

//    property real mouseYTMP: 0
//    MouseArea {
//        anchors.fill: parent
//        onPressed: {
//            mouseXTMP = mouseX
//            mouseYTMP = mouseY
//        }
//        onPositionChanged: {
//            inputPanel.x = mouseX + inputPanel.x - mouseXTMP
//            inputPanel.y = mouseY + inputPanel.y - mouseYTMP
//        }
//    }

    InputPanel {
        id: inputPanel
        z: 89
        y: root.height
        anchors.right: parent.right
        anchors.left: parent.left

        states: State {
            name: "visible"
            /*  The visibility of the InputPanel can be bound to the Qt.inputMethod.visible property,
                but then the handwriting input panel and the keyboard input panel can be visible
                at the same time. Here the visibility is bound to InputPanel.active property instead,
                which allows the handwriting panel to control the visibility when necessary.
            */
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: root.height - inputPanel.height - 50
            }
        }
        transitions: Transition {
            id: inputPanelTransition
            from: ""
            to: "visible"
            reversible: true
            enabled: !VirtualKeyboardSettings.fullScreenMode

            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
        Binding {
            target: InputContext
            property: "animating"
            value: inputPanelTransition.running
        }

        AutoScroller {}

    }

    Binding {
        target: VirtualKeyboardSettings
        property: "fullScreenMode"
        value: root.height > 0 && (root.width / root.height) > (16.0 / 9.0)
    }
}
