# node-jontelldus
Telldus-core wrapper.

Only tested with node 5.1.0. Under development..

## Methods
| method | description |
|--------|-------------|
| [getDevices](#user-content-getdevices)(callback(devices)) | get all devices |
| [turnOn](#user-content-turnon)(deviceId, callback(resultObj)) | send on command to device | 
| [turnOff](#user-content-turnoff)(deviceId, callback(resultObj)) | send off command to device |
| [up](#user-content-up)(deviceId, callback(resultObj)) | send up command to device |
| [down](#user-content-down)(deviceId, callback(resultObj)) | send down command to device |
| [bell](#user-content-bell)(deviceId, callback(resultObj)) | send bell command to device |
| [execute](#user-content-execute)(deviceId, callback(resultObj)) | send execute command to device |
| [stop](#user-content-stop)(deviceId, callback(resultObj)) | send stop command to device |
| [learn](#user-content-learn)(deviceId, callback(resultObj)) | send learn command for device |
| [addRawDeviceEventListener](#user-content-addrawdeviceeventlistener)(callback(data)) | add a raw device event listener |
| [addSensorEventListener](#user-content-addsensoreventlistener)(callback(sensorEventData)) | add a sensor event listener |
| [addDeviceEventListener](#user-content-adddeviceeventlistener)(callback(deviceEventData)) | add a device event listener |
| [sendRawCommand](#user-content-sendrawcommand)(command, callback(errorCode)) | send raw device command |
| [addDevice](#user-content-adddevice)(deviceConfiguration, callback(deviceId) | add a new device |

## Properties
| property | description |
|----------|-------------|
| sensorValueType | enum with sensor value types (Temperature, Humidity, RainTotal, RainRate, WindDirection, WindAverage, WindGust) |
| method | enum with methods (TurnOn, TurnOff, Bell, Toggle, Dim, Execute, Up, Down, Stop) |
| errorCode | enum with error codes (NoError, NotFound, PermissionDenied, DeviceNotFound, MethodNotSupported, Communication, ConnectingService, UnknownResponse, Syntax, BrokenPipe, CommunicatingService, Unknown) |

## Result object
A result object is an object with two properties; code and message. Something has probably gone wrong if code is other than errorCode.NoError. 

## Examples
Code examples is probably better than wall of text.

### getDevices
```
var jtelldus = require('jontelldus');
jtelldus.getDevices((devices) => {
  console.log(devices);
});
```

### turnOn 
```
var jtelldus = require('jontelldus');
jtelldus.turnOn(1, (err) => {
  if (err == jtelldus.errorCode.NoError) {
    console.log('On sent to device 1');
  }
});
```

### turnOff 
```
var jtelldus = require('jontelldus');
jtelldus.turnOff(1, (err) => {
  if (err == jtelldus.errorCode.NoError) {
    console.log('Off sent to device 1');
  }
});
```

### up 
```
var jtelldus = require('jontelldus');
jtelldus.up(1, (err) => {
  if (err == jtelldus.errorCode.NoError) {
    console.log('Up sent to device 1');
  }
});
```

### down
```
var jtelldus = require('jontelldus');
jtelldus.down(1, (err) => {
  if (err == jtelldus.errorCode.NoError) {
    console.log('Down sent to device 1');
  }
});
```

### bell 
```
var jtelldus = require('jontelldus');
jtelldus.bell(1, (err) => {
  if (err == jtelldus.errorCode.NoError) {
    console.log('Bell sent to device 1');
  }
});
```

### execute 
```
var jtelldus = require('jontelldus');
jtelldus.execute(1, (err) => {
  if (err == jtelldus.errorCode.NoError) {
    console.log('Execute sent to device 1');
  }
});
```

### stop
```
var jtelldus = require('jontelldus');
jtelldus.stop(1, (err) => {
  if (err == jtelldus.errorCode.NoError) {
    console.log('Stop sent to device 1');
  }
});
```

### learn
```
var jtelldus = require('jontelldus');
jtelldus.learn(1, (err) => {
  if (err == jtelldus.errorCode.NoError) {
    console.log('Learn sent to device 1');
  }
});
```

### addRawDeviceEventListener
```
var jtelldus = require('jontelldus');
jtelldus.addRawDeviceEventListener((event) => {
  console.log('RAW EVENT', event);
});
```

### addSensorEventListener
```
var jtelldus = require('jontelldus');
jtelldus.addSensorEventListener((event) => {
  console.log('SENSOR EVENT', event);
});
```

### addDeviceEventListener
```
var jtelldus = require('jontelldus');
jtelldus.addDeviceEventListener((event) => {
  console.log('DEVICE EVENT', event);
});
```

### addDevice
```
var jtelldus = require('jontelldus');
var device = {
  name: "Lamp",
  model: "selflearning-switch",
  protocol: "arctech",
  parameters: {
    house: 10,
    unit: 1
  }
};
jtelldus.addDevice(device, (err, deviceId) => {
  if (err == jtelldus.errorCode.NoError) {
    console.log('Device added. Id = ' + deviceId);
  }
});
```
