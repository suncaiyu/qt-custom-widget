
import QtQuick 2.12
import QtQuick.Window 2.0

Item
{
    id:root;
    visible: true;
    width: 800; height: 400

    ListView
    {
        id:view
        anchors.fill: parent
        orientation: Qt.Horizontal
        spacing: 10
        model:ListModel
        {
            ListElement{imgPath: "qrc:/img/1.jpeg";title:"标题1";detailed:"黄河之水天上来";}
            ListElement{imgPath: "qrc:/img/2.jpeg";title:"标题2";detailed:"奔流到海不复回";}
            ListElement{imgPath: "qrc:/img/3.jpeg";title:"标题3";detailed:"明镜高堂悲白发";}
            ListElement{imgPath: "qrc:/img/4.jpeg";title:"标题4";detailed:"朝如青丝暮成雪";}
            ListElement{imgPath: "qrc:/img/5.jpeg";title:"标题5";detailed:"人生得意须尽欢";}
        }
        delegate:Delegate{}
        focus: true
    }
}
