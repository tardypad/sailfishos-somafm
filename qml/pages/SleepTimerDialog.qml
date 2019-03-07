/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../scripts/DurationFormatter.js" as DurationFormatter

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
            acceptText: 'Sleep in '+ DurationFormatter.formatSleepTime(dialog.hour, dialog.minute)
        }
        TimePicker {
            id: timePicker
            hour: 1
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    onAccepted: {
        _player.startSleepTimer(hour*3600 + minute*60);
    }

}
