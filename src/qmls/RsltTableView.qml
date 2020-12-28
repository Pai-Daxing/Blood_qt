import QtQuick 2.7
import QtQuick.Controls 1.4
//import SqlQueryModel 1.0

TableView{
    id: tableview
    property var holdMenuModelDataArray: null
//    backgroundVisible: true;
//    frameVisible: false;
    itemDelegate: TableItemDelegate{} //Item代理
    headerDelegate: headerDele;  //表头委托
    rowDelegate: rowDele;   //行委托
    model: sqlquery

    //定义表头的委托
    Component{
        id:headerDele
        Rectangle{
            id: headerRect;
            height: 40;

            color:"white";
            Text{
                text: styleData.value
                visible: (headerRect.width == 0)? false :true
                anchors.centerIn: parent
                font.family: "微软雅黑";
                font.pixelSize: 16;
                color: "black";
            }
        }
    }

    //定义行的委托
    Component{
        id:rowDele
        Rectangle{
            id: rect;
            height: 40;
            color: "#404040";
        }
    }
    //更新表格标题列高度和role
    function updateColumn2Table(arrayData){
        if(arrayData.length != 3){
            console.log("DataShowTable.qml updateColumn2Table arrayData.length !=3");
            return;
        }

        var arrayTitle = arrayData[0]; //标题数组
        var arrayWidth = arrayData[1]; //宽度数组
        var arrayRoles = arrayData[2]; //role数组
        if(arrayTitle.length != arrayWidth.length || arrayTitle.length > arrayRoles.length){
            console.log("arrayTitle argument error in DataShowTable.qml updateColumn2Table(arrayTitle,arrayWidth,arrayRoles)");
            return;
        }

        //        tableview.model.clear(); //先将model里面的数据清空避免在更新的列里面有相同的role直接显示
        var i,str,count = tableview.columnCount;
        var sum = new Number(0);
        //求出长度累加和以便于按比例分配列宽
        for(i =0;i<arrayWidth.length;i++){
            sum += arrayWidth[i];
        }
        var prefix = 'import QtQuick 2.7;import QtQuick.Controls 1.4;TableViewColumn
                      {resizable: false; movable: false; width: Math.round(tableview.width *'; //创建TableViewColumn的代码
        //前缀
        //将现在的每列全部删除
        for(i=0;i<count;i++){
            tableview.removeColumn(0);
        }
        //循环添加TableViewColumn
        for(i=0;i<arrayTitle.length;i++){
            str = prefix + arrayWidth[i]/sum +");role:\"" + arrayRoles[i] + "\";title:\"" + arrayTitle[i] + "\"}";
            tableview.addColumn(Qt.createQmlObject(str,tableview,"dynamicSnippet1"));
        }
    }

//    SqlQueryModel{
//        id :dataModel
//    }

//    Component.onCompleted: {
//        console.log(dataModel)

////        dataModel.refresh();
//    }
}
