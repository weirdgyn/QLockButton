# QLockButton
QLockButton is a Qt 5 widget that implements an interactive lock button. The button itself is a timer that activates when the user press the button, if the user keep the button pressed for at given time the button change its state. This widget can be used to _secure_ some action that you don't want to be activated by a random click. The widget provided a visual indicator of the time needed to fullfill the status change.

To use this widget you should download the source code of this repository and then you can opt between:
- use the class code directly adding  ```qlockbutton.h ```,  ```qlockbutton.cpp ``` files to your code;
- include the class folder adding a  ```include(qlockbutton/qlockbutton.pri) ``` directive to your  ```.pro ``` file.

Optionally you can compile the main project file to enhance the visual integration experience (load  ```LockButton.pro ``` file).

If you have installed succesfully the plugin you can enjoy the full user experience as you can drop QLockButton into your form straight form the pallette in QtCreator (or QtDesigner), there you can manage properties as any other widget.
If you are using QLockButton trough source code then you can add the widget to the UI programatically or *promoting* a widget _placeholder_ to ```QLockButton``` class (referencing the correct header: ```qlockbutton.h``` of course).
You don't need to make the _placeholder_ square since ```QLockButton``` is beend designed to always _use_ a square footprint (inside assigned widget area).
To be notified of user interactions connect to the ```success``` and/or ```fail``` signals.
Every successul attempt to change the state of the button (i.e. keeping the button pressed for the time needed) is notified trough ```success``` signal along with the state reached by the button (```Locked```cor ```Unlocked```). If the user fails then the corresponding signal is fired (it will also report the missing time to a successfull state switch).

You can customize the look and behaviour of the widget through its properties.
You can find an example of the code needed to use this widget in the associated Qt application (```Test.pro```).

For the sake of documentation this is a complete list of ```QLockButton``` widget properties and their usage:

- ```QColor backgroundColor```: is the main color of the background (default: ```Qt::white```).
- ```QColor innerColor```: is the main color of the button actuator (default: ```Qt::blue```).
- ```QColor borderColor```: is the color of the external border of both background and pad area (default: ```Qt::black```).
- ```int borderWidth```: is the thickness of border (default: ```1```).
- ```int lockTimeout```: is the time needed to get to Locked status in milliseconds (default: ```3000```).
- ```int UnlockTimeout```: is the time needed to get to Unlocked status in milliseconds (default: ```3000```).
- ```Mode mode```: this property tells if the widget can be switched many times (```MultiShot```, default) or just one (```SingleShot```)
- ```State state```: this property read/set the internal status. You can choose between none (```Unlocked```, default) or (```Locked```).
- ```QColor fillStartColor```: is the color of the start of the fill effect gradient (default ```Qt::white```).
- ```QColor fillEndColor```: is the color of the end of the fill effect gradient (default ```Qt::red```).

There are also a number of static constants made public for reference use:
- ```DEF_INNER_RATIO```  (actuator size ratio)
- ```DEF_GLYPH_RATIO```  (lock/unlock glyph size ratio)
- ```DEF_TIMEOUT```  (default timeout for both Locking and Unlocking)
- ```MAX_TIMEOUT``` (maximum timeout value)
- ```MIN_TIMEOUT``` (minimum timeout value)
- ```DEF_UPDATE_TIMEOUT``` (this is update time in milliseconds of the fill effect)

If you are guessing how this widget may look like:

![QLockButton in all its beauty](images/screenshot1.png?raw=true "QLockButton in all its beauty")

This is the widget running in its associated Qt application.

## TODO
- Distribute as library/plugin
- Reverse fill direction (CW instead CCW)
- Translation
- Docs (doxygen)
- Add support for stylesheets
- ~~Improve lock/unlock glyph rendering quality~~
- More features...

## References
- [Qt framework](http://qt.io)
- [Google Material Icons](https://fonts.google.com/icons)

## License
Copyright 2023 Michele Santucci.
This product is released under MIT License.

## Greetings
Thanks to everyone collaborating.
#

Live long and prosper!

That's all folks.

Bye by[t]e[s]...Weirdgyn!
