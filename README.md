# DwarfStar engine

DrawfStar is a (constantly) work in progress game engine, written in C++ and based on my (also constently) work in progress, C written, CompactStar engine.

Initially DwarfStar was targetted to be a retro game engine, to create 3D games with fixed camera like **Resident Evil** or **Alone In The Dark**. But with the time, this project become my playground where I tested several new techniques who caught my attention.

<b>Here are the actual supported features</b>
- Simple shapes creation (surface, box, sphere, cylinder, disk, ring, spiral and capsule)
- Inter-Quake Model (.iqm) and Filmbox (.fbx, experimental) models
- Animations for Inter-Quake Model (.iqm) and Filmbox (.fbx) models
- Skybox
- Transparency
- Collision detection (GJK, geometry based, and models)
- Sound and music
- Cross-platform SDK written in C++

<b>Here are some screenshots of several projects I realized with this engine (all are available as demo)</b>

![Screenshot](Common/Screenshots/ThridPersonDemo.png?raw=true "Screenshot")

*A **third-person** demo with **Inter-Quake Model** animation and **GJK** based collision detection.*

![Screenshot](Common/Screenshots/FBXModelDemo.png?raw=true "Screenshot")

*A **Filmbox** animated model.*

![Screenshot](Common/Screenshots/CollisionsTest.png?raw=true "Screenshot")

*A **collision detection** test between 2 geometrical capsules.*

## Third-party
This project depends on several third-party libraries, which are:
- Glew (http://glew.sourceforge.net/)
- libPNG (http://www.libpng.org/pub/png/libpng.html)
- miniaudio (https://github.com/mackron/miniaudio)
- OpenAL (https://openal.org/)
- sxml (https://github.com/jbclements/sxml/tree/master)
- zlib (https://www.zlib.net/)

These third-party libraries depend on which OS is targetted, but are cross-platform, and are normally available on any OS. Please refer to the original website for the documentation, updates, and licenses.

Several [Blender](https://www.blender.org/) plugins were also used to export Inter-Quake (.iqm) model formats. You may find them on the following websites:
- Inter-Quake Model (.iqm) for Blender 2.49 to 2.93: https://github.com/lsalzman/iqm

## How to easily create animated characters
Below is a very simple method to create high quality animated characters which may be loaded with the provided reader.

### Prerequisites
You will need the following applications, all of them are free and may be downloaded from their official website:
- [Makehuman](http://www.makehumancommunity.org/)
- [Blender](https://www.blender.org/)
- The [Inter-Quake Model](https://github.com/lsalzman/iqm) exporter for Blender
- [HxD Editor](https://mh-nexus.de/en/hxd/)

An account to the [Adobe Mixamo](https://www.mixamo.com/) website is also required, you can create one for free if you still don't have one.

### Create the character with Makehuman
The first step is to create a character with Makehuman. The application provides a very large range of parameters allowing to create a huge variety of human characters, and in addition, the application provides a large library of clothes, topologies, and accessories, created and shared by other users.

![](Common/Screenshots/makehuman.png)
To create a character exportable as an .iqm model, you will need to:
- Under the *Geometries=>Topologies* tab, select the **Proxy741** proxy, or any available low polygon proxy. Don't use a proxy containing too many polygons, otherwise the export to .iqm file may fail later.
- Configure your model as desired.
- Under the *Pose/Animate=>Skeleton* tab, select the **Game Engine** skeleton.
- Once ready, under the *Files=>Export* tab, select the **Filmbox (fbx)** mesh format. Ensure that the **Feet on ground** and **Binary FBX** options are checked, then select a name and click on the **Export** button.

### Animate with Mixamo
The second step is to animate your character with Mixamo. The website provides a very large range of ready-to-use realistic animations, you just need to select which you want and to configure it.

![](Common/Screenshots/mixamo.png)

To animate your model, you will need to:
- Once logged, click on the *Upload Character* button, and select the model you exported from MakeHuman. Check if the model is well animated on the import end.
- Select the animation you want.
- Check the **In place** checkbox, and configure your animation.
- Click on the *Download* button, and select **FBX Binary (.fbx)** and **With skin** options. Click again on the *Download* button.

### Convert to .iqm with Blender
The third step is to convert the animated .fbx model to .iqm with Blender.

![](Common/Screenshots/blender.png)

To do that, you will need to:
- Create a new scene and clean it completely.
- Click on *File=>Import=>FBX (.fbx)* and select the animated model you exported from Mixamo.
- Select the *Animation view* (Ctrl+PgUp/Dn) and correct the animation length.
- Play the animation to check if all is working well.
- On the right panel tree, expand the *Game Engine=>Animation* items, and rename the **Game_engine|mixamo.com|Layer0** item to a name describing your animation.
- Optionally you may also rename the **Game Engine** item to your model name.
- Select Object Mode and select your whole model (press the A key).
- Click on *File=>Export=>Inter-Quake Model (.iqm, .iqe)*. In the *Animation* edit, enter the animation name you set on the tree item.

![](Common/Screenshots/blender_export.png)

- Ensure that all the checkboxes are checked, except the **Vertex Colors** one. Under *Materials*, select **Image**.
- Click on the *Export IQM* button.

...and voila!

**NOTE** in order to be opened with the c++ reader, you'll need to copy the textures exported by Makehuman next to the .iqm model. You'll have also to convert the image to Targa (.tga) format and to change the png to tga format in the .iqm file by using an hex editor like e.g. HxD.
## License

I decided to share this code freely (under MIT license), don't hesitate to use it if you think it useful for your purposes. Any collaboration on this project is welcome.
