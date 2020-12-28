#ifndef COMMANDS_H
#define COMMANDS_H


enum DataType
{
    DT_STATU,     //状态数据
    DT_PARAM,      //参数数据
};

typedef enum _CommandID {
    CMD_shake_hand, //握手

    CMD_start_calib1, //启动抗凝电子秤校准
    CMD_calib1, //执行抗凝电子秤校准
    CMD_quit_calib1, //退出抗凝电子秤校准

    CMD_start_calib2, //启动血浆电子秤校准
    CMD_calib2, //执行血浆电子秤校准
    CMD_quit_calib2, //退出血浆电子秤校准

    CMD_start_debug, //启动调试
    CMD_quit_debug, //退出调试

    CMD_boot_selftest, //开机自检
    CMD_boot_chkfailed, //自检失败
    CMD_boot_quit,      //退出开机自检

    CMD_start_selftest, //启动自检
    CMD_quit_selftest, //退出自检

    CMD_start_install, //启动安装
    CMD_confirm_install, //确认管路安装
    CMD_prime, //执行充液
    CMD_quit_install, //退出安装
    CMD_prepare_collect, //准备采集
    CMD_start_collect, //启动采集
    CMD_draw, //执行采血
    CMD_wash_RBC, //执行洗涤红细胞
    CMD_collect_RBC, //执行回血
    CMD_halt_collect, //暂停采集
    CMD_end_collect, //结束采集
    CMD_quit_collect, //退出采集
    CMD_cancel_alarm, //关闭当前报警

    CMD_set_params, //设置采集参数
    CMD_set_drawRate, //设置采集速度
    CMD_set_collectRBCRate,//设置红细胞速度
    CMD_set_pumpStatus, //设置血泵启停状态
    CMD_set_lineDSens, //设置管探灵敏度

    // 调试状态时的设置命令
    CMD_DB_set_bldPumpRate, //设置血泵速度
    CMD_DB_set_PrsvPumpRate, //设置保养液泵速度
    CMD_DB_set_acdFactor, //设置抗凝比
    CMD_DB_set_cfStatus, //设置离心机启停
    CMD_DB_set_bldValve, //设置血液阀开关
    CMD_DB_set_plmValve, //设置血浆阀开关
    CMD_DB_set_naclValve, //设置盐水阀开关
    CMD_DB_set_PresvValve, //设置保养液阀开关
    CMD_DB_set_RBCValve, //设置悬红阀开关
    CMD_DB_set_WasteValve, //设置废液阀开关
    CMD_DB_set_bldPump_Dir, //设置血泵方向   0：顺时针；1：逆时针

    CMD_set_softFun, //设置软件功能   0：采浆；   1：血浆置换；  2：蓉生定制软件功能

    //采集界面
    CMD_ala_collectblood,     //报警采血
    CMD_ala_preparation,      //报警制备
    CMD_ala_exit,             //报警退出

    CMD_Col_bldadd,           //采集界面血液转速增加
    CMD_Col_bldred,           //采集界面血液转速减小
    CMD_Col_bldsta,           //采集界面血泵打开
    CMD_Col_bldstop,          //采集界面血泵关闭
    CMD_stop,
    CMD_Fill_failed,

    //电子秤
    CMD_Scaled_Ok_One,
    CMD_Scaled_Ok_Two,

    CMD_BldSca_Ok_Three,
    CMD_BldSca_Ok_four,
    //CMD_BldSca_Ok_five,

    //paramset
    CMD_Collect_Blood = 100,
    CMD_Draw_Speed,
    CMD_Collect_Speed,
    CMD_Anti,
    CMD_LineCoeff,
    CMD_Presvvlm_Speed,
//    CMD_Paramset_ok,

    CMD_self_quit, //退出采集自检
    CMD_Sca_start,
    CMD_Sca_exit,

    CMD_Col_NPadd,   //保养液泵转速增加
    CMD_Col_NPred,   //保养液泵转速减少
    CMD_Col_Npsta,   //保养液泵打开
    CMD_Col_Npstop,  //保养液泵关闭
    CMD_Col_next,    //浓缩下一步

                      //stop按鈕

} CommandID;

typedef short CmdParam;     //“设置...”命令参数类型

#endif // COMMANDS_H
