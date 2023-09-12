#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "../hashMaterials/hashmap.h"

struct Response{ //helper struct 
    std::string type;
    std::string filename;
    size_t dataSize;
};

struct Request{
    std::string command;
    std::string filename;
};

struct File{
    std::string filename;
    std::vector<uint8_t> data;
};

void xorDecryption(char* buffer, ssize_t size) { 
    const char key = 42;
    for (ssize_t i = 0; i < size; ++i) {
        buffer[i] = buffer[i] ^ key;
    }
}

void xorEncryption(uint8_t* buffer, size_t size) {
    const uint8_t key = 42;
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = buffer[i] ^ key;
    }
}

int main(){
    //! Q1

    // sockets 
    int serverSocket, clientSocket, serverBind, serverListen;
    // for arguments
    struct sockaddr_in my_addr, client_addr;
    socklen_t addrlen = sizeof(client_addr);

    //! Q2 end
    HashMap<std::string, std::vector<uint8_t> > fileHashMap;

    //Creating a socket modelled after lecture from last year on UNIX SOCKET FUNCTIONS (lecture 18)
    serverSocket = socket(AF_INET, SOCK_STREAM,0); 
    if (serverSocket == -1){
        std::cerr << "Socket was unable to be created." << std::endl;
        return 1;
    }

    // defining sockaddr_in struct - from notes taken on lecture 18
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8081);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    // Binding modelled after lecture from last year on UNIX SOCKET FUNCTIONS (lecture 18)
    serverBind = bind(serverSocket,(struct sockaddr *) &my_addr, sizeof(my_addr)); 
    if (serverBind == -1){
        std::cerr << "Error while binding." << std::endl;
        return -1;
    }

    // Listening modelled after lecture from last year on UNIX SOCKET FUNCTIONS (lecture 18)
    serverListen = listen(serverSocket,10);
    if (serverListen == -1) {
        std::cerr << "Error while listening." << std::endl;
        return -1;
    }

    std::cout << "Listening (port 8081)..." <<std::endl;

    // Accepting using infinite loop
    //! Q5
    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*) &client_addr, &addrlen);
        if (clientSocket == -1){
            std::cerr << "Error accepting" << std::endl;
            continue;
        }

        std::cout << "Accepted Connection" << std::endl;


    const int buffSize = 1024;
    char buffer[buffSize];
    memset(buffer,0,buffSize);

    ssize_t bytesRead = recv(clientSocket, buffer, buffSize - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Unable to recieve data" << std::endl;
        close(clientSocket);
        continue;
    }

    //! Q6
    xorDecryption(buffer,bytesRead);

//! Q7
std::string type(buffer, bytesRead);

if (type == "Request") {
    Request request;
    if (recv(clientSocket, &request, sizeof(Request),0) == -1) {
        std::cerr << "Couldn't recieve the request" << std::endl;
        close(clientSocket);
        continue;
    }

    if (request.command == "download") {
        std::cout << "download request recieved" << request.filename << std::endl;

        //! Q9 start
        if (fileHashMap.contains(request.filename)) {
            std::vector<uint8_t> fileData = fileHashMap.get(request.filename);

            Response response;
            response.type = "Response";
            response.filename = request.filename;
            response.dataSize = fileData.size();

            if (send(clientSocket, &response, sizeof(Response), 0) == -1) {
                std::cerr << "Unable to send response" << std::endl;
                close(clientSocket);
                continue;
            }

            if (send(clientSocket, fileData.data(), fileData.size(), 0) == -1) {
                std::cerr << "Unable to send file data" << std::endl;
                close(clientSocket);
                continue;
            }

            std::cout << "sent response for file: " << response.filename << " with size: " << response.dataSize << std::endl;
            //! Q9 end
        } else {
            std::cout << "File requested was not found in the hash map: " << request.filename << std::endl;
        }
    } else if (request.command == "upload") {
        std::cout << "Upload request recieved" << request.filename << std::endl;
    }
    } else if (type == "File") {
        File file;
        if (recv(clientSocket, &file, sizeof(File), 0) == -1) {
            std::cerr << "couldn't recieve file" << std::endl;
            close(clientSocket);
            continue;
        }
        std::cout << "recieved file: " << file.filename << " with size: " << file.data.size() << std::endl;

        //! Q8
        std::vector<uint8_t> fileData(file.data.begin(), file.data.end());
        fileHashMap.insert(file.filename, fileData);
        std::cout << "The File has been inserted into a hashamap" << file.filename << std::endl;

        //!Q10
        File encryptedFile = file;
        xorEncryption(encryptedFile.data.data(), encryptedFile.data.size());

        if (send(clientSocket, &encryptedFile, sizeof(File), 0) == -1) {
            std::cerr << "Failed to send encrypted file" << std::endl;
            close(clientSocket);
            continue;
        }

        std::cout << "Sent encyrpted file back to the client" << std::endl;
    }

    }

    close(serverSocket);

return 0;
}