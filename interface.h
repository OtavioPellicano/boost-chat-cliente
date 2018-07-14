#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>

#include "clienteboost.h"
#include "mensagem.h"
#include "opmm-StringCsv/StringCsv.h"


class Interface
{
public:
    Interface();

    void mainLoop(clienteBoost *clt, thread_group *threads);

private:
    bool validarNickname();

private:

    const std::string BROADCAST_KEY = "$$$";
    const std::string BROADCAST_CONECTADO = "$c$";
    const std::string BROADCAST_DESCONECTADO = "$d$";

    clienteBoost* mClt;
    std::string mNickname;
    std::vector<std::string> mVecUsuarios;

};

#endif // INTERFACE_H
