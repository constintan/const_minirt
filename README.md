# MiniRT by lajudy and swilmer

###About the Task
TODO: The goal of the program is to generate
images using the Raytracing protocol.  Those
computer-generated images will each represent a
scene, as seen from a specific angle and position,
defined by simple geometric objects, and each with
its own lighting system.
[subject.pdf](11_miniRT.pdf)<br>


### Features
+ Multilight
+ Bumpmap
+ Textures
+ Checkerboard texture
+ Multithread rendering
+ Multi-light
+ Six different projection (quternions included)
+ Processing of heavy and super-heavy maps
+ Multu-scene mode
+ Old map handling, addition parser features and map-comments
+ etc. (see control keys)


### Control
`A` `W` `D` `S` — control camera position<br>
`Q` `E` — control camera height position<br>
`←` `↑` `→` `↓` — control camera direction<br>
`F` — reset camera<br>
`R` — change projection type<br>
`[` `]` — change FOV<br>
`J` `I` `L` `K` — control light position<br>
`U` `O` — control light position<br>
`1` `2` `3` `4` `5` — set minimum render quality <br>
`6` `7` `8` `9` `0` — set maximum render quality <br>
`Tab` — switch to the next scene (with ./miniRT /maps/*)<br>
`Z` — turn on/off shadows<br>
`X` — turn on/off multilight mode<br>
`Space` — choose a light in one-light-mode<br>
`C` — turn on/off lights<br>
`V` — turn on/off Specular Reflection (Phong model)<br>
`B` — turn on/off Checkerboard textures (spheres only)<br>
`N` — turn on/off Bumpmap textures (planes only)<br>
`left mouse click` — control camera direction<br>
`right mouse click` — choose shape to rotate around<br>
`Enter` — rotation mode<br>




### How to launch
Clone project to a directory then do

`$>make` to build _miniRT_ binary `./miniRT maps/map_name.rt`
<br>
Program works with special .rt files, which are descripting scene to render with special notation.

Ambient lightning:	A &emsp; 0.2 &emsp;255,255,255<br>
Camera:				C &emsp; -50.0,0,20 &emsp; 0,0,1 &emsp; 70<br>
Light:				L &emsp; -40.0,50.0,0.0 &emsp; 0.6 &emsp; 10,0,255<br>
Sphere:				sp &emsp; 0.0,0.0,20.6 &emsp; 12.6 &emsp; 10,0,255<br>
Plane:				pl &emsp; 0.0,0.0,-10.0 &emsp; 0.0,1.0,0.0 &emsp; 0,0,225<br>
Cylinder:			cy &emsp; 50.0,0.0,20.6 &emsp; 0.0,0.0,1.0 &emsp; 14.2 21.42 &emsp; 10,0,255<br>
Cone:				cn &emsp; 50.0,0.0,20.6 &emsp; 0.0,0.0,1.0 &emsp; 14.2 21.42 &emsp; 10,0,255<br>
These parameters describe shape's position, direction and color (check the subject for more specific information).



### Some visualization
![](visualization.gif)


### AUTHORS
- [lajudy (this page)](https://github.com/constintan/)
- [swilmer](https://github.com/kodet90)