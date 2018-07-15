#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "clienteboost.h"
#include "mensagem.h"



class Interface
{
private:
    enum delay{
        min = 400,
        max = 800
    };

public:
    Interface(clienteBoost* clt, thread_group* threads);
    virtual ~Interface();

    void mainLoop();
    void senderLoop();

private:
    bool validarNickname();
    void displayUsers();

    void split(std::vector<std::string>& vec, std::string str, const char& delimiter = ';');

    void popUser();

private:



    const std::string BROADCAST_KEY = "$$$";
    const std::string BROADCAST_CONECTADO = "$c$";
    const std::string BROADCAST_DESCONECTADO = "$d$";

    clienteBoost* mClt;
    std::string mNickname;
    size_t mId;
    std::string mDestino;
    std::string mIdDestino;
    std::vector<std::string> mVecUsuarios;

    boost::thread_group* mThreads;

    bool mFlagConectado;

};

#endif // INTERFACE_H
