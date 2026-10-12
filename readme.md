# PID Controller Project

Hi! Welcome to my repository. This is a project I made to learn about control systems and how to build a **PID Controller** from scratch.

I am building this as part of my journey learning about hardware design, embedded systems, and getting motors or robots to do exactly what I want them to do without crashing.

## What is a PID Controller?

PID stands for **Proportional, Integral, and Derivative**. it's basically a mathematical feedback trick used in engineering to keep things stable.

If you want a drone to hover at exactly 10 feet in the air, or a robot to follow a line smoothly, you use a PID controller. It constantly calculates the "error" (the difference between where you *want* to be and where you *actually* are) and adjusts the system to fix it.

Here is how I understand the three parts:

* **Proportional (P) - "The Present":** It looks at the current error. If my robot is really far off the line, it steers hard. If it's close, it steers gently.
* **Integral (I) - "The Past":** It adds up all the past errors over time. If the robot has been slightly off the line for a long time (maybe because the floor is tilted), the "I" part notices this buildup and gives it an extra push to finally get to the target.
* **Derivative (D) - "The Future":** It predicts what will happen next by looking at how fast the error is changing. If the robot is steering back toward the line way too fast, the "D" part acts like a brake so it doesn't overshoot and wobble back and forth.

### How I Wrote the Code

writing a digital PID controller means translating calculus into simple math that digital circuits or processors can handle on every clock cycle.

Here is how the logic works under the hood:

1. **Read Sensor:** Get the current position or speed.
2. **Calculate Error:** `Error = Target - Current_Sensor_Value`
3. **Calculate P:** `P = Error * Kp` (Kp is just a tuning multiplier).
4. **Calculate I:** Add the current error to a running total, then multiply by `Ki`.
5. **Calculate D:** Subtract the previous error from the current error to find the rate of change, then multiply by `Kd`.
6. **Output:** Add P + I + D together and send that signal out (usually as a PWM signal to control a motor's speed).
