## Why I'm doing the project  
I started this project to help my father keep track of his camper’s water supply. My father had to check the water level every morning and make
sure the flow from the spring hadn’t stopped. If the flow stopped, he would need to manually insert a water house into the pipe and 
Back flush the water lines to rid any sand that may have stopped up the line. We installed screens at the spring house to help catch most of the sand  
but some would still make it through. The lines would also become airlocked (I have a plane for this) and the backflushing would rid the lines of this blockage. 


## About the project
In the early stages I used an incandescent lamp in series with a tilt switch. This would give my father a visual indication as to when the water level  
was below the threshold and needed attention. But this didn’t tell him what the problem was, it just told him there was a problem that needed 
attention. I wanted a system that would automate the whole process for him with as little human interaction as possible. So, I started working  
on a modular automated system that would do the things he needed. 

I wanted to track water flow and water level also keeping things open and cable of upgrading/dating the system and capabilities in the future.  

## How it works
Utilizing an Arduino as the brain, the system monitors the water level and flow via a tilt switch, float, and a water flow sensor. When the water 
level falls low enough the tilt switch makes contact and the water level input pin on the Arduino is pulled low. This pin is read by the Arduino, 
relay 1 is then activated thus activating a servo that switches the position of a 3-way water valve blocking flow into the holding tank and opening 
access to the water lines. Five seconds later the Arduino activates relay 2 turning on a pump. This pump feeds water back into the water line 
backflushing the lines and removing all sand and airlocks. After running for one minute relay 2 deactivate turning off the pump. After 5 seconds 
relay 1 deactivates, this activates the 3-way water valve moving it back into its home position allowing water from the spring to once again 
flow into the holding tanks.  
The system also has a manual mode where at any time the sequence of operation can be performed when desired. 

## Field units 
[3-way water valve](https://www.aliexpress.us/item/3256804648845790.html?spm=a2g0o.order_list.order_list_main.5.695718020k35QP&gatewayAdapt=glo2usa)    
[5GPM submergible pump](https://www.amazon.com/dp/B09ZV2364K?psc=1&ref=ppx_yo2ov_dt_b_product_details)    
[water flow meter](https://www.adafruit.com/product/5066)     
[4 relay board](https://www.amazon.com/dp/B00E0NSORY?ref=ppx_yo2ov_dt_b_product_details&th=1)  
[Water circulator pump](https://www.amazon.com/dp/B0196WL55G?psc=1&ref=ppx_yo2ov_dt_b_product_details) *For testing water flow sensor  

## Control and display:
-[Arduino Uno wifi](https://store-usa.arduino.cc/collections/boards-modules/products/arduino-uno-wifi-rev2?_pos=5&_fid=1e131e922&_ss=c)  
-[AdaFruit LCD Screen with I2C backpack](https://www.adafruit.com/product/292)    
-Various buttons and switches  

## Power:
120 input -> 12DC output power supply
