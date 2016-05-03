![RiCino Lap Counter](images/ricino-logo-350.png)

---

_*NOTE:* There are changes coming to the RiCino Lap Counter which are not yet reflected in the source. These changes will affect the way the transponder communicates with the Reciever. These updates will be backward compatible, and will not be required if you do not wish to implement them._

The RiCino Lap Counter is an [Arduino](http://arduino.cc) based, open source infrared RC Lap Counting System, compatible with the industry standard [Zround](http://www.zround.com) software. It is ideal for small scale indoor racing (Mini-Z), but could be used for any type of scale sport.

RiCino Lap Counter was originally created by [Lisergio](http://lisergio.wordpress.com/). The name RiCino is a portmanteau of _RC_ + _Arduino_ and it was coined by Lisergio. The extra "i" between the R and C was added for phonetic reasons.


## Features ##

* Arduino based Receiver with Infrared Sensors
* Almost infinite number of transponders (over 60.000 ID's)
* Works with the industry standard [Zround](http://www.zround.com) software
* Scalable to any track width
* DIY instructions
* Dirt cheap to buy parts and build on your own


## The Lap Counter System ##

The RiCino Lap Counter system is comprised of two main components, the Receiver and the Transponder. Each has it's own hardware and software.

![RiCino Lap Counter](images/ricino-lap-counter.jpg)


### Receiver ###
The receiver can be built as a modular and expandable system, which can scale depending on the track size. The two main parts are the Decoder and the Sensors.

##### Decoder #####
The main decoder is an Arduino ([ATmega328P](https://www.arduino.cc/en/Main/Products)) based module, running the custom RiCino Lap Counter software. 

![Decoder Schematic](Receiver/Decoder.png)

##### Sensors #####
The RiCino Lap Counter is designed with scalability in mind. You can add as many Infrared Sensors as your track requires. Usually, you'll need a sensor every 70cm for a 50cm high bridge.

![Sensor Schematic](Receiver/Sensor.png)


### Transponder ###
The transponders are based on a single ATtiny85 chip design and are programmed to emit a single 2 byte HEX code, delivering over 60.000 unique ID's.

![Transponder Schematic](Transponder/Transponder.png)


##### Transponder HEX Code Generator #####
When you programme your own transponders, it goes without saying that you should create each transponder to emit a unique code. Doing this on a local scale is easy. But we've built a tool to generate, catalogue and register every unique code used for RiCino Lap Counter. This way, no two transponders will ever be the same, no matter where you are in the world.



