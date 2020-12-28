#ifndef STATUSDEFINE_H
#define STATUSDEFINE_H

enum ControlSystemStatus //控制系统状态值定义
{
    CSS_unknown = 0,                  //未知
     CSS_standby,                      //待机
     CSS_debug,                        //调试
     CSS_calib_check1,                  //皮重检查1
     CSS_calib_waiting1,                //等待校准1
     CSS_calib_success1,                //校准成功1

     CSS_calib_fail1,                   //校准失败1
     CSS_calib_check2,                  //皮重检查2
     CSS_calib_waiting2,                //等待校准2
     CSS_calib_success2,                //校准成功2
     CSS_calib_fail2,                   //校准失败2

     CSS_selftest_begin,
     CSS_open_waiting,                 //离心机盖
     CSS_close_waiting,
     CSS_AirDs_checking,               //空探正在检查(自检)
     CSS_Vlvs_checking,                //阀门(自检)
     CSS_Pumps_checking,               //泵
     CSS_line_checking,                //回输管路安全检查
     CSS_CF_checking,                  //离心机

     CSS_DPM_checking,                 //压力监测器
     CSS_Scales_checking,              //电子秤
     CSS_leak_checking,                //漏液

     CSS_selftest_stopping,            //自检正在结束
     CSS_selftest_failed,              //自检失败
     CSS_selftest_over,                //自检结束
     CSS_collect_begin,                //(采集模式开始)
     CSS_Sf_AirDs_checking=CSS_collect_begin,  //空探正在检查(采集)
     CSS_Sf_Vlvs_checking,              //阀门(采集)
//     CSS_Sf_AirDs_Vlvs_failed,           //空探阀门自检失败

     CSS_Sf_Chk_failed,
     CSS_cup_waiting,                  //等待离心杯安装
     CSS_line_ready,                   //等待管路安装确认
     CSS_acd_waiting,                  //等待抗凝剂穿刺
     CSS_filling,                      //充液

     CSS_filling_failed,               //充液失败
     CSS_install_finished,             //安装完成
     CSS_alarm_paused,                 //报警暂停
     CSS_ready_draw,                   //采集准备
     CSS_drawing,                      //正在采血

     CSS_draw_ending,                  //采集转洗涤或制备过程状态
     CSS_washing,                      //正在洗涤红细胞
     CSS_collect,                      //制备
     CSS_drawstate_turning,            //采集/洗涤和制备切换
     CSS_collect_paused,               //采集暂停

     CSS_collect_stopping,             //采集正在终止
     CSS_collect_over,                 //采集结束

     CSS_drawing_power,                //采集时掉电
     CSS_collect_power,                //制备时掉电
     CSS_continueOrover,              //浓缩回血时空探

};

//  工作状态，用于数据管理软件作区别
enum WorkStatus
{
    WS_NONE,                       //对应数据管理软件的3个状态，若其中一边变化，注意统一！！！
    WS_FREE,                       //空闲
    WS_BUSY,                       //采集中
    WS_ALM,                        //采集中
};

#endif // STATUSDEFINE_H
