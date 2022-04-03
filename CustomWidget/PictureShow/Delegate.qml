
import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle
{
    id:root
    width: 50
    height: 320
    radius: 25
    color: ListView.isCurrentItem?"#157efb":"#53d769" //选中颜色设置
    border.color: Qt.lighter(color, 1.1)

    Image
    {
        id:_image
        anchors.fill: parent
        fillMode:Image.PreserveAspectCrop
        source: imgPath
        sourceSize: Qt.size(parent.size, parent.size)
        smooth: true
        antialiasing: true
        visible: false
    }

    Rectangle
    {
        id: _mask
        color: "black"
        anchors.fill: parent
        radius: root.radius
        visible: false
        antialiasing: true
        smooth: true
    }
    OpacityMask
    {
        id: mask_image
        anchors.fill: _image
        source: _image
        maskSource: _mask
        visible: true
        antialiasing: true
    }

    Rectangle
    {
        id:cir
        color: "#ffffff"
        width: 36
        height: 36
        radius: 18
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 7
        anchors.bottomMargin: 6
        MouseArea
        {
            anchors.fill: cir
            cursorShape: Qt.PointingHandCursor
            onClicked:
            {
                view.currentIndex = index  //item切换

                if(root.state == "")
                {
                    for(var i = 0;i < view.count;++i)
                    {
                        var item = view.itemAtIndex(i)
                        if(item !== index)
                        {
                            item.state = ""
                        }
                    }
                    root.state = "showDetails"
                }
                else
                {
                    root.state = ""
                }
            }
        }
    }

    Column
    {
        anchors.left: cir.right
        anchors.top: cir.top
        anchors.leftMargin: 10

        Text
        {
            text: title
            color: "#ffffff"
            font.pixelSize: 16
            font.bold: true
        }
        Text
        {
            text: detailed
            color: "#ffffff"
            font.pixelSize: 14
        }
    }

    states:
    [
        State
        {
            name: "showDetails"
            PropertyChanges { target: root;width: 460;}
        }
    ]
    transitions: //设置状态转变的动画
    [
        Transition
        {
            NumberAnimation//其值为数值类型的动画
            {
                duration: 300;
                properties: "height,width"
            }
        }
    ]
}
