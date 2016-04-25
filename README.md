# Async Library for Arduino
A simple library for Arduino, utilizing an event loop and message queues, to help facilitate simple easy to use asynchronous control flow patterns.

## Installation
Copy the folder Async into your Arduino Libraries folder, as described in the Arduino [documentation](http://www.arduino.cc/en/Guide/Libraries).

## Dependencies
[SimpleList](https://github.com/blackhack/ArduLibraries) as described in [Libraries for Arduino](http://playground.arduino.cc//Main/LibraryList)

## Usage
At the top of your sketch you must include the EventManager header file:
    #include <Async.h>

Next, we need to run the event loop:

    void loop() {
      Async::tick();
    }

Processing time can be saved by executing the tick less frequently, i.e., `if (counter % 100 == 0) // every 100 cycles`, or the while loop could be modified by overriding `main()`

### Create Timeout
Without context:

    Async::setTimeout([](void* context) {
      // Do something 1.5 seconds later
    }, 1500);

With context:

    int myInt = 200;

...

    Async::setTimeout([](void* context) {
      // cast context to int and dereference
      int myCapturedInt = *((int *) context);
    }, 1500, &myInt);
