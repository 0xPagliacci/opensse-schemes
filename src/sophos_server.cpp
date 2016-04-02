//
//  sophos_server.cpp
//  sophos
//
//  Created by Raphael Bost on 30/03/2016.
//  Copyright © 2016 Raphael Bost. All rights reserved.
//

#include "sophos_server.hpp"

#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>


namespace sse {
    namespace sophos {


SophosImpl::SophosImpl() {

}

grpc::Status SophosImpl::setup(grpc::ServerContext* context,
                    const sophos::SetupMessage* request,
                    google::protobuf::Empty* e)
{
    
    std::cout << "Setup!" << std::endl;
    
    return grpc::Status::OK;
}

grpc::Status SophosImpl::search(grpc::ServerContext* context,
                    const sophos::SearchRequestMessage* request,
                    grpc::ServerWriter<sophos::SearchReply>* writer)
{
    std::cout << "Search!" << std::endl;
    
    uint32_t r_count = request->add_count();
    
    for (uint32_t i = 0; i < r_count; i++) {
        sophos::SearchReply reply;
        reply.set_result((uint64_t) i);
        
        writer->Write(reply);
    }
    
    return grpc::Status::OK;
}

grpc::Status SophosImpl::update(grpc::ServerContext* context,
                    const sophos::UpdateRequestMessage* request,
                    google::protobuf::Empty* e)
{

    std::cout << "Update!" << std::endl;
    std::cout << "Token: " << request->update_token() << std::endl;
    std::cout << "Index: " << request->index() << std::endl;
    
    
    return grpc::Status::OK;
}

void run_sophos_server() {
    std::string server_address("0.0.0.0:4242");
    SophosImpl service;
    
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

} // namespace sophos
} // namespace sse

int main(int argc, char** argv) {
    // Expect only arg: --db_path=path/to/route_guide_db.json.
    sse::sophos::run_sophos_server();
    
    return 0;
}