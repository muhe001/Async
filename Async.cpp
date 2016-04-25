/*
 * Async.cpp
 *
 * An async library for Arduino.
 *
 */

#include "Async.h"

SimpleList<Async::TimeoutItem> Async::mTimeouts;

void Async::tick()
{
  for (
    SimpleList<Async::TimeoutItem>::iterator itr = mTimeouts.begin();
    itr < mTimeouts.end();
    itr++ )
  {
    if (millis() > ((*itr).timeout)) {
      (*itr).callback((*itr).context);
      itr = mTimeouts.erase(itr);
    }
  }
}

void Async::setTimeout(Callback callback, int milliseconds)
{
  Async::TimeoutItem timeoutItem = {
    callback,
    millis() + milliseconds
  };
  mTimeouts.push_back(timeoutItem);
}

void Async::setTimeout(Callback callback, int milliseconds, void* context)
{
  Async::TimeoutItem timeoutItem = {
    callback,
    millis() + milliseconds,
    context
  };
  mTimeouts.push_back(timeoutItem);
}
