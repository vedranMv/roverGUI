# Rover control GUI

Project contains QT-based application written to control a small homemade rover. Rover is based on microcontroller and communicates over ESP8266 using network sockets. This app starts up a TCP server which, once connected with the rover, can visualize data from on-board sensors, monitor system events on the rover or steer it around. More complex functionality includes mission planning, where rover can (remotely) be instructed to perform series of tasks on a given timeline while reporting outcome back through this app (this functionality is supported by the rover and timed on-board, not through app).

GUI is still in development but some of the screen shots can be seen below:


'Overview' tab
![alt tag](https://hsr.duckdns.org/images/roverGUI/guiOver.png)


'Instruments' tab showing plot of IMU sensor data
![alt tag](https://hsr.duckdns.org/images/roverGUI/guiInstr.png)


'Mission planner' tab (in development)
![alt tag](https://hsr.duckdns.org/images/roverGUI/guiMiss.png)


Note: This is mostly educational project, so some parts of the code might be considered "reinventing he wheel" but were made in order to get a better understanding of coding principles and practices :)