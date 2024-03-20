# Installation

```Cmake
add_subdirectory(FileProtocol)
target_link_libraries(yourTarget FileProtocol)
```

### Then you can
```c++
#include <FileProtocol.h>
``` 

# Usage

```c++
FileProtocol protocol;
protocol.setInFile("pathToInFile");
protocol.setOutFile("pathToOutFile");
```

> - #### `setInFile` - set file for getting input params 
> - #### `setOutFile` - set file writing changed params
> - #### `getStatus` - returns true if both input and output files exist
> - #### `changeParam` - send changed param value to buffer
> - #### `exchange` - procol routine, if files locked does nothing, else clear the change buffer and returns list of changed params
> - #### `sendRequestForAllParams` - sends request to get all params, params will be recieved on the next success exchange