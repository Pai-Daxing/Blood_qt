import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "customCtrls"

Item{
    id : container
    width: 1280
    height: 750
    anchors.top: upperView.bottom
    property alias swipeView: swipeView

//    anchors.topMargin: 2

    MyColors {
        id : m_color
    }

    SwipeView {
        id: swipeView
        interactive :false
        //        anchors.top: tabBar.bottom
        //        anchors.left: parent.left
        //        anchors.right: parent.right
        //        height: container.height - tabBar.height

        anchors.fill: parent
        anchors.bottomMargin: indicator.height
        currentIndex: 0

        background:Rectangle{
            color : "#404040"
        }

        RunningPage {
            id : runningView
            // 主页面滑动
            onSwiped: {
                swipeView.currentIndex = 1
                upperView.statusLabel.text = "设置"
            }
        }

        SettingPage {
            id : settingingView

            // 主页面滑动
            onSwiped: {
                swipeView.currentIndex = 0
                upperView.statusLabel.text = "运行"
            }

            onBcodeopen: {
                runningView.label_blood_code.visible = true
                runningView.blood_code.visible = true
                console.log("open_Blood_label")
            }

            onBcodeclose: {
                runningView.label_blood_code.visible = false
                runningView.blood_code.visible = false
                console.log("close_Blood_label")
            }

            onCcodeopen: {
                runningView.label_consu_code.visible = true
                runningView.consu_code.visible = true
            }

            onCcodeclose: {
                runningView.label_consu_code.visible = false
                runningView.consu_code.visible = false
            }

            onAcodeopen: {
                runningView.label_anti_code.visible = true
                runningView.anti_code.visible = true
            }

            onAcodeclose: {
                runningView.label_anti_code.visible = false
                runningView.anti_code.visible = false
            }

            onPcodeopen: {
                runningView.label_maintenance_code.visible = true
                runningView.maintenance_code.visible = true
            }

            onPcodeclose: {
                runningView.label_maintenance_code.visible = false
                runningView.maintenance_code.visible = false
            }

            onUcodeopen: {
                runningView.label_user_code.visible = true
                runningView.user_code.visible = true
            }

            onUcodeclose: {
                runningView.label_user_code.visible = false
                runningView.user_code.visible = false
            }
        }

        Component.onCompleted: {
        }
    }
    //底部加上小圆点
    PageIndicator {
        id: indicator

        count: 2
        currentIndex: swipeView.currentIndex

        anchors.bottom: swipeView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

}
