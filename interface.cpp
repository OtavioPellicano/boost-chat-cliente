#include "interface.h"

Interface::Interface(clienteBoost *clt, thread_group *threads)
    :mClt(clt), mThreads(threads), mFlagConectado(false)
{

}

Interface::~Interface()
{
    std::cout << "destructor" << std::endl;
    mClt->pushSenderQueue("###:");
    boost::this_thread::sleep( boost::posix_time::millisec(delay::max));
    mThreads->interrupt_all();
    delete mClt;
    delete mThreads;
}

void Interface::mainLoop()
{

    for(;;)
    {
        if(mFlagConectado)
        {
            if(!mClt->reveiverQueueIsEmpty())
            {
                Mensagem msgRcv(mClt->getAndPopReceiverQueue());

                //Atualizacao de usuários conectados
                if(msgRcv.origem() == BROADCAST_KEY && msgRcv.destino() == BROADCAST_CONECTADO)
                {
                    split(mVecUsuarios, msgRcv.mensagem());
                    displayUsers();
                    continue;
                }

                //Atualizacao de usuários desconectados
                if(msgRcv.origem() == BROADCAST_KEY && msgRcv.destino() == BROADCAST_DESCONECTADO)
                {

                    std::cout << "entrei" << std::endl;
                    split(mVecUsuarios, msgRcv.mensagem());
                    std::string userDesconect = mVecUsuarios[mVecUsuarios.size() - 1];
                    popUser();
                    if(userDesconect == mNickname)
                    {
                        break;
                    }

                    displayUsers();
                    continue;

                }

            }
            boost::this_thread::sleep( boost::posix_time::millisec(delay::min));

        }

    }



}

void Interface::senderLoop()
{
    using namespace std;

    if(!validarNickname())
    {
        mClt->pushSenderQueue("###:");
        boost::this_thread::sleep( boost::posix_time::millisec(delay::max));
        mThreads->interrupt_all();
    }

    mFlagConectado = true;

    std::string strMsg;

    for(;;)
    {
        getline(cin, strMsg);




        if(strMsg == "sair")
            break;


    }

    //mandando mensagem de desconexao
    mClt->pushSenderQueue("###:");
    boost::this_thread::sleep( boost::posix_time::millisec(delay::max));
    mThreads->interrupt_all();
}

bool Interface::validarNickname()
{
    using namespace std;
    string nickTemp;
    cout << "Digite o seu nickname:" << endl;
    getline(cin, nickTemp);

    Mensagem msg;
    msg.setCabecalho(nickTemp, "");
    msg.setCorpo("");

    mClt->pushSenderQueue(msg.mensagemEstruturada());
    boost::this_thread::sleep( boost::posix_time::millisec(delay::min));

    while(!mClt->reveiverQueueIsEmpty())
    {
        Mensagem msgRcv(mClt->getAndPopReceiverQueue());

        //se o nickname é invalido
        if(msgRcv.origem().empty() && msgRcv.destino().empty())
        {
            cout << "nickname existente!" << endl;
            return false;
        }

        //se o nickname é valido
        if(!msgRcv.origem().empty() && msgRcv.destino().empty())
        {
            cout << "nickname valido" << endl;
            mNickname = msgRcv.origem();
            boost::this_thread::sleep( boost::posix_time::millisec(delay::min));
            continue;
        }

        //recebendo o primeiro broadcast de usuários conectados
        if(msgRcv.origem() == BROADCAST_KEY && msgRcv.destino() == BROADCAST_CONECTADO)
        {
            cout << "broadcast conectado" << endl;
            split(mVecUsuarios, msgRcv.mensagem());

            displayUsers();
        }

    }

    return true;

//    //Validando nickname existente
//    if(destino().isEmpty() && origem().isEmpty())
//    {
//        QMessageBox::critical(this, tr("Chat"), tr("Nickname em uso!"), QMessageBox::Ok);
//        ui->actionConectar_a_sala->setChecked(false);
//        return;
//    }


//    //recebendo nickname
//    if(destino().isEmpty() && !origem().isEmpty())
//    {
//        setNickname(origem());
//        ui->lineEdit_origem->setText(nickname());
//        setUiConectado(true);
//        return;
//    }

//    //Broadcast: #$$$$#???#:user1;user2;user3
//    if(origem() == BROADCAST_KEY &&
//            (destino() == BROADCAST_CONECTADO || destino() == BROADCAST_DESCONECTADO) &&
//            !mensagem().isEmpty())
//    {

//        if(destino() == BROADCAST_CONECTADO)
//        {
//            setListaNicknameOnline(mensagem().split(";"));
//            QString usuarioOnline = listaNicknameOnline().back();

//            for(auto itqstr = mListaNicknameOnline.begin(); itqstr != mListaNicknameOnline.end(); ++itqstr)
//            {
//                if(*itqstr == nickname())
//                {
//                    mListaNicknameOnline.erase(itqstr);
//                    break;
//                }
//            }

//            ui->listWidget_usuarios->clear();
//            ui->listWidget_usuarios->addItems(listaNicknameOnline());

//            qDebug() << "nickname: " << nickname();
//            qDebug() << "usuario online:" << usuarioOnline;

//            if(usuarioOnline != nickname())
//            {
//                QMessageBox::information(this, tr("Chat"), QString("Novo usuário online:\n%1").arg(usuarioOnline), QMessageBox::Ok);
//            }


//        }
//        else
//        {
//            setListaNicknameOnline(mensagem().split(";"));
//            ui->listWidget_usuarios->clear();

//            ui->statusBar->showMessage(QString("%1 desconectado").arg(mListaNicknameOnline.back()), 3000);

//            if(mListaNicknameOnline.back() == ui->lineEdit_destino->text())
//                ui->lineEdit_destino->clear();

//            mListaNicknameOnline.pop_back();

//            for(auto itqstr = mListaNicknameOnline.begin(); itqstr != mListaNicknameOnline.end(); ++itqstr)
//            {
//                if(*itqstr == nickname())
//                {
//                    mListaNicknameOnline.erase(itqstr);
//                    break;
//                }
//            }

//            ui->listWidget_usuarios->addItems(listaNicknameOnline());

//        }

//        return;
//    }


//    if(!origem().isEmpty() && !destino().isEmpty() && !mensagem().isEmpty())
//    {
//        if(destino() == nickname())
//            atualizarChatList(origem(), mensagem());

//        return;
//    }



}

void Interface::displayUsers()
{
    std::string display = "Usuarios online (" + std::to_string(mVecUsuarios.size() - 1) + ")\n";
    for(size_t i = 0; i < mVecUsuarios.size(); ++i)
    {
        if(mVecUsuarios[i] != mNickname)
            display += std::to_string(i) + " - " + mVecUsuarios[i] + "\n";
        else
            mId = i;
    }
    std::cout << display;
}

void Interface::split(std::vector<std::string> &vec, std::string str, const char &delimiter)
{
    vec.clear();
    if(str.empty())
        return;

    std::string::iterator itFirst = str.begin();
    std::string::iterator itSecond;
    vec.reserve(std::count(str.begin(), str.end(), delimiter) + 1);
    while((itSecond = std::find(itFirst, str.end(), delimiter)) != str.end())
    {
        vec.push_back(std::string(itFirst, itSecond));

        itFirst = itSecond + 1;
    }
    vec.push_back(std::string(itFirst, itSecond));
}

void Interface::popUser()
{
    mVecUsuarios.erase(mVecUsuarios.end() - 1);
    mVecUsuarios.shrink_to_fit();
}
