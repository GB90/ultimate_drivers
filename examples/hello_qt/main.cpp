#include "qt_common.h"
#include "thread/qt_thread_display.h"
#include "thread/qt_thread_key.h"

qt_common * qt_con = new qt_common();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qt_thread_display   thread_display;
    qt_thread_key       thread_key;

    thread_display.start();
    thread_key.start();

    return a.exec();
}
