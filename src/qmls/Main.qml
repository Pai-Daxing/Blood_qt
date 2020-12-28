import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import UiAdaptor 1.0
import "content"

ApplicationWindow {
    id:root
    width: 1280
    height: 800
    visible: true

    flags:qsTr("Qt::FramelessWindowHint")
//    background:Image{
//        source: "/res/pics/bg.png"
//    }

    header:UpperView{
        id:upperView
        width: parent.width

        statusLabel.text:(appView.swipeView.currentIndex = 0)? qsTr("运行"):qsTr("设置")
    }

    AppView {
        id:appView
    }

    UiAdaptor{
        id: uiAdaptor
    }

    Component.onCompleted: {

    }
}
