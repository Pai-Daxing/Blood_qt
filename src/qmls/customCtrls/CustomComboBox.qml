import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Private 1.0

ComboBox {
    id: box

    currentIndex: 0
    activeFocusOnPress: true
    width: 110

    style: ComboBoxStyle {
        id: comboBox
        background: Rectangle {
            id: rectCategory
//            radius: 5
            border.width: 1
            color: "#ffffff"
        }
        label: Text {
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 15
            font.family: "微软雅黑"
//            font.capitalization: Font.SmallCaps
            color: "black"
            text: control.currentText
        }

        // drop-down customization here
        property Component __dropDownStyle: MenuStyle {
            __maxPopupHeight: 600
            __menuItemType: "comboboxitem"

            frame: Rectangle {              // background
                color: "#fff"
                border.width: 1
//                radius: 5
            }

            itemDelegate.label:             // an item text
                                            Text {
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 15
                font.family: "微软雅黑"
                font.capitalization: Font.SmallCaps
//                color: styleData.selected ? "white" : "black"
                text: styleData.text
            }

            itemDelegate.background: Rectangle {  // selection of an item
//                radius: 2
                color: styleData.selected ? "darkGray" : "transparent"
            }

            __scrollerStyle: ScrollViewStyle { }
        }

        property Component __popupStyle: Style {
            property int __maxPopupHeight: 400
            property int submenuOverlap: 0

            property Component frame: Rectangle {
                width: (parent ? parent.contentWidth : 0)
                height: (parent ? parent.contentHeight : 0) + 2
                border.color: "white"
                property real maxHeight: 500
                property int margin: 1
            }

            property Component menuItemPanel: Text {
                text: "NOT IMPLEMENTED"
                color: "white"
                font {
                    pixelSize: 14
                    bold: true
                }
            }

            property Component __scrollerStyle: null
        }
    }

}
