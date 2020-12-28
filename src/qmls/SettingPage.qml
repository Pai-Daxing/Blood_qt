import QtQuick 2.4

import "customCtrls" as MyCtrls
//import QtQuick.Controls 2.2
import UiAdaptor 1.0

import QtQuick.Controls 2.0
//import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import Network 1.0

import "Parame.js" as Parame

SettingPageForm {
    id :form

    signal swiped()

    signal bcodeopen()
    signal bcodeclose()

    signal ccodeopen()
    signal ccodeclose()

    signal acodeopen()
    signal acodeclose()

    signal pcodeopen()
    signal pcodeclose()

    signal ucodeopen()
    signal ucodeclose()

    function changeTitlestr(str){
        title_text.text = str;
    }

    function restoreTitlestr(){
        title_text.text = qsTr("设置");
    }

    //    SqlQueryModel{
    //        id:sqlquery
    //    }

    Network {
        id: netwifi

        onWlanFound: {
            comboBox_wifi.model = list
        }

        onLocalname: {
            input_ip.text = localHostName
        }

        onIpaddress: {
            input_netmask.text = add
        }
    }

    //////////////////////////////////////////////////////////////////////
    //////// mainSetting
    //////////////////////////////////////////////////////////////////////
    btnParam.onClicked: {
        mainSetting.visible = false;
        paramSet.anchors.top = form.top;
        paramSet.visible = true;
        toRunPage.visible = false
        changeTitlestr("")
        //  initParams();
    }

    btnLog.onClicked: {
        sqlquery.refresh();
        mainSetting.visible = false;
        logView.anchors.top = form.top;
        logView.visible = true;
        changeTitlestr(btnLog.text)

        toRunPage.visible = false
    }

    btnSetTime.onClicked: {
        mainSetting.visible = false;
        timeSetView.anchors.top = form.top;
        timeSetView.visible = true;
        changeTitlestr(btnSetTime.text)

        timeSetView.init();
        toRunPage.visible = false
    }


    btnMaintian.onClicked: {
        mainSetting.visible = false;
        loginView.anchors.top = form.top;
        loginView.visible = true;
        changeTitlestr("登录")
        toRunPage.visible = false
    }

    btnVersion.onClicked: {
        mainSetting.visible = false;
        versionView.anchors.top = form.top;
        versionView.visible = true;
        changeTitlestr(btnVersion.text)

        title_text.visible = qsTr("关于本机");
        toRunPage.visible = false
    }

    btnWifi.onClicked: {
        netwifi.myOpenWlan();
        mainSetting.visible = false;
        wifiView.anchors.top = form.top;
        wifiView.visible = true;

        changeTitlestr(btnWifi.text)
        toRunPage.visible = false
        netwifi.getip();
    }

    btnBootSelf.onClicked: {
        mainSetting.visible = false;
        bootselfView.anchors.top = form.top;
        bootselfView.visible = true;

        //    changeTitlestr(btnBootSelf.text);
        title_text.text = qsTr("");
        toRunPage.visible = false
    }
    ///////////////////////sysconfig/////////////////
    btnsysconfig.onClicked: {
        mainSetting.visible = false;
        sysconfigView.anchors.top = form.top;
        sysconfigView.visible = true;

        changeTitlestr(btnsysconfig.text)
        toRunPage.visible = false

    }

    switch_Bcode.onCheckedChanged: {
        if(switch_Bcode.checked == true)
        {
            form.bcodeopen();
            console.log("send_signal")
        }
        else
        {
            form.bcodeclose();
            console.log("close_signal")
        }
    }

    switch_Ccode.onCheckedChanged: {
        if(switch_Ccode.checked == true)
        {
            form.ccodeopen();
        }
        else
        {
            form.ccodeclose();
        }
    }

    switch_Acode.onCheckedChanged: {
        if(switch_Acode.checked == true)
        {
            form.acodeopen();
        }
        else
        {
            form.acodeclose();
        }
    }

    switch_Pcode.onCheckedChanged: {
        if(switch_Pcode.checked == true)
        {
            form.pcodeopen();
        }
        else
        {
            form.pcodeclose();
        }
    }

    switch_Ucode.onCheckedChanged: {
        if(switch_Ucode.checked == true)
        {
            form.ucodeopen();
        }
        else
        {
            form.ucodeclose();
        }
    }

    btnexit_config.onClicked: {
        mainSetting.visible = true;
        sysconfigView.visible = false;

        restoreTitlestr();
        toRunPage.visible = true
        //TODO  quit cmd
    }
    ///////////////////////////////////////////////////
    btnSca.onClicked: {
        uiAdaptor.scaledstart()
        mainSetting.visible = false;
        scaledView.anchors.top = form.top;
        scaledView.visible = true;

        changeTitlestr(btnSca.text);
        toRunPage.visible = false

    }

    // mainSetting  end///////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////


    /////////// Maintain  ///////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    btnNetSet.onClicked: {
    }
    btnDebug.onClicked: {
        uiAdaptor.starDebug();
        mainTain.visible = false;
        dbView.anchors.top = form.top;
        dbView.visible = true;

        changeTitlestr(btnDebug.text)
        toRunPage.visible = false
    }


    btnSysParam.onClicked: {
        mainTain.visible = false;
        sysParamView.anchors.top = form.top;
        sysParamView.visible = true;

        changeTitlestr(btnSysParam.text)
        toRunPage.visible = false
    }

    btnRestore.onClicked: {
    }
    btnOK_Maintain.onClicked: {

        mainSetting.visible = true;
        mainTain.visible = false;

        restoreTitlestr();
        toRunPage.visible = true
        //To do
    }

    btnChangedPasswd.onClicked: {
        mainTain.visible = false;
        passwdchangedView.anchors.top = form.top;
        passwdchangedView.visible = true;

        changeTitlestr(btnChangedPasswd.text)
        toRunPage.visible = false


    }

    ////////////////////////////////////////////////////////////////////////////
    ///////////// Log
    ///////////////////////////////////////////////////////////////////////////
    Log {
        id: logView
        //        anchors.margins: 40

        btnQuitLog.onClicked: {
            mainSetting.visible = true;
            logView.visible = false;

            restoreTitlestr();
            toRunPage.visible = true
        }
    }

    ////////////// paramSet  /////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    Paramt{
        id: paramSet
        visible: false
        anchors.horizontalCenter: form.horizontalCenter
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
                mainSetting.visible = true;
                paramSet.visible = false;

                var num1 = (btnOK_param) ? target.currentText : 0;
                var num2 = (btnOK_param) ? drawSpeed.text : 0;
                var num3 = (btnOK_param) ? collectSpeed.text : 0;
                var num4 = (btnOK_param) ? comboBox_anti.currentText :0;
                var num5 = (btnOK_param) ? lineCoeff.text :0;
                var num6 = (btnOK_param) ? presvVlmSpeed.text :0;
                uiAdaptor.paramOK(num1,num2,num3,num4,num5,num6);
                uiAdaptor.paramsave(num1,num2,num3,num4,num5,num6);

                toRunPage.visible = true
            }
        }

        btnDiscard_param.onClicked: {
            mainSetting.visible = true;
            paramSet.visible = false;
            toRunPage.visible = true
        }
    }

    MyCtrls.CustomButton{
        id : toRunPage
        height: 110
        width:  100
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6

        bgColor: "#404040"
        bHasIcon: true
        btnIcon.source: "/res/pics/left.png"

        text : qsTr("运行")
    }

    ////////////// paramSet  end/////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////


    btnQuitVer.onClicked: {
        mainSetting.visible = true;
        versionView.visible = false;

        restoreTitlestr();
        toRunPage.visible = true
        //TODO  quit cmd
    }

    scan.onClicked: {
        netwifi.myScanWlan()
    }

    connect.onClicked: {
        var UserName = input_name.text
        var psk = input_password.text
        netwifi.mySetWlan(UserName,psk)
        connectOK.visible = true
    }

    btnQuitWifi.onClicked: {
        mainSetting.visible = true;
        wifiView.visible = false;

        restoreTitlestr();
        toRunPage.visible = true
        //TODO  quit cmd

    }

    ////////////////////////////////////////////////////////////////////////////
    ///////////   自检
    ///////////////////////////////////////////////////////////////////////////
    UiAdaptor{
        id: uiAdaptor

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

        onShowSelftTestAirDs :{
            setselfTest_animated.visible = false

            console.log("空探自检开始")
            setselfAirDs.color = "#0000FF"
            setselfTest.anchors.top = form.top;
        }
        onShowSelftTestVlvs: {
            setselfVlvs.color = "#0000FF"
        }

        onShowSelftTestPumps: {
            setselfPumps.color = "#0000FF"
        }

        onShowSelftTestline: {
            setselfline.color = "#0000FF"
        }

        onShowSelftTestCF: {
            setselfCF.color = "#0000FF"
        }

        onShowSelftTestDPM:{
            setselfDPM.color = "#0000FF"
        }

        onShowSelftTestScales: {
            setselfScales.color = "#0000FF"
        }

        onShowSelftTestleak: {
            setselfleak.color = "#0000FF"
        }

        onSetCSS2WaitCoverOpen:{
            console.log("请打开盖开关")
            setselfCoverOpen.color = "#0000FF"

            setselfTest_animated.source  = "/res/pics/open_cover.gif"
            setselfTest_animated.anchors.centerIn = setselfTest.Center
            setselfTest_animated.visible = true
        }

        onSetCSS2WaitCoverClose:{
            console.log("请关闭盖开关")
            setselfCoverClose.color = "#0000FF"

            setselfTest_animated.source = "/res/pics/close_cover.gif"
            setselfTest_animated.anchors.centerIn = setselfTest.Center
            setselfTest_animated.visible = true
        }

        onSetCSS2SelfTestFailed:{
            //                setselfTest_err.visible = true
            //                setselfTest_err.text = errStr

            //                setretrySelfT.visible = true;
            mess_selftest.open()
            lab_SF.text = "警告\n" + errStr

        }

        onSetCSS2Succeed:{
            //      setclearPages();
            bootselfok.visible = true;
            //     setselfTest_msg.text = qsTr("自检成功")

        }
        onVersionChanged:{
            textInput_third.text = newValue
            console.log(newValue)

        }
    }
    function setclearcolor()
    {
        setselfCoverOpen.color = "#ffffff"
        setselfCoverClose.color = "#ffffff"
        setselfAirDs.color = "#ffffff"
        setselfVlvs.color = "#ffffff"
        setselfPumps.color = "#ffffff"
        setselfline.color = "#ffffff"
        setselfCF.color = "#ffffff"
        setselfDPM.color = "#ffffff"
        setselfScales.color = "#ffffff"
        setselfleak.color = "#ffffff"
    }
    bootself.onClicked: {
        uiAdaptor.bootSelfTest();
        //   bootself.visible = false
        bootselfView.visible = false
        setselfTest.visible = true
        setselfTest.anchors.top = form.top;
    }

    bootselfok.onClicked: {
        bootselfok.visible = false;
        setclearcolor()
        setselfTest.visible = false
        bootselfView.visible = true
    }

    setretrySelfT.onClicked: {
        uiAdaptor.startSelfTest()
        setretrySelfT.visible = false
        setselfTest_err.text = ""
        setclearcolor()
    }

    bootselfexit.onClicked: {
        mainSetting.visible = true;
        bootselfView.visible = false;
        bootselfok.visible = false
        bootself.visible = true
        setclearcolor()
        restoreTitlestr();
        toRunPage.visible = true
        //TODO  quit cmd

    }
    setselfTestexit.onClicked: {
        setclearcolor()
        uiAdaptor.bootQuit();
        bootselfView.visible = true;
        setselfTest.visible = false;
        setselfTest_animated.visible = false;
        setselfTest_err.visible = false;
        setretrySelfT.visible = false;
        bootselfok.visible = false;
        setselfTest_msg.visible = false
        toRunPage.visible = true
    }

    ////////////////////////////////////////////////////////////////////////////
    ///////////   SetTime
    ///////////////////////////////////////////////////////////////////////////
    SetTimer{
        id:timeSetView
        visible: false
        anchors.horizontalCenter: form.horizontalCenter

        btnQuitSetTimer.onClicked: {
            mainSetting.visible = true;
            timeSetView.visible = false;
            restoreTitlestr();
            toRunPage.visible = true
        }

        btnSaveSetTimer.onClicked: {
            //TODO
            var cmd = getSetTimeStr();

            uiAdaptor.execCmd(cmd);
            mainSetting.visible = true;
            timeSetView.visible = false;
            restoreTitlestr();
            toRunPage.visible = true
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    ///////////// Debug
    ///////////////////////////////////////////////////////////////////////////
    Debug{
        id:dbView
        visible: false
        anchors.horizontalCenter: form.horizontalCenter

        btnQuitDebug.onClicked: {
            uiAdaptor.exitDebug();
            switch_centri.checked = false;
            switch_bldVlv.checked = false;
            switch_RBCVlv.checked = false;
            switch_plasmaVlv.checked = false;
            switch_wasteVlv.checked = false;
            switch_prsvVlv.checked = false;
            switch_naclVlv.checked = false;
            switch_BP.checked = false;
            switch_BP_Dir.checked = false;
            switch_NP.checked = false;
            switch_AP.checked = false;

            mainTain.visible = true;
            dbView.visible = false;

            changeTitlestr(btnMaintian.text);
            //TODO  quit cmd
        }
    }

    Connections {
        target: toRunPage
        onClicked: {
            form.swiped();
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // SysParam
    ///////////////////////////////////////////////////////////////////////////
    SysParam{
        id:sysParamView
        visible: false
        anchors.horizontalCenter: form.horizontalCenter

        btnQuitSysParam.onClicked: {
            mainTain.visible = true;
            sysParamView.visible = false;

            changeTitlestr(btnMaintian.text);
            //TODO  quit cmd

        }
    }

    Connections {
        target: toRunPage
        onClicked: {
            form.swiped();
        }
    }

    Connections {
        target: toRunPage
        onClicked: {
            form.swiped();
        }
    }

    Scaled{
        id:scaledView
        visible: false
        anchors.horizontalCenter: form.horizontalCenter

        btnQuitScaled.onClicked: {
            uiAdaptor.scaledexit()
            mainSetting.visible = true;
            scaledView.visible = false;

            restoreTitlestr();
            toRunPage.visible = true
            //TODO  quit cmd

        }
    }

    Login{
        id:loginView
        visible: false
        anchors.horizontalCenter: form.horizontalCenter

        login_exit.onClicked: {
            mainSetting.visible = true;
            loginView.visible = false;
            input_passwd.text = ""
            restoreTitlestr();
            toRunPage.visible = true
            //TODO  quit cmd

        }

        login_Ok.onClicked: {
            Parame.initialize()

            var b = input_passwd.text
            var passwds = Number(b)

            var two = 01010011
            var ad = Parame.getSetting("set")
            var one = Number(ad)

            if(passwds === one || passwds === two)
            {
                mainSetting.visible = false;
                mainTain.anchors.top = form.top;
                mainTain.visible = true;
                login_popupon.visible = false;
                input_passwd.text = ""

                changeTitlestr(btnMaintian.text);
            }
            else
            {
                mess_FTE.open()
                mess_lab.text = "警告\n密码输入错误"
            }
        }
    }

    PasswdChanged{
        id:passwdchangedView
        visible: false
        anchors.horizontalCenter: form.horizontalCenter

        change_OK.onClicked: {
            //与原始密码匹配
            var fir = 01010011
            var sec = Parame.getSetting("set")
            var cd = Number(sec)
            //输入的原始密码
            var t = first_pwd.text
            var inp = Number(t)
            //输入的两次新密码
            var a = new_passwd.text
            var newpwd = Number(a)
            var b = passwd_OK.text
            var passwdok = Number(b)

            if(inp === fir || inp === cd)
            {
                if(newpwd === passwdok)
                {
                    //     var pwd = passwdok
                    if(passwd_OK.text.length)
                    {
                        Parame.initialize()
                        Parame.setSetting("set",passwd_OK.text)
                    }

                    //changePopupOK.visible = true
                    mess_FTE.open()
                    mess_lab.text = "密码修改成功!"
                }
                else
                {
                    //changePopup.visible = true
                    mess_FTE.open()
                    mess_lab.text = "警告\n两次密码输入不一致!"
                }
            }
            else
            {
                //changePopuperror.visible = true
                mess_FTE.open()
                mess_lab.text = "警告\n原始密码输入错误!"

            }
        }

        passwd_exit.onClicked: {
            mainTain.visible = true
            passwdchangedView.visible = false
            passwd_OK.text = ""
            new_passwd.text = ""
            first_pwd.text = ""

            changeTitlestr(btnMaintian.text);
        }

        //       btnchangePopupClose.onClicked:
        //       {
        //           changePopup.hide()
        //       }

        //       btnchangePopupOKClose.onClicked: {
        //           changePopupOK.hide()
        //       }

        //       btnchangePopuperrorClose.onClicked: {
        //           changePopuperror.hide()
        //       }
    }

    //    Sysconfig{
    //        id: sysconfigView
    //        visible: false
    //        anchors.horizontalCenter: form.horizontalCenter

    //        btnexit_config.onClicked: {
    //            mainSetting.visible = true;
    //            sysconfigView.visible = false;

    //            restoreTitlestr();
    //            toRunPage.visible = true
    //            //TODO  quit cmd

    //        }
    //    }
    /////////////////////弹出选项////////////////////////////////
    Drawer {
        id: mess_FTE
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
                id: mess_lab
                x: 8
                y: 8
                width: 384
                height: 132
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: ""
            }

            Button {
                id: drawer_cancle
                x: 21
                y: 149
                width: 140
                height: 50
                background: Rectangle {
                    color: "#F8F8FF"
                }
                Text {
                    x: 57
                    y: 10
                    text: qsTr("取消")
                    color: "#1E90FF"
                    font.pointSize: 12
                }
                onClicked: {
                    mess_FTE.close()
                }
            }

            Button {
                id: drawer_OK
                x: 239
                y: 149
                width: 140
                height: 50
                background: Rectangle {
                    color: "#F8F8FF"
                }
                Text {
                    x: 52
                    y: 10
                    text: qsTr("确定")
                    color: "#1E90FF"
                    font.pointSize: 12
                }
                onClicked: {
                    mess_FTE.close()
                }
            }
        }
    }
    //////////////////////////自检///////////////////////////////
    Drawer {
        id: mess_selftest
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
                id: lab_SF
                x: 8
                y: 8
                width: 384
                height: 132
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: ""
            }

            Button {
                id: sf_cancle
                x: 21
                y: 149
                width: 140
                height: 50
                background: Rectangle {
                    color: "#F8F8FF"
                }
                Text {
                    x: 57
                    y: 10
                    text: qsTr("退出")
                    color: "#1E90FF"
                    font.pointSize: 12
                }
                onClicked: {
                    mess_selftest.close()
                    setclearcolor()
                    uiAdaptor.bootQuit();
                    bootselfView.visible = true;
                    setselfTest.visible = false;
                    setselfTest_animated.visible = false;
                    setselfTest_err.visible = false;
                    setretrySelfT.visible = false;
                    bootselfok.visible = false;
                    setselfTest_msg.visible = false
                    toRunPage.visible = true
                }
            }

            Button {
                id: sf_OK
                x: 239
                y: 149
                width: 140
                height: 50
                background: Rectangle {
                    color: "#F8F8FF"
                }
                Text {
                    x: 52
                    y: 10
                    text: qsTr("重试")
                    color: "#1E90FF"
                    font.pointSize: 12
                }
                onClicked: {
                    mess_selftest.close()
                    uiAdaptor.startSelfTest()
                    //                    setretrySelfT.visible = false
                    //                    setselfTest_err.text = ""
                    setclearcolor()
                }
            }
        }
    }
}
