## Standard GRBL protocol

GRBL protocol is public and well [documented](https://github.com/gnea/grbl/wiki/Grbl-v1.1-Interface).

Essentially PC software (like LaserGRBL) send a gcode command i.e. **G0 X100 Y100** followed by **\n** newline character, the board receive the command and reply with an **ok\n** message or with an **error:x\n** message. The reception of the reply tell the sender that the command has been handled and then next commands of a job can be sent.

Also, the program may periodically send a "**?**" which asks the machine to send a status message containing [real-time information](https://github.com/gnea/grbl/wiki/Grbl-v1.1-Interface#real-time-status-reports) such as current position, alarm/idle/run status and other data.

That's all you need to know.



## VigoWork protocol (how VigoWork and L7x board talk)

**NOTE:** following info were deduced by intercepting and spying the USB communication between VigoWork software and its board using [eltima serial logger](www.eltima.com/products/rs232-data-logger).

The first difference is that Vigo does not use "**?**" but use character "**0x88**" to query status, but this is not a big issue.

Problems start with the difference in how Vigo stream the command, that is, in the way in which the machine confirms receipt of commands.

Essentially the gcode commands are sent "as-is" in the same way as grbl does, but no "**ok**" and no "**error**" messages are sent back from the board. Instead of ok/error response a special status message is sent from the board. This status message has this format:

`<VSta:2|SBuf:5,1,0|LTC:4095>`

--- TO BE CONTINUED ---






