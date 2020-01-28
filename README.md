# Flight-Stabilisation_Arduino
>Contains all arduino sketches that can be used for flight stabilization using the MPU60250
>All connections made using an arduino Mega
>Responses are calculated using the PID algorithm.
>PID tuning may need to be carried out on a case-by-case basis.
>Uses a library created by Jeff Rowberg
**Datacheck.ino**  Checks if data is being transferred serially to the Arduino.
**One_axis.ino** Stabilization of aircraft in one axis using a simple p controller
**3_axis.ino**  Stabiliztaion of aircraft in three axes using a simple p controller
**pid_controller.ino** Implementation of a PID controller for aircraft stabilization
