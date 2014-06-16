Restoration
===========

Game project for CSC 476

### Authors
* Aaron Jacobs
* Aargon Gragg
* Cody Thompson
* Thomas Sanford
* Nathan Farnum
* Cameron Nouri

### Overview / Synopsis

The world has become desolate. Everyone I knew and loved... My family, my friends... Have been taken by the Umbran. They ravaged the land... But I will stop them. I will traverse across this ruinous landscape using the sacred Keys of Wasd, leaping and bounding using the Bar of Space over all obstacles in my way. I have been chosen by destiny, it seems, for I have been given the power to vanquish them. By using my Vis - my life energy - I can purify those monsters and add their life to my own. My Vis already purifies the world around me, giving me a tangible, visible hope. By channeling my Vis, I can fire a Justitia blast in whatever direction the Arrow of Guidance chooses. This is the only weapon that can stop the many kinds of Umbrans that I will face. The Corona, the rank-and-file pawns, just walk back and forth; showing that they’re tactics are as empty as their hearts. The Obex, the automated traps, hinder my advancing. Their spikes are strong, but their paths are easy to follow and overcome. The Turris, the steadfast towers, aim to shoot me down while maintaining their ground. They too can channel their Vis, firing Aegrum wherever I go. Luckily, my Justitia can block their Aegrum. The Vagus, the dive-bombing fiends, lie in wait for my arrival. They don’t seem to be alive until I come close, and then they relentlessly pursue. The Magus, the , is the most tenacious of all. His Aegrum are lethal, and his movements misleading and sudden. I must take him down quickly, before he gets the chance to fight back. The Judex, the fallen Judge, awaits me at the end of my quest. I must conquer him if I am to save this world. I must not fail in my endeavor... I shall not fail! This world has waited too long for its Restoration.

### Controls

* Mouse movement: Specifies direction of player attack
* Mouse click: Shoots Justitia
* `a` key: Moves left
* `d` key: Moves right
* `space` key: Jump
* `esc` key: Quits the game
* `~` key: Toggels level edit mode
* `z` key: The Zoë effect. For when there just aren't enough particles for all your particle needs.

### Technologies

**Shadow Mapping**

Point light with high resolution shadows by having the projection be a constant bias away from the character at all times. The orthographic projection only encompasses the visibile scene.

**Animation**

The system supports skeletal animation as well as switching between animations with a single call. All animation transformations are applied on the GPU with a list of bones and weights computed on the CPU.

**Animated Character**

The main character, Leoht, has idle, running, and jump skeletal-based animations, fully textured in Maya.

**Aura**

Using a stencil buffer, we specified what should be drawn in multiple render passes. Then, after all framebuffers are set up, alpha blending is applied to the scene to merge the scenes together.

**Ambient Lighting**

Ambient light color is determined by looking up a value from a heavily blurred version of the active skybox, and averaging it with a global scene color. The end result is that objects appear to 'fit' better in the scene, and their colors change between the light and dark render passes.

**Ambient Occlusion**

We have toggleable screen space ambient occlusion. This is achieved by bluring the depth buffer with the application of a threshold, and then subtracting the original depth buffer. The values are then scaled and contained between 0 and 1. The inverse of this value is applied to the alpha of the pixels of a black plane infront of the camera to get a basic ambient occlusion effect.

**Particle Effects**

The particle effects include a versatile particle effect function that creates a variable number of particles with velocity, acceleration, spread, size, and duration.

**Audio**

Using FMod, a seperate class was packaged with the functionality to switch tracks, play tracks, and loop tracks.

**Level Editor**

The level editor started with a mouse trace from a 2D plane into a 3D world to easily select objects. After we added abilities to use it more efficiently like copying and pasting objects.

**View Frustum Culling**

Each object in the scene is checked against the view frustum. If the object, based on its bounding box, is outside of the 6 planes of the view frustum, it is not drawn, saving effort by the GPU. The 6 planes are updated each draw call, based on the view-projection matrix.

### References

* Skybox - http://ogldev.atspace.co.uk/www/tutorial25/tutorial25.html
* Animations - http://ephenationopengl.blogspot.com/2012/06/doing-animations-in-opengl.html
* Ambient lighting - http://blog.wolfire.com/2010/03/Image-based-ambient-lighting
* Shadow mapping - http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/
