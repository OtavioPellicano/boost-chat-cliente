#include "clienteboost.h"


clienteBoost::clienteBoost(const std::string &ipAddress, const unsigned int &portNum)
{
    mEndPoint = new asio::ip::tcp::endpoint(asio::ip::address::from_string(ipAddress), portNum);

    mSock = new asio::ip::tcp::socket(mIos);

    mSock->open(mEndPoint->protocol());

    mSock->connect(*mEndPoint);

}

void clienteBoost::readyReadLoop()
{
//    std::cout << "readyReadLoop" << std::endl;
    for(;;)
    {
        if(mSock->available())
        {
            asio::streambuf buf;

            asio::read_until(*mSock, buf, '\n');

            std::string strMsg;
            std::istream inputStream(&buf);
            std::getline(inputStream, strMsg);

            std::cout << "Coloquei na pilha: " << strMsg << std::endl;

            mMtx.lock();
            mReceiverQueue.push(strMsg);
            mMtx.unlock();

        }
    }
}

void clienteBoost::senderMsgLoop()
{
//    std::cout << "senderMsgLoop" << std::endl;
    for(;;)
    {
        if(!mSenderQueue.empty())
        {
            std::cout << "Enviando mensagem..." << std::endl;
            Mensagem msg(mSenderQueue.front());

            asio::write(*mSock, asio::buffer(msg.mensagemEstruturada()));

            std::cout << "Mensagem enviada!" << std::endl;
            mMtx.lock();
            mSenderQueue.pop();
            mMtx.unlock();
            std::cout << "pop senderQueue" << std::endl;
        }
    }
}

bool clienteBoost::reveiverQueueIsEmpty()
{
    if(mReceiverQueue.empty())
        return true;
    return false;
}

void clienteBoost::pushSenderQueue(const std::string &strMsg)
{
    mMtx.lock();
    mSenderQueue.push(strMsg);
    mMtx.unlock();
}

std::string clienteBoost::getAndPopReceiverQueue()
{
    std::string strMsg =  mReceiverQueue.front();

    mMtx.lock();
    mReceiverQueue.pop();
    mMtx.unlock();

    return strMsg;
}

