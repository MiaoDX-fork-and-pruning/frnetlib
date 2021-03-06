//
// Created by fred on 06/12/16.
//

#ifndef FRNETLIB_TCPLISTENER_H
#define FRNETLIB_TCPLISTENER_H
#include <string>
#include "TcpSocket.h"
#include "Socket.h"
#include "NetworkEncoding.h"
#include "Listener.h"

namespace fr
{

class TcpListener : public Listener
{
public:
    TcpListener() = default;
    virtual ~TcpListener() override;
    TcpListener(TcpListener &&o) = default;

    /*!
     * Listens to the given port for connections
     *
     * @param port The port to bind to
     * @return If the operation was successful
     */
    virtual Socket::Status listen(const std::string &port) override;

    /*!
     * Accepts a new connection.
     *
     * @param client Where to store the connection information
     * @return True on success. False on failure.
     */
    virtual Socket::Status accept(Socket &client) override;

    /*!
     * Calls the shutdown syscall on the socket.
     * So you can receive data but not send.
     *
     * This can be called on a blocking socket to force
     * it to immediately return (you might want to do this if
     * you're exiting and need the blocking socket to return).
     */
    virtual void shutdown() override;

    /*!
     * Gets the socket descriptor.
     *
     * @return The listen socket descriptor
     */
    virtual int32_t get_socket_descriptor() override;

    /*!
     * Sets the socket descriptor.
     *
     * @param descriptor The listen descriptor to use
     */
    virtual void set_socket_descriptor(int32_t descriptor) override;


private:
    int32_t socket_descriptor;
};

}


#endif //FRNETLIB_TCPLISTENER_H
