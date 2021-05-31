# Rover control GUI

Project contains QT-based application written to control a small homemade rover. Rover is based on microcontroller and communicates over ESP8266 using network sockets. This app starts up a TCP server which, once connected with the rover, can visualize data from on-board sensors, monitor system events on the rover or steer it around. More complex functionality includes mission planning, where rover can (remotely) be instructed to perform series of tasks on a given timeline while reporting outcome back through this app (this functionality is supported by the rover and timed on-board, not through app).

GUI is now in integration-testing phase (with the rover) and some of the screen shots can be seen below:


'Overview' tab giving most important info<br/>
![alt tag](https://my-server.dk/public/images/roverGUI/guiOver.png)


'Instruments' tab showing plot of IMU sensor data<br/>
![alt tag](https://my-server.dk/public/images/roverGUI/guiInstr.png)


'Instruments' tab showing individual platform modules<br/>
![alt tag](https://my-server.dk/public/images/roverGUI/guiPlat.png)


'Mission planner' tab<br/>
![alt tag](https://my-server.dk/public/images/roverGUI/guiMiss.png)

'Engines data' tab<br/>
![alt tag](https://my-server.dk/public/images/roverGUI/guiEng.png)


Note: This is mostly educational project, so some parts of the code might be considered "reinventing the wheel" but were made in order to get a better understanding of coding principles and practices :)

### Credits
This project relies on following freely available libraries available on github:
 * [QtOpenCVViewerGl](https://github.com/Myzhar/QtOpenCVViewerGl) - QT Widget used for rendering OpenCV images (renders all graphs and visualizations seen in the UI)
 * [ocvGraph](https://github.com/vedranMv/ocvGraph) - OpenCV library wrote specifically for plotting graphs; developed as a part of this project
