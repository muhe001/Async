/*
 * Async.h
 *
 * An async library for Arduino.
 *
 */
#ifndef Async_h
#define Async_h

#include <Arduino.h>
#include <SimpleList.h>

typedef void ( *Callback )(void*);

class Async
{
public:
  static void tick();
  static void setTimeout( Callback callback, int milliseconds );
  static void setTimeout( Callback callback, int milliseconds, void* context );

private:
  struct TimeoutItem
  {
      Callback	callback;
      unsigned long timeout;
      void* context;
  };
  static SimpleList<TimeoutItem> mTimeouts;
};

#endif
