# cpplogs - A cpp standard log library
## Preparation before compilation
### `Windows`
Compile `protobuf` and `grpc`.

About `protobuf`, you can download source code from https://github.com/protocolbuffers/protobuf, and compile by yourself. Compile finished and find the path of the `protoc.exe`, configure it path into environment variables.
You can also download the executable file from https://github.com/protocolbuffers/protobuf/releases

About `grpc`, you can only compile from [source code](https://github.com/grpc/grpc.git). Before compile, you should install [nasm](https://www.nasm.us/), and configure it path into enviroment variables.
