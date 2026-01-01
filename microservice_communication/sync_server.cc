// greeter_server.cc
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h" // Generated header

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::HelloService;

class HelloServiceServiceImpl final : public HelloService::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override {
    std::cout << "Received message from : " << request->request() << std::endl;
    std::string prefix("Hello ");
    reply->set_reply(prefix + request->request());
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  HelloServiceServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with clients.
  builder.RegisterService(&service);
  // Assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to be shut down. Note that some synchronization is needed
  // here to prevent the process from exiting.
  server->Wait(); // Blocks until the server is shut down
}

int main() {
  RunServer();
  return 0;
}

