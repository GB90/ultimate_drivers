/*
 * qt_thread_key.cpp
 *
 *  Created on: 2014-12-26
 *      Author: root
 */

#include "qt_thread_key.h"

extern qt_common * qt_con;

void qt_thread_key::run()
{
    int i32_fd_bus;
    struct bus_struct x_bus;

    while(true)
    {
        i32_fd_bus = open("/dev/ud_bus", O_RDWR);
        if(i32_fd_bus < 0)
        {
            printf("open bus fail\n");
        }
        else
        {
            x_bus.u32_bus_addr = 0x02;
            x_bus.u32_bus_data = 0;
            ioctl(i32_fd_bus, UD_BUS_CMD_GET_DATA, &x_bus);
            qt_con->lock_key.lock();
            for(int i=0; i<8; i++)
            {
                if(x_bus.u32_bus_data & (1<<i))
                {
                    qt_con->key[i].key_status = 1;
                    qt_con->key[i].key_time ++;
                }
                else
                {
                    qt_con->key[i].key_status = 0;
                    qt_con->key[i].key_time = 0;
                }
            }
            qt_con->lock_key.unlock();
        }
        close(i32_fd_bus);

        usleep(10*1000);
    }
}
