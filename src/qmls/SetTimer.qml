import QtQuick 2.4
import QtQuick.Controls 2.2

import "customCtrls"

Item {
    id: setTime
    property alias btnSaveSetTimer: btnSaveSetTimer
    property alias btnQuitSetTimer: btnQuitSetTimer
    property string timeStr: ""
    property string targetTimeStr: ""
    property date curDate

    property int curYear: 2018

    width: 1260
    height: 700

    MyColors {
        id : cs_color
    }

    function init(){
        curDate = new Date();
        timeStr = Qt.formatDateTime(curDate, "yyyy/MM/dd  hh:mm");
    }

    function formatText(count, modelData) {
        var data = modelData;
        return data.toString().length < 2 ? "0" + data : data;
    }

    function generateIntArray(bg, end) {
        if (bg > end){
            var tmp = bg;
            bg = end;
            end = tmp;
        }

        var rtArray = new Array();
        var i = 0;
        while (i <= end - bg){
            rtArray[i] = bg + i;
            i++;
        }

        return rtArray;
    }

    function updateTimeStr() {
        var newDate = new Date();
        newDate.setFullYear(yearTumbler.currentIndex + curYear);
        newDate.setMonth(monthTumbler.currentIndex);
        newDate.setDate(dayTumbler.currentIndex + 1);

        newDate.setHours(hoursTumbler.currentIndex);
        newDate.setMinutes(minutesTumbler.currentIndex);

        timeStr = Qt.formatDateTime(newDate, "yyyy/MM/dd  hh:mm");
        targetTimeStr = Qt.formatDateTime(newDate, "yyyy-MM-dd hh:mm:00");
    }

    function updateDayModel(){
        var y = yearTumbler.currentIndex + curYear;
        if (y < curYear)
            y = curDate.getUTCFullYear();

        var m = monthTumbler.currentIndex + 1
        if (m <= 1)
            m = curDate.getMonth() + 1;

        dayTumbler.model = generateIntArray(1, getdays(y, m));
    }

    function getdays(year, month) {
        var newDate = new Date();
        newDate.setFullYear(year);
        newDate.setMonth(month);

        newDate.setDate(0);
        return newDate.getDate();
    }

    function getSetTimeStr(){
        var cmd = "sudo date --s=";
        cmd += "\""+targetTimeStr+"\"";

        console.log(cmd);
        return cmd;
    }

    FontMetrics {
        id: fontMetrics
    }

    Component {
        id: delegateComponent

        MyLabel {
            font.pixelSize: 40
            font.bold: false

            text: formatText(Tumbler.tumbler.count, modelData)
            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
        }
    }

    Frame {
        id: frame

        width: 1000
        height: 500
        anchors.centerIn: parent

        MyLabel{
            id: curTimeLabel
            anchors.horizontalCenter: parent.horizontalCenter

            font.pixelSize: 36
            font.bold: true

            horizontalAlignment: Text.AlignHCenter
            text: timeStr
        }

        Row {
            id: row
            spacing: 30
            anchors.centerIn: parent

            Tumbler {
                id: yearTumbler
                width: 150
                height: 250
                model: generateIntArray(curYear, 2099)
                delegate: delegateComponent
                currentIndex: curDate.getFullYear() - curYear

                onCurrentItemChanged: {
                    updateDayModel()
                    updateTimeStr()
                }
            }

            Tumbler {
                id: monthTumbler
                width: 100
                height: 250
                model: generateIntArray(1, 12)
                delegate: delegateComponent
                currentIndex: curDate.getMonth()

                onCurrentItemChanged: {
                    updateDayModel()
                    updateTimeStr()
                }
            }
            Tumbler {
                id: dayTumbler
                width: 100
                height: 250
                model: generateIntArray(1, 31)
                delegate: delegateComponent
                currentIndex: curDate.getDate() - 1

                onCurrentItemChanged: updateTimeStr()
            }

            Tumbler {
                id: hoursTumbler
                model: 24
                width: 100
                height: 250
                delegate: delegateComponent
                currentIndex: curDate.getHours()

                onCurrentItemChanged: updateTimeStr()
            }

            Tumbler {
                id: minutesTumbler
                width: 100
                height: 250
                model: 60
                delegate: delegateComponent
                currentIndex: curDate.getMinutes()

                onCurrentItemChanged: updateTimeStr()
            }
        }
    }

    CustomButton {
        id: btnQuitSetTimer
        x: 1100
        y: 620
        width: 100
        height: 80
        text: "退出"

        bgColor: "#404040"
        bHasIcon: true
        btnIcon.source: "/res/pics/exit.png"
    }

    CustomButton {
        id: btnSaveSetTimer
        x: 950
        y: 620

        text: qsTr("保存")

        width: 100
        height: 80

        bgColor: "#404040"
        bHasIcon: true
        btnIcon.source: "/res/pics/save.png"
    }

    Component.onCompleted: {
        init()
        updateTimeStr()
    }
}
