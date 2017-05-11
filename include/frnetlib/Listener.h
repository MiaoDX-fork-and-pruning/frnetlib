//
// Created by fred.nicolson on 3/31/17.
//

#ifndef FRNETLIB_LISTENER_H
#define FRNETLIB_LISTENER_H
#include "Socket.h"

namespace fr
{
    class Listener
    {
    public:
        Listener()
        : ai_family(AF_UNSPEC)
        {

        }

        /*!
         * Listens to the given port for connections
         *
         * @param port The port to bind to
         * @return If the operation was successful
         */
        virtual Socket::Status listen(const std::string &port)=0;

        /*!
         * Accepts a new connection.
         *
         * @param client Where to store the connection information
         * @return True on success. False on failure.
         */
        virtual Socket::Status accept(Socket &client)=0;

        /*!
         * Calls the shutdown syscall on the socket.
         * So you can receive data but not send.
         *
         * This can be called on a blocking socket to force
         * it to immediately return (you might want to do this if
         * you're exiting and need the blocking socket to return).
         */
        virtual void shutdown()=0;

        /*!
         * Set which IP version to use. IP::any is the default
         * value, so either an IPv4 OR IPv6 interface will be used.
         *
         * @param version Should IPv4, IPv6 be used, or any?
         */
        void set_inet_version(Socket::IP version)
        {
            switch(version)
            {
                case Socket::IP::v4:
                    ai_family = AF_INET;
                    break;
                case Socket::IP::v6:
                    ai_family = AF_INET6;
                    break;
                case Socket::IP::any:
                    ai_family = AF_UNSPEC;
                    break;
                default:
                    throw std::logic_error("Unknown Socket::IP value passed to set_inet_version()");
            }
        }

    protected:
        int ai_family;
    };
}


#endif //FRNETLIB_LISTENER_H
