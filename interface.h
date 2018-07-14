#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>

#include "clienteboost.h"
#include "mensagem.h"
#include "opmm-StringCsv/StringCsv.h"


class Interface
{
private:
    enum delay{
        min = 250,
        max = 500
    };

public:
    Interface();
    virtual ~Interface();

    void mainLoop(clienteBoost *clt, thread_group *threads);

private:
    bool validarNickname();
    void displayUsers();

private:

    const std::string BROADCAST_KEY = "$$$";
    const std::string BROADCAST_CONECTADO = "$c$";
    const std::string BROADCAST_DESCONECTADO = "$d$";

    clienteBoost* mClt;
    std::string mNickname;
    size_t mId;
    opmm::StringCsv mStrCsvUsuarios;

    boost::thread_group* mThreads;

};

#endif // INTERFACE_H
