# node-jontelldus
Telldus-core wrapper.

Under development, poorly tested. I've used node 5.1.0.

## Methods
| method | description |
|--------|-------------|
| [getDevices](#user-content-getdevices)(callback(devices)) | get all devices |
| [addDevice](#user-content-adddevice)(deviceConfiguration, callback(deviceId) | add a new device |
| [removeDevice](#user-content-removedevice)(deviceId, callback(err)) | remove a device |
| [updateDevice](#user-content-updatedevice)(deviceId, deviceConfiguration, callback(err, deviceId)) | update a device |
| [turnOn](#user-content-turnon)(deviceId, callback(error)) | send on command to device | 
| [turnOff](#user-content-turnoff)(deviceId, callback(error)) | send off command to device |
| [up](#user-content-up)(deviceId, callback(error)) | send up command to device |
| [down](#user-content-down)(deviceId, callback(error)) | send down command to device |
| [bell](#user-content-bell)(deviceId, callback(error)) | send bell command to device |
| [execute](#user-content-execute)(deviceId, callback(error)) | send execute command to device |
| [stop](#user-content-stop)(deviceId, callback(error)) | send stop command to device |
| [learn](#user-content-learn)(deviceId, callback(error)) | send learn command for device |
| [addRawDeviceEventListener](#user-content-addrawdeviceeventlistener)(callback(data)) | add a raw device event listener |
| [addSensorEventListener](#user-content-addsensoreventlistener)(callback(sensorEventData)) | add a sensor event listener |
| [addDeviceEventListener](#user-content-adddeviceeventlistener)(callback(deviceEventData)) | add a device event listener |
| [sendRawCommand](#user-content-sendrawcommand)(command, callback(error)) | send raw device command |

## Properties
| property | description |
|----------|-------------|
| sensorValueType | enum with sensor value types (Temperature, Humidity, RainTotal, RainRate, WindDirection, WindAverage, WindGust) |
| method | enum with methods (TurnOn, TurnOff, Bell, Toggle, Dim, Execute, Up, Down, Stop) |
| errorCode | enum with error codes (NoError, NotFound, PermissionDenied, DeviceNotFound, MethodNotSupported, Communication, ConnectingService, UnknownResponse, Syntax, BrokenPipe, CommunicatingService, Unknown) |

## Examples
Code examples is probably better than wall of text.

### getDevices
```
var jtelldus = require('jontelldus');
jtelldus.getDevices((devices) => {
  console.log(devices);
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
  if (!err) {
    console.log('Device added. Id = ' + deviceId);
  }
});
```


### removeDevice
```
var jtelldus = require('jontelldus');

jtelldus.addDevice(1, (err) => {
  if (!err) {
    console.log('Device 1 removed');
  }
});
```

### updateDevice
```
var jtelldus = require('jontelldus');
var device = {
  name: 'Blue lamp'
  parameters: {
    house: 10,
    unit: 3
  }
};
jtelldus.addDevice(1,, device (err, deviceId) => {
  if (!err) {
    console.log('Device updated. Id = ' + deviceId);
  }
});
```

### turnOn 
```
var jtelldus = require('jontelldus');
jtelldus.turnOn(1, (error) => {
  if (!error) {
    console.log('On sent to device 1');
  }
});
```

### turnOff 
```
var jtelldus = require('jontelldus');
jtelldus.turnOff(1, (error) => {
  if (!error) {
    console.log('Off sent to device 1');
  }
});
```

### up 
```
var jtelldus = require('jontelldus');
jtelldus.up(1, (error) => {
  if (!error) {
    console.log('Up sent to device 1');
  }
});
```

### down
```
var jtelldus = require('jontelldus');
jtelldus.down(1, (error) => {
  if (!error) {
    console.log('Down sent to device 1');
  }
});
```

### bell 
```
var jtelldus = require('jontelldus');
jtelldus.bell(1, (error) => {
  if (!error) {
    console.log('Bell sent to device 1');
  }
});
```

### execute 
```
var jtelldus = require('jontelldus');
jtelldus.execute(1, (error) => {
  if (!error) {
    console.log('Execute sent to device 1');
  }
});
```

### stop
```
var jtelldus = require('jontelldus');
jtelldus.stop(1, (error) => {
  if (!error) {
    console.log('Stop sent to device 1');
  }
});
```

### learn
```
var jtelldus = require('jontelldus');
jtelldus.learn(1, (error) => {
  if (!error) {
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

### sendRawCommand
```
var jtelldus = require('jontelldus');
var command = 'class:command;protocol:waveman;model:codeswitch;house:A;unit:1;method:turnoff;';
jtelldus.sendRawCommand(command, (error) => {
  if (error) {
    console.log(error);
  }
});
```
