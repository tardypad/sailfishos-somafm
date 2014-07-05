/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

.pragma library

function formatSleepTime(hours, minutes)
{
    if (hours !== 0)
        if (minutes !== 0)
            return hours + 'H ' + minutes + 'min'
        else
            return hours + 'H'
    else
        return minutes + 'min'
}

function formatRemainingTime(seconds)
{
    var hours = getHours(seconds)
    var minutes = getMinutes(seconds)

    if (hours !== 0)
        if (minutes !== 0)
            return hours + 'H ' + minutes + 'min'
        else
            return hours + 'H'
    else
        if (minutes !== 0)
            return minutes + 'min'
        else
            return 'few seconds'
}

function getHours(seconds)
{
    return Math.floor(seconds / 3600)
}

function getMinutes(seconds)
{
    return Math.floor(seconds / 60) % 60
}
