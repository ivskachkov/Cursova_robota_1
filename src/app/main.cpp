// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//https://doc.qt.io/qt-6/cmake-get-started.html

#include <QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}
