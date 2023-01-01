# PinballNudgeRelay

If you have an Arcade Legends Pinball you probably have discovered that he built in accelerometer that enables nudge detection is sensitive to the levels
of table sound and haptic feedback settings.  If you have made any mods to improve the haptics you have know that the problem gets worse and that the built in accelerometer most likely will need to be disabled.
<BR><BR>
This project is intended to restore the nudge functionality be enabling an external device made of an Arduino Pro Micro mpu6050 accelerometer and relay
board to activate the built in nudge buttons when the pinball cabinet is physically nudged.  The mod retains the existing button functionality as well.
<BR><BR>
This technique could also be used for more traditional Visual Pinball builds but a KL25Z based solution would be a better overall.
<BR><BR>
If AtGames ever adds low pass filtering to their accelerometer this mod may become unnecessary.
<BR>
<BR>
<img src="https://github.com/j2robin/PinballNudgeRelay/blob/main/PinballNudgeRelay.jpg" alt="Fig1" width="500" height="600"></img>
<BR><BR>
Parts Needed:
<BR>
These are the parts I used.  Anything similar from the retailer of your choice should work but you may have to adjust as connection labels and pin numbers may be different.
<BR>
<BR>
Pro Micro Arduino clone.  Any Arduino should work although you might have to use different pins than those used in this example.
<BR>
https://www.amazon.com/dp/B01KJR41J4?psc=1&ref=ppx_yo2ov_dt_b_product_details
<BR>
<BR>
Pro Micro Mount:<BR>
I simply used small screws to secure the MPU6050 module and the relay module to a piece of wood.  The pro Micro doesn't have any mounting holes so I 3D printed this stl to secure the Pro Micro to the wood before securing the entire assembly to the interior of the ALP using double sided tape.  If you decide to mount this way you might solder the Pro Micro header pins to the parts side of the Pro Micro instead of the bottom like I did.  This should give you more clearance for the Micro USB cable and leave the LEDs visible.
https://www.thingiverse.com/thing:3745009
<BR><BR>
MPU6050:
<BR>
https://www.amazon.com/dp/B008BOPN40?psc=1&ref=ppx_yo2ov_dt_b_product_details
<BR>
<BR>
Relay Board:
<BR>
https://www.amazon.com/dp/B00E0NSORY?ref=ppx_yo2ov_dt_b_product_details&th=1
<BR>
<BR>
Spade Connectors:
<BR>
https://www.amazon.com/dp/B01MYTWTE2?psc=1&ref=ppx_yo2ov_dt_b_product_details
<BR>
<BR>
Module Wiring:<BR>
<table>
  <tr><th>Pro Micro</th><th>MPU6050</th><th>Relay Module</th></tr>
  <tr><th>GND</th><th>GND</th><th></th></tr>
  <tr><th>VCC</th><th>VCC</th><th></th></tr>
  <tr><th>2 (SDA)</th><th>SDA</th><th></th></tr>
  <tr><th>3 (SCL)</th><th>SCL</th><th></th></tr>
  <tr><th>GND</th> <th></th><th>GND</th></tr>
  <tr><th>RAW</th> <th></th><th>VCC</th></tr>
  <tr><th>4</th> <th></th><th>IN1</th></tr>
  <tr><th>5</th> <th></th><th>IN2</th></tr>
  <tr><th>6</th> <th></th><th>IN3</th></tr>
</table>
<BR>
Cabinet Wiring:<BR>
I created a wring harness that will enable the relay to close the physical nudge buttons.  This can be done with two wires for each contact of each button.  On one end join the two wires together and crimp into one of the connectors.  I joined them together on the female (button) end of the wire but the male end for the existing wire would work just as well. On the other end of the wire crimp the other gender connector.  This will allow you to tap into that wire to the button while leaving the button function intact.
<BR><BR>
I made six of these, two for each button.  The un-crimped tap wire will go to the NO contacts for each of the three relays.  I removed the existing button wires from the buttons and attached this harness in their place with the existing wires then plugged into the harness.
<BR>
<BR>
<img src="https://github.com/j2robin/PinballNudgeRelay/blob/main/Pinball%20wiring%20Diagram.jpg" alt="Fig2" width="500" height="600"></img>
<BR><BR>
Power:<BR>
I Powered the Pro Micro through the micro USB port.  I run a USB cable outside the cabinet to a USB adapter so that I can make adjustments to the sketch if needed.  I will likely power it from some internal source once I am satisfied that I will no longer be tweaking any values or code.  You might power it from the ALU's usb port or if you use solenoids for flipper feedback like I do you might use a 12V to 5V adapter like this one.  https://www.amazon.com/gp/product/B0B24MF21J/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&th=1. Make sure the power supply you use has enough headroom doe the additional drain though.
<BR><BR>
Adjusting Constants:<BR>
I have tweaked the constant values for acceleration for the nudge directions to suit me.  I prefer a relatively light touch in the horizontal directions so I don't have to nudge too hard.  I did find that I needed to increase the forward nudge force slightly to reduce false activations from using the plunger.  You may need to adjust the constant values to your own taste if you find my defaults to light or heavy.
<BR><BR>
const float XNUDGE_FORCE = .6;<BR>
const float YNUDGE_FORCE = .8;
<BR>
<BR>
Disclaimers:
<BR>
I have documented what I have done to implement this project for my own use.  If you choose to use my code or follow my directions I take no responsibility if you break something, void your warranty, hurt someone or cause the world to come to an end or anything in between.  If you choose to build this project you do so completely at your own risk and there is no warranty of any kind.
