# node-jontelldus
Telldus-core wrapper.

Only tested with node 5.1.0. Under development..

## Example

```javascript
var telldus = require('node-jontelldus');

telldus.getDevices(devices => 
	devices.forEach(device => console.log(device)));
```

## Methods
| method | description |
|--------|-------------|
| getDevices(callback) | get all devices |
| turnOn(deviceId) | send on signal to device | 
| turnOff(deviceId) | send off signal to device |
| addRawDeviceEventListener(callback) | add a raw device event listener |
| addSensorEventListener(callback) | add a sensor event listener |

## Properties
| property | description |
|----------|-------------|
| sensorValueType | enum with sensor value types (Temperature, Humidity, RainTotal, RainRate, WindDirection, WindAverage, WindGust) |
| method | enum with methods (TurnOn, TurnOff, Bell, Toggle, Dim, Execute, Up, Down, Stop) |

