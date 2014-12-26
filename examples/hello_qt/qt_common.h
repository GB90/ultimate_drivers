/*
 * qt_common.h
 *
 *  Created on: 2014-12-26
 *      Author: root
 */

#ifndef QT_COMMON_H_
#define QT_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

#include "/opt/workspace/ultimate_drivers/include/ud_device_lcd.h"
#include "/opt/workspace/ultimate_drivers/include/ud_device_bus_emulated.h"

#include <QtGui>
#include <QApplication>
#include "ui/qt_ui.h"

#define KEY_NUM  (9)

class qt_key_buffer
{
public:
    int     key_status;
    int     key_time;
};


class qt_common
{
public:
    qt_common();
    ~qt_common();

    QMutex          lock_key;

    int             display_refresh_time;
    qt_key_buffer   key[KEY_NUM];
    hello_qt        main_ui;
};

#endif /* QT_COMMON_H_ */
