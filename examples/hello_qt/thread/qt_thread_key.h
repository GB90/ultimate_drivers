/*
 * qt_thread_key.h
 *
 *  Created on: 2014-12-26
 *      Author: root
 */

#ifndef QT_THREAD_KEY_H_
#define QT_THREAD_KEY_H_

#include "../qt_common.h"

class qt_thread_key : public QThread
{
public:
    void run();
};

#endif /* QT_THREAD_KEY_H_ */
