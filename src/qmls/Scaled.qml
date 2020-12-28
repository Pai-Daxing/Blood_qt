import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

import UiAdaptor 1.0

ScaledForm {
    id: scaledView

    UiAdaptor{
        id: uiAdaptor_sca

        //“血浆量更新”信号
        onVolumeOfPlasmaChanged : {
            textInput_scale1.text = newValue/10;
        }
        //“抗凝剂量更新”信号
        onVolumeOfACDChanged : {
            //textInput_scale2.text = newValue/10;
        }
        //“压力监视器更新”信号
        onPressureOfDpmChanged : {
            textInput_dpm.text = newValue/10;
        }
    }

//    one_Ok.onClicked: {
//        var num = (one_Ok) ? input_one.text : 0
//        uiAdaptor_sca.scaledOkOne(num);
//    }
    two_Ok.onClicked: {
        var num1 = (two_Ok) ? input_one.text : 0
        uiAdaptor_sca.scaledOkTwo( num1);
    }
//    three_Ok.onClicked: {
//        var num2 = (three_Ok) ? input_three.text : 0
//        uiAdaptor_sca.bldScaOkThree(num2);
//    }
    four_Ok.onClicked: {
        var num3 = (four_Ok) ? input_three.text : 0
        uiAdaptor_sca.bldScaOkFour( num3);
    }


}
