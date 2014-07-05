/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: dialog
    objectName: "SleepTimerDialog"

    property alias hour: timePicker.hour
    property alias minute: timePicker.minute

    canAccept: hour != 0 || minute != 0

    Column {
        width: parent.width
        spacing: Theme.paddingMedium

        DialogHeader {
            acceptText: 'Sleep in '+ timePicker.hour + 'h ' + timePicker.minute + 'm'
        }
        TimePicker {
            id: timePicker
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    onAccepted: {
        _player.startSleepTimer(hour*3600 + minute*60);
    }

}
