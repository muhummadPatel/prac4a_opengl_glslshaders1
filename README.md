##Practical 4a - _OpenGL: GLSL Shaders_

**Author** : Muhummad Yunus Patel  
**Student#** : PTLMUH006  
**Date** : 17-August-2015  

**NOTE:** Should you require any clarification, please feel free to contact me 
 at muhummad.patel@gmail.com. Thank you. :)

###Description:
This practical extends on the functionality of the previous OpenGL assignment(practical 2).
We were required to write GLSL shaders to implement Phong shading in the application we developed for the previous practical. The shaders must also be able to render textured objects. My implementations of the various requirements for this practical are outlined below.
Included in this submission, is the build folder which contains the glm library and a bunny.obj model with two textures for testing (viz. concrete.png and wicker.png).

###Phong-shading and Shader Files:
The vertex and fragment shader files were used to implement the required shader. The shader program I implemented uses Phong shading and allows for the object to be either textured, or a single uniform colour (this colour can be changed as described in the usage instructions below).
The shader uses per-pixel lighting and factors in the effect of _both_ of the lights in the scene.

###Moving Lights:
The two lights in the scene can be rotated either clockwise, or anti-clockwise around the model. To do this, press 'L' to go into light-rotation mode and then scroll the mousewheel either up or down to rotate the lights around the model (direction of scrolling controls direction of rotation). Note that both the lights will rotate around the model.

###Texturing:
When a model is loaded, the user has the option to load a texture file to texture the model. When loading a model, the user will be presented with a file dialog to open an image. If you wish to texture the model, then open an image, if not, just click cancel. If you choose not to use a texture, the default colour will be used(white).

Texture/uv co-ordinates are read from the file. The UV coordinates specified in the file are used to map the texture onto the model.

###Compiling and Running the Solution:

* Load the project into QtCreator.

* Build the project in QtCreator.

* Run the project in QtCreator. \(**NOTE**: by default, there will be no model 
 rendered. You must choose an obj file to load. see below.\)  
 \(**ALSO NOTE**: please ensure the the glm folder is in the working directory\(by
 default this is the build folder\)\)

* Loading a model and texture(texture is optional):
    * when the program starts, there will be no model.
    * open the File menu in the menu bar on the top of the screen.
    * click on Open.
    * Select the obj file to be loaded in the fileDialog that pops up.
    * Select the png texture file in the fileDialog that pops up. If you click cancel, the default colour will be used.
    * The model should then be displayed in the window.  

* Translating the model:
    * press t to enter translate mode.
    * scroll up or down with the mousewheel to translate the model in the current
     active axis.
    * press t again to toggle between the axes.  

* Rotating the model:
    * press r to enter rotate mode.
    * scroll up or down with the mousewheel to rotate the model in the current
     active axis.
    * press r again to toggle between the axes.  

* Scaling the model:
    * press s to enter scale mode.
    * scroll up or down with the mousewheel to scale the model in the current
     active axis.
    * press s again to toggle between the axes.  

* Changing the colour of the model:
    * Note that this will only work if you clicked cancel when asked to choose a texture image.
    * press either 1, 2, 3, 4, or 5.
    * this will switch between 5 preset colours.
    * the model will then be rendered in the colour preset that you selected.  

* Rotating the lights around the model:
    * press l (l for lemon) to enter rotate lights mode.
    * scroll up or down with the mousewheel to rotate the lights around the model. The direction you scroll will determine if the lights rotate clockwise or anti-clockwise.

* Resetting the Scene:
    * open the File menu from the menu bar at the top of the screen.
    * click on new/reset.
    * this will reload the current model and reset the scene (undoes any changes 
     you made to the scene).