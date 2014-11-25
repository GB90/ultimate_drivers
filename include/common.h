#ifndef __UD_COMMON__
#define __UD_COMMON__

#define UD_DEBUG

#ifdef UD_DEBUG
#define printd(arg,x...)    printk(KERN_ALERT "UD debug : "arg, ##x)
#define assertd(expr)       while(expr) { \
        printk(KERN_ALERT "UD assert : failed at %s (%d)\n", \
               __FILE__,  __LINE__); \
    } 
#else
#define printd(arg,x...)
#define assertd(expr)
#endif

#endif