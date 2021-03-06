{
  "targets": [
    {
    "target_name": "jontelldus",
    "sources": [ 
  		"src/JonTelldus.cc",
      "src/Mutex.cc",
      "src/ListenerRegister.cc",
      "src/WorkerBase.cc",
      "src/QueueInvoker.cc",
      "src/Device.cc",
      "src/AddDeviceWorker.cc",
      "src/UpdateDeviceWorker.cc",
      "src/RemoveDeviceWorker.cc",
      "src/GetDevicesWorker.cc",
      "src/IntIdWorker.cc",
      "src/RemoveListenerWorker.cc",
  		"src/RawDeviceEventCallbackInvoker.cc",
      "src/SensorEventCallbackInvoker.cc",
      "src/DeviceEventCallbackInvoker.cc",
      "src/SendRawCommandWorker.cc",
      "src/DimDeviceWorker.cc"
  	],
    "conditions": [
        ['OS=="mac"', {
            'include_dirs': [
            	'/Library/Frameworks/TelldusCore.framework/Headers',
              "<!(node -e \"require('nan')\")"
            ],
            'libraries': [
            	'/Library/Frameworks/TelldusCore.framework/TelldusCore'
            ]
        }],
        ['OS=="linux"', {
          'include_dirs': [
            "<!(node -e \"require('nan')\")"
          ],
        	'link_settings': {
         		'libraries': [
         			'-ltelldus-core',
         		]
        	}
        }],
        ['OS == "win"', {
          'defines': [
            '_WINDOWS=1',
          ],
          'link_settings': {
            'libraries': [
              '-lTelldusCore'
            ],
            'library_dirs': [
              "<!(node -e \"require('nan')\")",
              'C:\\Program\\Telldus\\Development\\',
              'C:\\Program Files\\Telldus\\Development\\',
              'C:\\Program Files (x86)\\Telldus\\Development\\'
            ]
          },
          'include_dirs': [
            'C:\\Program\\Telldus\\Development\\',
            'C:\\Program Files\\Telldus\\Development\\',
            'C:\\Program Files (x86)\\Telldus\\Development\\'
          ]
        }]
      ]
    }
  ]
}
