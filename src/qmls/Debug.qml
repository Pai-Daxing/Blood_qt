import QtQuick 2.4
import QtQuick.Controls 2.2
import "customCtrls" as MyCtrls
import UiAdaptor 1.0

DebugForm {

    id : db_form
    UiAdaptor{
        id: uiAdaptor_db_in
        // 调试界面信号更新

        //“压力监测值更新”信号
        onPressureOfDpmChanged : {
            textInput_dpm.text = newValue/10;
        }
        //“血浆量更新”信号
        onVolumeOfPlasmaChanged : {
            textInput_scale1.text = newValue/10;
        }
        //“抗凝剂量更新”信号
        onVolumeOfACDChanged : {
            textInput_scale2.text = newValue/10;
        }
        //“血泵流速更新”信号
        onBPrealChanged : {
            textInput_bldP.text = newValue;
        }

        //“抗凝剂泵流速更新”信号
        onAPrealChanged: {
            textInput_ACDP.text = newValue;
        }

        //“保养液泵流速更新”信号
        onNPrealChanged: {
            textInput_PresvP.text = newValue;
        }

        //“离心机转速更新”信号
        onSpeedOfCentrifugeChanged: {
            textInput_centri.text = newValue;
        }

        //“管路探测器更新”信号
        onLineDetectorChanged: {
            textInput_lineD.text = newValue;
        }

        //“血液阀开关更新”信号 1开 0关
        onValveOfBloodChanged:{
            comboBox_bldV.currentIndex = newValue?1:0;

        }

        //“血浆阀开关更新”信号 1开 0关
        onValveOfPlasmaChanged:{
            comboBox_plsmV.currentIndex = newValue?1:0;
        }

        //“盐水阀开关更新”信号 1开 0关
        onValveOfNaClChanged:{
            comboBox_NaClV.currentIndex = newValue?1:0;
        }

        //“血液空探更新”信号 1液体 0空气
        onAirDetectorOfBloodChanged:{
            comboBox_bldairD.currentIndex = newValue?1:0;
        }

        //“抗凝剂空探更新”信号 1液体 0空气
        onAirDetectorOfAcdChanged:{
            comboBox_ACDairD.currentIndex = newValue?1:0;
        }

        //“保养液空探更新”信号 1液体 0空气
        onAirDetectorOfPresvChanged:{
            comboBox_PrsvairD.currentIndex = newValue?1:0;
        }

        //“压力监测器状态更新”信号 1已安装 0未安装
        onDpmChanged:{
            comboBox_DPM.currentIndex = newValue?1:0;
        }

        //“漏夜监测器状态更新”信号 1已漏液 0未漏液
        onLeakChanged:{
            comboBox_leak.currentIndex = newValue?1:0;
        }

        //“离心机盖状态更新”信号 1已关盖 0未关盖
        onCoverChanged:{
            comboBox_cover.currentIndex = newValue?1:0;
        }

        //“管路探测器更新”信号 1发现红细胞 0未发现红细胞
        onLineSensorChanged:{
            comboBox_lineSensor.currentIndex = newValue?1:0;
        }
        //“抗凝阀开关更新”信号 1开 0关
        onValveOfACDChanged: {
            comboBox_ACDV.currentIndex = newValue?1:0;
        }

        //“保养液阀开关更新”信号 1开 0关
        onValveOfPresvChanged: {
            comboBox_PresvV.currentIndex = newValue?1:0;
        }

        //“红细胞阀开关更新”信号 1开 0关
        onValveOfRBCChanged: {
            comboBox_RBCV.currentIndex = newValue?1:0;
        }

        //“废液阀开关更新”信号 1开 0关
        onValveOfWasteChanged:  {
            comboBox_wasteV.currentIndex = newValue?1:0;
        }
    }

    switch_centri.onCheckedChanged: {
        var val = switch_centri.checked;
        console.log(val+" 离心机盖是否关闭")
        uiAdaptor_db_in.dbSetBool( 0, val);      // case 0:  emit UICmd(CMD_DB_set_cfStatus, (const short *)&val, 1);
    }
    switch_bldVlv.onCheckedChanged: {
        var val = switch_bldVlv.checked;
        uiAdaptor_db_in.dbSetBool( 1, val);      //case 1: emit UICmd(CMD_DB_set_bldValve, (const short *)&val, 1);
    }
    switch_RBCVlv.onCheckedChanged: {
        var val = switch_RBCVlv.checked;
        uiAdaptor_db_in.dbSetBool( 2, val);      //case 2: emit UICmd(CMD_DB_set_RBCValve, (const short *)&val, 1);
    }
    switch_plasmaVlv.onCheckedChanged: {
        var val = switch_plasmaVlv.checked;
        uiAdaptor_db_in.dbSetBool( 3, val);      //case 3: emit UICmd(CMD_DB_set_plmValve, (const short *)&val, 1);
    }
    switch_wasteVlv.onCheckedChanged: {
        var val = switch_wasteVlv.checked;
        uiAdaptor_db_in.dbSetBool( 4, val);      //case 4: emit UICmd(CMD_DB_set_WasteValve, (const short *)&val, 1);
    }
    switch_prsvVlv.onCheckedChanged: {
        var val = switch_prsvVlv.checked;
        uiAdaptor_db_in.dbSetBool( 5, val);      //case 5: emit UICmd(CMD_DB_set_PresvValve, (const short *)&val, 1);
    }
    switch_naclVlv.onCheckedChanged: {
        var val = switch_naclVlv.checked;
        uiAdaptor_db_in.dbSetBool( 6, val);      //case 6: emit UICmd(CMD_DB_set_naclValve, (const short *)&val, 1);
    }

    switch_BP.onCheckedChanged: {
        var bldS = (switch_BP.checked) ? input_BP_Speed.text : 0;
        uiAdaptor_db_in.dbSetBldPSpeed(bldS);
    }


    switch_BP_Dir.onCheckedChanged: {
        var dir = switch_BP_Dir.checked;
        uiAdaptor_db_in.dbSetBldPDir(dir);
    }

    switch_AP.onCheckedChanged: {
        var acdS = (switch_AP.checked) ? input_AP_Speed.text : 0
        uiAdaptor_db_in.dbSetAcdPSpeed(acdS);
    }
    switch_NP.onCheckedChanged: {
        var nS = (switch_NP.checked) ? input_NP_Speed.text : 0
        uiAdaptor_db_in.dbSetPresvPSpeed( nS);
    }
}
