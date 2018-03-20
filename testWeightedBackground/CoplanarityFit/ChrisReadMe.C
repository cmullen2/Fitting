There are two methods for performing fits on both neut and proton channels.
Firstly if the data is split into separate bin dirs based on topo then you can just
configure bins twice once for each topo and set filedir differently.

Second option is we configure them without splitting topo and then they have the same bin dir but then you have to change the name of the directory to be coplanarityproton, or some such, each time.


I prefer the first option currently









