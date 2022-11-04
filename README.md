Provides a convenient starting point if you want to start developing a plugin for ReFramed.

ReFramed exposes 5 different types of interfaces that your plugin can implement. You can choose to implement any or all of these at the same time, depending on your needs. These types are:
  1) **UI Interface**: This is the simplest interface, and allows you to register a GUI (QWidget) so it gets displayed by ReFramed. Almost all plugins implement this. If you don't need to interact with replay files or sessions (example: The BridgeLab calculator) then this is all you need. The directory ```ui``` contains an example of a UI plugin.
  2) **Replay Interface**: This interface notifies you whenever the user loads or unloads replay files. Implement this if your plugin processes frame data in any way.
  3) **Realtime Interface**: This interface lets you hook into protocol events (game start, game end, training start, etc.) and you can use it to process frame data in real time.
  4) **Visualizer Interface**: The interface plugins use to share data between each other.
  5) **Video Player Interface**: The video player interface. Unless you are directly implementing your own video player, you won't need this.


