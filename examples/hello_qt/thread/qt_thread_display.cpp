/*
 * qt_thread_display.cpp
 *
 *  Created on: 2014-12-26
 *      Author: root
 */

#include "qt_thread_display.h"

extern qt_common * qt_con;


void qt_thread_display::run()
{
    int i32_fd_lcd;

    while(true)
    {
        for(int i=0; i<KEY_NUM; i++)
        {
            qt_con->lock_key.lock();
            if(qt_con->key[i].key_status == 1)
            {
                qt_con->main_ui.ui.pushButton[i]->setDown(true);
            }
            else
            {
                qt_con->main_ui.ui.pushButton[i]->setDown(false);
            }
            qt_con->lock_key.unlock();
        }

        qt_con->main_ui.show();

        i32_fd_lcd = open("/dev/ud_lcd", O_RDWR);
        if(i32_fd_lcd < 0)
        {
            printf("open lcd fail\n");
        }
        else
        {
            ioctl(i32_fd_lcd, UD_LCD_CMD_REFRESH, NULL);
        }
        close(i32_fd_lcd);

        usleep(300*1000);
    }
}
