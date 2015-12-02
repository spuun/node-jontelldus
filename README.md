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
| getDevices(callback(devices)) | get all devices |
| turnOn(deviceId, callback(errorCode)) | send on command to device | 
| turnOff(deviceId, callback(errorCode)) | send off command to device |
| up(deviceId, callback(errorCode)) | send up command to device |
| down(deviceId, callback(errorCode)) | send down command to device |
| bell(deviceId, callback(errorCode)) | send bell command to device |
| execute(deviceId, callback(errorCode)) | send execute command to device |
| stop(deviceId, callback(errorCode)) | send stop command to device |
| learn(deviceId, callback(errorCode)) | send learn command for device |
| addRawDeviceEventListener(callback(controllerId, data)) | add a raw device event listener |
| addSensorEventListener(callback(sensorEventData)) | add a sensor event listener |

## Properties
| property | description |
|----------|-------------|
| sensorValueType | enum with sensor value types (Temperature, Humidity, RainTotal, RainRate, WindDirection, WindAverage, WindGust) |
| method | enum with methods (TurnOn, TurnOff, Bell, Toggle, Dim, Execute, Up, Down, Stop) |
| errorCode | enum with error codes (NoError, NotFound, PermissionDenied, DeviceNotFound, MethodNotSupported, Communication, ConnectingService, UnknownResponse, Syntax, BrokenPipe, CommunicatingService, Unknown) |
