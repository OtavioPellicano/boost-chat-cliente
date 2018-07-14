#ifndef CLIENTEBOOST_H
#define CLIENTEBOOST_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <queue>
#include <iostream>
//#include <cstdlib>
#include "mensagem.h"

using namespace boost;

class clienteBoost
{
public:
    clienteBoost(const std::string &ipAddress, const unsigned int &portNum);

    void readyReadLoop();   //Faz a leitura do socket
    void senderMsgLoop();   //enviar mensagem para o servidor

    //interface:
    bool reveiverQueueIsEmpty();
    void pushSenderQueue(const std::string &strMsg);
    std::string getAndPopReceiverQueue();

    std::queue<std::string> mSenderQueue;


private:

    boost::asio::io_service mIos;
    boost::asio::ip::tcp::endpoint *mEndPoint;
    asio::ip::tcp::socket *mSock;

    std::queue<std::string> mReceiverQueue;


    boost::mutex mMtx;

//    std::string mNickname;


};

#endif // CLIENTEBOOST_H
