#Application:
This class is the main application class and **the entry point** of the library.  
It is responsible for initializing the SDL2 library and manage the multiples contexts.  
This class is a [**singleton**](Singleton.md).    
## Methods
### `Application(void)` This constructor is private and is called by the [`instance()`](#`static Application &	instance(void)`) method.
Constructor of the class which initialize the SDL2 library.  
  
### `~Application(void)`
Delete each context and quit the SDL2 library.  
  
### `static Application &	instance(void)`
Returns the instance of the application and [creates](#`Application(void)` This constructor is private and is called by the [`instance()`](#`static Application &	instance(void)`) method.) it if it doesn't exist.  
  
### `[Context](Context.md) &	create_context(const char *title = "LCppGL", int width = 800, int height = 600)`
Creates a new context and returns a reference to it.
### `[Context](Context.md) &	context(size_t index = 0) const`
Returns the context at the given index.
### `void	destroy_context(size_t index)`
### `void	destroy_context([Context](Context.md) & context)`
Delete the context at the given index or the given context.  
  
### `void	run(void)`
Runs the application by calling the `update` method of each context.
### `void	stop(void)`
Stops the running of the application. But does not destroy anyting.
  
### `void	quit(void)` This method is deprecated. Use `stop` instead.
Call the [destructor](#`~Application(void)`).
