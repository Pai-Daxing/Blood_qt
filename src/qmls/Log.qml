import QtQuick 2.0
import "customCtrls"

Item {  
    id: rootlog
    property alias btnQuitLog: btnQuitLog

    width: 1270
    height: 650
    visible: false

    MyColors{
        id:g_color
    }

    property var rsltTableArray:
        [["结束时间","操作者条码","献血条码","耗材条码","抗凝剂条码","保养液条码",
          "全血量", "血浆量", "悬红量", "保养液量","抗凝剂量","总时长","状态"],
        [200,120,120,120,120,120,100,100,100,100,100,100,50],
        ["bgtime", "nID","dID","dposlId", "acId", "prsvId", "bldVlm",
         "plsmVlm", "SRBCVlm", "prsvVlm","acVlm", "timeLen_e", "status"]]

    RsltTableView {
        id: table;
//        anchors.fill: parent
        anchors.topMargin: 60
        width: 1200
        height: 550
        anchors.centerIn: parent
        anchors.margins: 18
        Component.onCompleted: {
            console.log("mytableview")
            table.updateColumn2Table(rootlog.rsltTableArray);    //创建表
        }
    }

    CustomButton {
        id: btnQuitLog
        x: 1100
        y: 620
        width: 100
        height: 80
        text: "退出"

        bgColor: g_color.bg
        bHasIcon: true
        btnIcon.source: "/res/pics/exit.png"
    }
}
