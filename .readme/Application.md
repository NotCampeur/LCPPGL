# Application
## Brief
This class is the main application class and **the entry point** of the library.  
It is responsible for initializing the SDL2 library and manage the multiples contexts.  
This class is a [**singleton**](Singleton.md).    
## Methods
||
|-----|
|[destructor](#destructor)|
|[instance](#instance)|
|[create_context](#create_context)|
|[context](#context)|
|[destroy_context](#destroy_context)|
|[run](#run)|
|[stop](#stop)|
|[quit](#quit)|
  
### destructor
`~Application(void)`
Delete each context and quit the SDL2 library.  
  
### instance
`static Application &	instance(void)`
Returns the instance of the application and creates it if it doesn't exist. The private constructor initialize the SDL2 library.  
 
### create_context
`[Context](Context.md) &	create_context(const char *title = "LCppGL", int width = 800, int height = 600)`
Creates a new context and returns a reference to it.

### context
`[Context](Context.md) &	context(size_t index = 0) const`
Returns the context at the given index.

### destroy_context
`void	destroy_context(size_t index)`
`void	destroy_context([Context](Context.md) & context)`
Delete the context at the given index or the given context.  
  
### run
`void	run(void)`
Runs the application by calling the `update` method of each context.

### stop
`void	stop(void)`
Stops the running of the application. But does not destroy anyting.
  
### quit
`void	quit(void)`
`This method is deprecated. Use `stop` instead.`
Call the [destructor](###~Application(void)).
