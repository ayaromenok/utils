// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/utils/blob/master/LICENSE

import QtQuick 2.0
import QtQuick.Controls 1.4 as QQC1
Item {
    QQC1.Action {
        id: acExit
        text: "E&xit"
        //shortcut: StandardKey.Quit
        onTriggered: Qt.quit()
    }
}

