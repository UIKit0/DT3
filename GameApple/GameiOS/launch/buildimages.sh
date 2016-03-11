#!/bin/sh


convert landscape-2048.png -gamma 0.454545 -resize 320x480^ -gravity center -extent 320x480 -gamma 2.2 Default~iphone.png
convert landscape-2048.png -gamma 0.454545 -resize 640x960^ -gravity center -extent 640x960 -gamma 2.2 Default@2x~iphone.png
convert landscape-2048.png -gamma 0.454545 -resize 640x1136^ -gravity center -extent 640x1136 -gamma 2.2 Default-568h@2x~iphone.png

convert landscape-2048.png -gamma 0.454545 -resize 1024x748^ -gravity center -extent 1024x748 -gamma 2.2 Default-Landscape~ipad.png
convert landscape-2048.png -gamma 0.454545 -resize 2048x1496^ -gravity center -extent 2048x1496 -gamma 2.2 Default-Landscape@2x~ipad.png
