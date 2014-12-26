/*
 * qt_common.cpp
 *
 *  Created on: 2014-12-26
 *      Author: root
 */

#include "qt_common.h"

qt_common::qt_common()
{
    display_refresh_time = 0;

    for(int i=0; i<KEY_NUM; i++)
    {
        key[i].key_status = 0;
        key[i].key_time = 0;
    }
}

qt_common::~qt_common()
{

}
