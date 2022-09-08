# mars-rover-project
a demonstration of autonomous driving using a custom made rover platform

This project was a semester long project from 2018 with 1 partner as an effort to demonstrate how an autonomous vehicle on another planet might be constructed to suit the needs of the researchers using it. 

## Components used:
* Adafruit Feather ESP8266 Microcontroller
  * Used to control stepper motors as well as run obstacle avoidance program for self driving
  * Logging temperature and humidity to a cloud dashboard (Adafruit IO) was also tested but later not implemented due to technical restrictions with networking. 
* Raspberry Pi 3B Microcomputer
  * Used to relay live video feed from on board camera to a local webserver that could be accessed remotely over the network
* Drive Train
  * 4x NEMA 17 Stepper motors
    * Stepper motors were used for their high torque, both while rotating, and holding torque. The precision was also necessary to perform turns and move distances accurately and precicely. 
  * 4x A4899 Stepper motor drivers
    * Used to power the 4 motors
* HC SR-04 Ultrasonic Distance sensor
  * Used to sense distance infront of the rover to avoid collisions with obstacles
* LM7805 Voltage Regulator
  * Used to step down the 12 Volts from the battery down to 5 volts for the onboard microcontroller and microcomputer. 
* 12 Volt Battery Pack
  * Provided all of the power necessary for the rover to function. 
  * Solar power was considered and is normally necessary for a real mars rover deployment but since this was just a demonstration on earth of mainly autonomous driving, solar power was not necessary. 
* Chassis
  * Custom made chassis made from 1/4 Inch thich medium density fiberboard
  * Laser cut chassis and wheels from MDF and used GT2 belts as tires to provide traction
