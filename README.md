# Creating a Nanoleaf replica

I decided to create a replica of the Nanoleaf by connecting individually addressable LEDS to an ESP32 arduino board and controlling it through the code I wrote interacting with the Blynk App giving access to controlling the lights through WiFi.

# Watch my video!
https://www.youtube.com/watch?v=9F8-3xiVmeo&t=54s&ab_channel=TonyHuang

# UML Diagram of my classes:


![UML of Arduino Lights](https://user-images.githubusercontent.com/30247851/107065392-b729c000-67aa-11eb-8f23-0e959ba0fc9c.png)

Explanation of classes:

I created a Nanoleaf class as a controller to structure my overall code. The Leaf class is created to manipulate the lights of each individaul Nanoleaf light so that they can work separately from each other. In this way this makes it more cohesive with a controller class and have less coupling by creating a Leaf class. 

The Nanoleaf class takes in information from the Blynk app and feeds the Leaf class information. The Leaf class takes that information controls all the colours on the lights through choosing different colours based on the mode that the lights are in and feeds that information back to the Nanoleaf class. The Nanoleaf class then is able to interact with the lights to change the colour. 

# How it was created:

In terms of electronics, I used an ESP32 Module to manage the individually addressable lights. I cut the lights into separate light strips of 18 LEDS and soldered wires onto them so that they could connect with each other. The physical lights were made through cardboard and styrofoam plates to diffuse the lights. Each 18 LED light strip was attached to each hexagon shaped light panel and the wires were used to connect to each other. 

# Final Product
![Nanoleaf1](https://user-images.githubusercontent.com/30247851/107066808-6915bc00-67ac-11eb-8f58-fe8b069a779c.PNG)
![Nanoleaf2](https://user-images.githubusercontent.com/30247851/107066821-703cca00-67ac-11eb-9c20-eae1c7bbb04c.PNG)

# Improvements or potential future upgrades
Design Choices:
I would have liked to 3d print the parts to make it more sustainable. This way I can make the panels more customizable so that I'm able to rearrange the panels much easier.
Coding choices:
Simplifying some of the code where it is a little bit repetitive to make it more concise.

