import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import "customCtrls" as MyCtrls
import UiAdaptor 1.0
import SerialTest 1.0


RunningPageForm {
   // property alias blood: blood
    property alias preparation: preparation
   // property alias exit: exit
    property alias popupon: popupon
    property alias alarmMsg: alarmMsg
    property alias alarmR: alarmR

    id :runningView

    signal swiped()

    retrySafeT.onClicked: {
        uiAdaptor_running.bootChkFailed()
        retrySafeT.visible = false
        safeTest_err.text = ""
        safeTest_msg.text = ""
    }

    buttonfillfailed.onClicked: {
        uiAdaptor_running.fillfailed()
        buttonfillfailed.visible = false
    }

    btnCfmACD.onClicked: {
        uiAdaptor_running.confirmACDRdy();
    }

    btnCfmLine.onClicked: {
        uiAdaptor_running.confirmLine();
    }

    btnDraw.onClicked: {
        btnDraw.visible = false;
        clearPages()       
        pgBar.value = "0"
        label_bldVlm.text = "0"
        timeLen.text = "0"
        //collectionVlmall.text= "0"
        uiAdaptor_running.startDrawing()
    }
    /////////////////////////////////////////////////////////////报警弹出选项
    Rectangle {
        id : alarmR
        color: "red"
        x:340
        y:0
        width: 600
        height: 50

        visible: false
        MyCtrls.MyLabel {
            id: alarmMsg
            color :"black"
            font.pixelSize: 28
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("泵速过快!!!")
        }
        Button {
            //  anchors.centerIn: parent
            id: help    //帮助
            y: 5
            text: "帮助"
            anchors.right: parent.right
            anchors.rightMargin: 8
            style:ButtonStyle{ // 可以不要 style 直接 background
                background:Rectangle{
                    implicitWidth:70
                    implicitHeight:40
                    radius: 2
                    color:"lightgray"
                    border.width:control.press?4:2
                    border.color:(control.hovered||control.pressed)?"blue":"green"
                }
            }
            onClicked: {
                msgDialog.openMsg();
            }
        }
        MsgDialog {
            id: msgDialog
            tipText: qsTr("QML")
        }
    }
    Rectangle {
        id: popupon
        width: 300
        height: 150
//        x: 500
//        y: 300
        anchors.centerIn:parent
        //color: "#2F4F4F"
        color:Qt.rgba(0.5,0.5,0.5,0.9)    //透明
        visible: false
        radius: 5
        Button {
            id: preparation
            x: 100
            y: 50

            text:"继续"
            style:ButtonStyle{ // 可以不要 style 直接 background
                background:Rectangle{
                    implicitWidth:100
                    implicitHeight:50
                    radius: 3
                    color:"lightgray"
                    border.width:4
                    border.color:"blue"
                }
            }

                onClicked: {
                    bloodhide();
                    rbcVlmPgbar.visible = false
                    pgBar.visible = true
                    myLabel.visible = true
                    label_bldVlm.visible = true
                    myLabel6.visible = true
                    toID.visible = false

                }
            }
    }
    //////////////////////////////////////////////////////////////
    startDraw.onClicked: {
        console.log(Date.now().toString() + "  start click")
        uiAdaptor_running.startDrawProc()
        toSettingPage.visible = true
        toSetting.visible = false
        blood_code.text = qsTr("")
        consu_code.text = qsTr("")
        anti_code.text = qsTr("")
        maintenance_code.text  = qsTr("")
    }


    ///////////////////////////////////////////////////
    ////////////血泵控制////////////////////////////////

    add.onClicked: {
  //      var bldS = pumpSpeed.text
        uiAdaptor_running.bldSpeedAdd();
    }

    reduce.onClicked: {
  //      var bldS = pumpSpeed.text;
        uiAdaptor_running.bldSpeedReduce();
    }

    stop.onClicked: {
        if(stop.status === 1)
        {
            stop.status = 0;
      //      var bldS = pumpSpeed.text;
            uiAdaptor_running.bldSpeedStart();
         //   stop.btnIcon.source =  "/res/pics/continue.png"
            stop.btnIcon.source =  "/res/pics/pause.png"
        }
        else
        {
            stop.status = 1;
            uiAdaptor_running.bldSpeedStop();
           // stop.btnIcon.source =  "/res/pics/pause.png"
            stop.btnIcon.source =  "/res/pics/continue.png"
        }

    }
    enriadd.onClicked: {
        uiAdaptor_running.bldSpeedAdd();
    }

    enrireduce.onClicked: {
        uiAdaptor_running.bldSpeedReduce();
    }

    enristop.onClicked: {
        if(enristop.status === 1)
        {
            enristop.status = 0;
            uiAdaptor_running.bldSpeedStart();
            enristop.btnIcon.source =  "/res/pics/pause.png"
        }
        else
        {
            enristop.status = 1;
            uiAdaptor_running.bldSpeedStop();
            enristop.btnIcon.source =  "/res/pics/continue.png"
        }

    }

    add1.onClicked: {
          uiAdaptor_running.colNPadd();
    }
    reduce1.onClicked: {
        uiAdaptor_running.colNPred();
    }
    stop1.onClicked: {

        if(stop1.status === 1)
        {
            stop1.status = 0;
            uiAdaptor_running.colNPsta();
            stop1.btnIcon.source =  "/res/pics/pause.png"
        }
        else
        {
            stop1.status = 1;
            uiAdaptor_running.colNPstop();
            stop1.btnIcon.source =  "/res/pics/continue.png"
        }

    }

    //////////////////////////////////////////////////////////

    /////结束界面
    btnUpload.onClicked: {
        console.log("btnUpload click ")
        uiAdaptor_running.quitselftest();

        var consequence = new Array(12);
        consequence[0] = label_collectionVlm.text//label_donorCode.text;
        consequence[1] = label_enrivlm.text//label_disposableCode.text;
        consequence[2] = label_timeLen.text//label_ACDCode.text;
//        consequence[3] = ""//label_presvCode.text;

//        consequence[4] = ""//label_operatorCode.text;
//        consequence[5] = ""//label_presvVlm1.text;
//        consequence[6] = label_timeLen1.text;
//        consequence[7] = label_dpmVlm_e.text;
//        consequence[8] = ""//label_plsmVlm_e.text;
//        consequence[9] = ""//label_RBCVlm_e.text;
//        consequence[10] = "";//label_ACDVlm1.text;
//        consequence[11] = ""//label_statelabel.text;
        uiAdaptor_running.saveConsequence(consequence);

        toStandBy()
        toSettingPage.visible = true

    }

    btnOK.onClicked: {
        uiAdaptor_running.quitselftest();
        toSettingPage.visible = true
        toStandBy()
    }

    btnQuitself.onClicked: {
        uiAdaptor_running.quitselftest()
        toSettingPage.visible = true
        toStandBy()
    }

    UiAdaptor{
        id: uiAdaptor_running

        onBloodChanged : {
            var a = newValue
                    if (a === 400){
                        paramSet.target.currentIndex = 0;
                    }
                    else if (a === 300){
                        paramSet.target.currentIndex = 1;
                    }
                    else if (a === 200)
                    {
                        paramSet.target.currentIndex = 2;
                    }
                    else if (a === 50)
                    {
                        paramSet.target.currentIndex = 3;
                    }
                    else if (a === 20)
                    {
                        paramSet.target.currentIndex = 4;
                    }
        //    target.currentText = newValue
        }

        onDrawspeedChanged: {
            paramSet.drawSpeed.text = newValue
        }

       onCollectspeedChanged: {
           paramSet.collectSpeed.text = newValue
       }

       onLinecoffChanged: {
           paramSet.lineCoeff.text = newValue
       }

       onBpaprateChanged: {
           var a = newValue
                   if (a === 2){
                       paramSet.comboBox_anti.currentIndex = 0;
                   }
                   else if (a === 3){
                       paramSet.comboBox_anti.currentIndex = 1;
                   }
                   else if (a === 4)
                   {
                       paramSet.comboBox_anti.currentIndex = 2;
                   }
                   else if (a === 5)
                   {
                       paramSet.comboBox_anti.currentIndex = 3;
                   }
                   else if (a === 6)
                   {
                       paramSet.comboBox_anti.currentIndex = 4;
                   }
                   else if (a === 7)
                   {
                       paramSet.comboBox_anti.currentIndex = 5;
                   }
                   else if (a === 8)
                   {
                       paramSet.comboBox_anti.currentIndex = 6;
                   }
                   else if (a === 9)
                   {
                       paramSet.comboBox_anti.currentIndex = 7;
                   }
                   else if (a === 10)
                   {
                       paramSet.comboBox_anti.currentIndex = 8;
                   }

   //        comboBox_anti.model = newValue
       }

       onPrsspeedChanged: {
           paramSet.presvVlmSpeed.text = newValue
       }

        onStopButtonPressed:{
            uiAdaptor_running.stoppress()
       //     popupon.visible = true
        }


        onShowSfChkMsg :{
            safeTest_msg.text = str
            toSetting.visible = false
            toSettingPage.visible = false

        }

        onSetCSS2StandBy: {
            clearPages();
            standBy.anchors.top = runningView.top;
            standBy.visible = true

            btnCfmLine.visible = false;
            btnDraw.visible = false;
            btnCfmACD.visible = false;
        }

        onSetCSS2SafeChk: {
            toSetting.visible = false
            toSettingPage.visible = false
            console.log("CSS2SafeChk")
            clearPages()
            safeTest.anchors.top = runningView.top;
//            // 移动字符串位置
//            safeTest_msg.anchors.centerIn = safeTest.Center

            safeTest.visible = true


        }

        onSetCSS2SafeChkFailed:{
         //   uiAdaptor_running.bootChkFailed()
            safeTest_err.text = errStr

            retrySafeT.visible = true;

        }


        onSetCSS2WaitCup : {
            safeChk_img.source = "/res/pics/bowl.gif";
            safeChk_img.visible = true;
            // 移动字符串位置
    //        safeTest_msg.anchors.top = safeChk_img.bottom

        }

        onSetCSS2WaitLine : {
            btnCfmLine.visible = true;
            btnDraw.visible = false;
            safeChk_img.visible = false;
        }

        onSetCSS2WaitACD : {
            safeChk_img.source = "/res/pics/filling.gif"
            safeChk_img.visible = true;
            btnCfmLine.visible = false;
            btnDraw.visible = false;
            btnCfmACD.visible = true;
        }


        onCssFillFailed:{
            toSetting.visible = false
            toSettingPage.visible = false
            buttonfillfailed.visible = true;

        }

        onSetCSS2Prime: {

            btnCfmACD.visible = false;

        }

        onSetCSS2ReadyDraw: {
            console.log("onSetCSS2ReadyDraw")
            clearpara();
            //safeChk_img.source = "/res/pics/needle.gif"
            safeChk_img.visible = true;
            btnCfmLine.visible = false;
            btnCfmACD.visible = false;
            btnDraw.visible = true
        }
        onSetCSS2Draw: {

            toSetting.visible = true
            toSettingPage.visible = false
            safeChk_img.visible = false;
            btnDraw.visible = false;

            clearPages()
            draw.anchors.top = runningView.top;
            draw.visible = true
            //statusLabel.text = qsTr("采集")
            statusLabel.text = qsTr("采集设置")
            pgBar.visible = true            
            myLabel.visible = true
            label_bldVlm.visible = true            
            myLabel6.visible = true
            //pgBar.value = "0"
            //label_bldVlm.text = "0"
            //timeLen.text = "0"

            rbcVlmPgbar.visible = false
            myLabel_rbc.visible = false
            rbcVlm.visible = false
            myLabel_rbc1.visible = false

           // presvVlm.text = 0

           // blood.visible = true

            toID.visible = false
            toSetting.visible = false

        }

//        onSetCSS2Washing: {
//            statusLabel.text = qsTr("洗涤")
//        }

        onSetCSS2Collect: {
            toSetting.visible = false
            toSettingPage.visible = false
            //statusLabel.text = qsTr("制备")
            statusLabel.text = qsTr("采集设置")
            rbcVlmPgbar.visible = true
            rbcVlmPgbar.value = "0"
            myLabel_rbc.visible = true
            rbcVlm.visible = true
            rbcVlm.text = "0"
            myLabel_rbc1.visible = true


            pgBar.visible = false
            myLabel.visible = false
            label_bldVlm.visible = false
            myLabel6.visible = false

            //blood.visible = false
            toID.visible = false
            toSetting.visible = false



        }

        onSetCSS2Halt: {

        }

        //采集结束，等到用户确认结果
        onSetCSS2CollectEnd: {
            toSetting.visible = false
            toSettingPage.visible = false
            clearPages()
            uiAdaptor_running.quitselftest();
            toSettingPage.visible = true
            toStandBy()
            //result.anchors.top = runningView.top;
            //result.visible = true
            idpageView.visible = false
            //label_RBCVlm_e.text = rbcVlm.text
            label_dpmVlm_e.text = bldVlm.text
            //label_plsmVlm_e.text = plsmVlm.text
            //label_presvVlm1.text =""// presvVlm.text
            //label_ACDVlm1.text = ""//acdVlm.text
            label_timeLen1.text = timeLen.text

            //label_donorCode.text =  blood_code.text
            //label_disposableCode.text = consu_code.text
            label_ACDCode.text = anti_code.text
            //label_presvCode.text = maintenance_code.text
            //label_operatorCode.text = user_code.text

            //label_statelabel.text = "1"
            toID.visible = false
            toSetting.visible = false


        }

        onSetCSSdrawpower: {
            safeChk_img.visible = false;
            btnDraw.visible = false;


            clearPages()
            draw.anchors.top = runningView.top;
            draw.visible = true
            //statusLabel.text = qsTr("采集")
            statusLabel.text = qsTr("采集设置")
            pgBar.visible = true
            pgBar.value = "0"
            myLabel.visible = true
            label_bldVlm.visible = true
            label_bldVlm.text = "0"
            myLabel6.visible = true

            popupon.visible = true
            timeLen.text = "0";

            rbcVlmPgbar.visible = false
            myLabel_rbc.visible = false
            rbcVlm.visible = false
            myLabel_rbc1.visible = false

            //presvVlm.text = 0

            //blood.visible = true

            toID.visible = false
        }

        onSetCSScollectpower: {
            safeChk_img.visible = false;
            btnDraw.visible = false;


            clearPages()
            draw.anchors.top = runningView.top;
            draw.visible = true
            //statusLabel.text = qsTr("制备")
            statusLabel.text = qsTr("采集设置")
            rbcVlmPgbar.visible = true
            rbcVlmPgbar.value = "0"
            myLabel_rbc.visible = true
            rbcVlm.visible = true
            rbcVlm.text = "0"
            myLabel_rbc1.visible = true
            popupon.visible = true

            pgBar.visible = false
            myLabel.visible = false
            label_bldVlm.visible = false
            myLabel6.visible = false

            //blood.visible = false
            toID.visible = false
        }

        /////// 采集界面

        //“压力”更新信号
        onPressureOfDpmChanged : {
            textInput_dpm.value = newValue/10;
        }

        onNegapressureOfDpmChanged :{
            textInput_dpm_false.value = a/10;
        }

        //“血浆量更新”信号
        onVolumeOfPlasmaChanged : {
            //collectionVlm.text=newValue
            //plsmVlm.text = newValue/10;
        }
        //“抗凝剂量更新”信号
        onVolumeOfACDChanged : {
            //acdVlm.text = newValue/10;
        }
        //“血泵流速更新”信号
        onFlowRateOfBloodPumpChanged : {
            pumpSpeed.text = newValue;
            pumpSpeed2.text = newValue;
        }
        //"保养液泵速度更新"
        onFlowRateOfPresvPumpChanged:{
            preserSpeed.text=newValue;
        }
        //“离心机转速更新”信号
        onSpeedOfCentrifugeChanged: {
            centrifugeSpeed.text = newValue;
            centrifugeSpeed1.text = newValue;
        }
        //“盐水量更新”信号
        onVolumeOfNaClChanged :{
            //naclVlm.text = newValue
           // enrivlm.text=newValue
        }
        //“全血采集量量更新”信号
        onVolumeOfBloodChanged : {
            bldVlm.text = newValue
            label_bldVlm.text=newValue
            collectionVlm.text=newValue
        }
        //“全血采集pgbar量更新”信号
        onVolumeOfBloodPgbarChanged:{
            pgBar.value = newValue

        }

        //“保养液量更新”信号
        onVolumeOfPresvChanged : {
            //presvVlm.text = newValue
            //enrivlm.text=newValue
        }

        //“悬红量更新”信号        
        onVolumeOfSRBCChanged : {
            //console.log("qml浓缩量:",newValue)
            rbcVlm.text = newValue
            enrivlm.text=newValue
        }
        //“悬红量Pgbar更新”信号
        onVolumeOfSRBCPgbarChanged : {
            rbcVlmPgbar.value = newValue

        }

        //“开机时长”信号
//        onTimeLenChanged : {
//            timeLen.text = newValue
//        }
        onCollecttimeChanged : {
            timeLen.text = newValue
        }
         onSetCSScontinueOrover :{
             overView.open()
         }

        onRaiseAlarm: {
            console.log(str)
            console.log(lv)
            if (1 === lv) //不栓锁
            {
                alarmMsg.text = qsTr("!!!") + str
                msgDialog.tipText = qsTr("!") + details
                alarmR.color = "yellow"
                alarmR.visible = true

                idpageView.visible = false;
                paramSet.visible = false
                draw.visible = true
                toID.visible = false;
                toSetting.visible = false;


            }
            else if(2 === lv)//栓锁
            {
                alarmMsg.text = qsTr("!!") + str
                msgDialog.tipText = qsTr("!") + details
                alarmR.color = "red"
                popupon.visible = true
                alarmR.visible = true

                idpageView.visible = false;
                paramSet.visible = false
                draw.visible = true
                toID.visible = false;
                toSetting.visible = false;


            }
            else
            {
                popupon.visible = false
            }
        }

        onCancelAlarm: {
            alarmR.visible = false

        }
    }



    function clearPages()
    {
        safeChk_img.visible = false;
        draw.visible  = false;
        selfTest.visible = false;
        safeTest.visible = false;
        standBy.visible  = false;
        result.visible   = false;
        enrichment.visible=false;
        //To do
    }

    function clearpara()
    {
        rbcVlm.text = "0";
        bldVlm.text = "0";
        //plsmVlm.text = "0";
       // presvVlm.text = "0";
        //acdVlm.text = "0";
        timeLen.text = "0";

        blood_code.text = "";
        consu_code.text = "";
        anti_code.text = "";
        maintenance_code.text = "";
        user_code.text = "";
    }

    function bloodhide(){
        if(alarmR.visible == false)
        {
            uiAdaptor_running.bldSpeedStart()
            uiAdaptor_running.colNPsta()
            popupon.visible = false
            uiAdaptor_running.dbSetBool( 0, 1);
        }

    }

    SerialTest {
        id:serial

        onReceivedataChanged: {
            var list = colu_code.children

            console.log("count: " + list.length);
            for ( var i in list) {
                if(list[i].text === "")
                {
                    list[i].text = receipivedata
                    break;
                }
            }

        }


    }

    MyCtrls.CustomButton{
        id : toSetting

        height: 110
        width:  100
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        bgColor: "#404040"
        bHasIcon: true
        btnIcon.source: "/res/pics/right.png"
        text : qsTr("设置")
    }

    MyCtrls.CustomButton{
        id : toSettingPage

        height: 110
        width:  100
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        bgColor: "#404040"
        bHasIcon: true
        btnIcon.source: "/res/pics/right.png"
        text : qsTr("设置")
    }

    MyCtrls.CustomButton{
        id : toID
        height: 110
        width:  100
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6

        bgColor: "#404040"
        bHasIcon: true
        btnIcon.source: "/res/pics/left.png"

        text : qsTr("ID")
        visible: false
    }

    Connections{
        target: toID
        onClicked: {
            serial.openAndSetPort(0,3,3,0,0,0)
            serial.sendto();
            draw.visible = false
            idpageView.anchors.top = draw.top;
            idpageView.visible = true;
            toID.visible = false;
            title_ID.visible = true;
            toSetting.visible = false;
        }
    }

    btnQuitId.onClicked: {
        serial.closePort()
        idpageView.visible = false;
        draw.visible = true
        toID.visible = false
        toSetting.visible = false;
    }
    Connections{
        target: toSetting
        onClicked: {
            draw.visible = false
            paramSet.anchors.top = draw.top;
            paramSet.visible = true;
            toSetting.visible =false;
            toID.visible = false;
            toSetting.visible = false;
        }
    }

    Connections {
        target: toSettingPage
        onClicked: {
            if(popupon.visible === false && alarmR.visible === false)
            {
                runningView.swiped();
            }
        }
    }





    function toStandBy()
    {
        clearPages()
        standBy.anchors.top = runningView.top;
        standBy.visible = true
        toID.visible = false
    }

    Component.onCompleted: {
        //        clearPages()
        //        standBy.anchors.top = runningView.top;
        //        standBy.visible = true
        //        clearPages()
        //        safeTest.anchors.top = runningView.top;
        //        safeTest.visible = true
        //    }

    }

    Paramt{
        id: paramSet
        visible: false
        anchors.horizontalCenter: draw.horizontalCenter
        btnOK_param.onClicked: {
            if(drawSpeed.text > 100 || drawSpeed.text < 20 ||
                    collectSpeed.text > 200 || collectSpeed.text < 20 ||
                    presvVlmSpeed.text > 100 || presvVlmSpeed.text < 2 ||
                    lineCoeff.text > 100 || lineCoeff.text < 0)
            {
                popup_error.visible = true;
            }
            else
            {
                draw.visible = true
                paramSet.visible = false;
                toID.visible = false;
                toSetting.visible = false;

                var num1 = (btnOK_param) ? target.currentText : 0;
                var num2 = (btnOK_param) ? drawSpeed.text : 0;
                var num3 = (btnOK_param) ? collectSpeed.text : 0;
                var num4 = (btnOK_param) ? comboBox_anti.currentText :0;
                var num5 = (btnOK_param) ? lineCoeff.text :0;
                var num6 = (btnOK_param) ? presvVlmSpeed.text :0;
                uiAdaptor_running.paramOK(num1,num2,num3,num4,num5,num6);
                uiAdaptor_running.paramsave(num1,num2,num3,num4,num5,num6);
            }
        }


        btnDiscard_param.onClicked: {
            draw.visible = true
            paramSet.visible = false;
            toID.visible = false;
            toSetting.visible = false;
        }
    }


    skip.onClicked:{
        uiAdaptor_running.colNext();
        draw.visible = false;
        enrichment.anchors.top = runningView.top;
        enrichment.visible = true;
        toSetting.visible =false;
        toID.visible = false;
        enristop.btnIcon.source =  "/res/pics/pause.png"
    }
    over.onClicked:{
        overView.open()
    }
    Drawer {
        id: overView
        width: 1280
        height: 800
        modal: true
        clip: true
        //抽屉起始方向
        edge: Qt.LeftEdge
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        background: Rectangle{
            anchors.fill: parent
            color: "#565656"
            opacity: 0.8
        }

        Rectangle {
            x: 440
            y: 300
            height: 200
            width: 400
            color: "#F8F8FF"
            radius: 20
            Rectangle {
                x: 0
                y :146
                height: 2
                width: 400
                color: "#B0C4DE"
            }

            Rectangle {
                x: 199
                y :146
                height: 55
                width: 2
                color: "#B0C4DE"
            }

            Label{
                id: over_lab
                x: 8
                y: 8
                width: 384
                height: 132
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: "继续采集or完成浓缩"
            }

            Button {
                id: over_continue
                x: 21
                y: 149
                width: 100
                height: 50
                 style:ButtonStyle{
                background: Rectangle {
                    anchors.fill: parent
                    color: "#F8F8FF"
                }
              }
                Text {
                    x: 40
                    y: 10
                    text: qsTr("继续")
                    color: "#1E90FF"
                    font.pointSize: 12
                }
                onClicked: {
                    draw.anchors.top = runningView.top
                    draw.visible=true
                    enrichment.visible=false
                    uiAdaptor_running.popupalarmblood()
                    stop1.btnIcon.source =  "/res/pics/pause.png"
                    stop.btnIcon.source =  "/res/pics/pause.png"
                    overView.close()
                }
            }
            Button {
                id: over_cancle
                x: 141
                y: 149
                width: 100
                height: 50
                style:ButtonStyle{
                background: Rectangle {
                    color: "#F8F8FF"
                }
              }
                Text {
                    x: 57
                    y: 10
                    text: qsTr("取消")
                    color: "#1E90FF"
                    font.pointSize: 12
                }
                onClicked: {
                    overView.close()
                }
            }

            Button {
                id: over_OK
                x: 261
                y: 149
                width: 100
                height: 50
                style:ButtonStyle{
                background: Rectangle{
                     color: "#F8F8FF"
                }
               }
                Text {
                    x: 52
                    y: 10
                    text: qsTr("结束")
                    color: "#1E90FF"
                    font.pointSize: 12
                }
                onClicked: {
                    uiAdaptor_running.endCollect()
                    toStandBy()
                    overView.close()
                    enrivlm.text="0"
                }
            }
        }
    }

}

