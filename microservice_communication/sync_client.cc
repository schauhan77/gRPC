// sync_client.cc
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h" // Generated header

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::HelloService;

class HelloServiceClient {
 public:
  HelloServiceClient(std::shared_ptr<Channel> channel)
      : stub_(HelloService::NewStub(channel)) {}

  // Assembles the client's request, sends it to the server, and waits for the response.
  std::string SayHello(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_request(user);

    // Container for the response from the server.
    HelloReply reply;
    // Context for the client. It can be used to send deadlines, metadata, etc.
    ClientContext context;

    // The actual RPC call. This is a synchronous call.
    Status status = stub_->SayHello(&context, request, &reply);

    // Act upon the status of the RPC call.
    if (status.ok()) {
      return reply.reply();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<HelloService::Stub> stub_;
};

int main() {
  // Instantiate the client. It requires a channel, out of which the actual RPCs are created.
  std::string target_str = "localhost:50051";
  HelloServiceClient hello_client(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  std::string user("service 1");
  std::string reply = hello_client.SayHello(user);
  std::cout << "Client received: " << reply << std::endl;

  return 0;
}
