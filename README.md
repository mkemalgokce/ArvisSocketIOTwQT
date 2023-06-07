# ArvisSocketIOTwQT
It's a arvis socket program for iot devices.
## Installation

### Dependencies
- WiringPi
- QtWebSockets

### Build 

- ``` mkdir build && cd build ```
- ``` cmake ..```
- ``` make ```

### Daemon Setup

1 - ``` sudo cp arvis-iot.service /etc/systemd/system```

2 - You should change path variables in ".service" file.

3 - "WorkingDirectory" path must include executable file and config(".ini") file.

4 - "ExecStart" path is executable files path.
