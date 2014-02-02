/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


import QtQuick 2.0

Rectangle {
    id: banner

    property alias spacing: row.spacing

    color: "black"

    Row {
        id: row
        anchors.centerIn: parent

        Image {
            anchors.verticalCenter: parent.verticalCenter
            source: somaTheme.getImageSource("logo")
            smooth: true
            fillMode: Image.PreserveAspectFit
            height: banner.height * 0.8
            width: banner.width * 0.2
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            source: somaTheme.getImageSource("name")
            smooth: true
            fillMode: Image.PreserveAspectFit
            height: banner.height * 0.8
            width: banner.width * 0.6
        }
    }
}
