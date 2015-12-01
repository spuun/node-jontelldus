# node-jontelldus
Telldus-core wrapper.

Only tested with node 5.1.0. Under development..

## Example

```javascript
var telldus = require('node-jontelldus');

telldus.getDevices(devices => 
	devices.forEach(device => console.log(device)));
```
