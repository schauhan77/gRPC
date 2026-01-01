# Microservice communication using gRPC protocol
Sample gRPC synchronous client and server to show communication. one microservice will send data to attached gRPC client and another microservice will receive data using attached gRPC server.
I have created sample client and server using perplexity and modified them as needed.

## Machine used
I am using ubuntu machine for building and running it

## How to build client and server

### i) Download gRPC library and build it

I have mentioned required steps below. But you can see same steps at https://grpc.io/docs/languages/cpp/quickstart/#install-grpc

```
git clone --recurse-submodules -b v1.76.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc
cd grpc
mkdir -p cmake/build
pushd cmake/build
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_CXX_STANDARD=17 \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..
make -j 4
make install
popd
```
### i) copy microservice_communication folder under grpc/examples/cpp/

```
cd examples/cpp/
```

### i) build client and server

Binary of async_client and async_server is under cmake/build . If you make changes in any file like async_client.cc, async_server.cc, message.proto
then you need to build it again.

steps for building

```
cd cmake/build
cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
make -j 4
```

### i) run client and server

start server in one tab and then run client in another tab

##### sync_server 
```
./sync_server
Server listening on 0.0.0.0:50051
Received message from : service 1
```

##### sync_client
```
cd cmake/build
./sync_client
Client received: Hello service 1
```





