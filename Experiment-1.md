# Experiment 1 - MicroServo SG90 & Photoresistor, Normal mode
<br><br/>
## Description
My goal was to create a circuit where a photoresistor would move a MicroServo arm depending on the amount of light in the room. The main question I was trying to answer was: how can light levels as an environmental input control physical movement as feedback?

I broke this task into two parts: first, controlling the servo arm with code, and second, adding a photoresistor and making the movement depend on the light level.

I started with the "Sweep" template. By changing the `pos` variable in the `for` loops, I could adjust how the motor arm moved. I also experimented with `delay()`. When I set the delay close to zero, the arm moved very quickly and the change in `pos` was difficult to notice.

Before connecting the photoresistor, I used `rand()` to generate angles between 0 and 180. This was a way to simulate changing input values. In my first version, some movements did not have the expected delay because the two `for` loops were placed one after another. I fixed this by adding an `if` statement which checked the previous and new positions, so only the correct loop could run.

After this, I connected the photoresistor with a resistor and used Serial Monitor to collect readings. I tested it in the evening with a room lamp and a torch. The torch produced values around 850–950, the lamp was around 630, and darkness was around 0–30. From these results, I chose `700` as the threshold. In the final version, the servo moves to 90 degrees when the value is above the threshold and returns to 0 degrees when it is below it.

I also tried to make the movement smooth, but the servo made a fast movement at the start which I could not control properly. For this experiment I returned to the simpler two-position version because it worked more reliably. The servo also needed to be held in place during testing, so I used a roll of tape as a temporary stand. It was not a final construction, but it made the circuit easier to test.
<br><br/>
## Components
- Arduino UNO - Open-source microcontroller board with digital and analog inputs. It reads sensor values and controls outputs like LEDs and servos.
- Breadboard - A solderless construction base used for developing an electronic circuit and wiring with microcontroller boards. Has two power rails (+ and -) and multiple component rows.
- Jumper Cables - Wires used to connect components on the breadboard to Arduino pins or to each other.
- USB-B Power Cable - Standard USB 2.0 cable with a Type-B connector. Connects the Arduino Uno to a computer USB port.
- Photoresistor - Light-dependent resistor. Its resistance depends on the light intensity: low resistance in brightness, high - in darkness.
- 10kΩ resistor - Resistor with resistence 10,000Ω. Used together with a photoresistor, converts resistance in measurable voltage.
- Servo SG90 - Small rotary actuator that can rotate to a specific angular position (0 to 180 degrees). Controlled by PWM signals from a digital pin. Contains a DC motor, gears, and a feedback potentiometer for position control.

## Content

## Technical information

## External sources
- Grammarly AI -> to improve writing and help with language barrier

## Reflection
