#include "interface.h"

Interface::Interface()
{

}

void Interface::mainLoop(clienteBoost *clt, boost::thread_group* threads)
{

    mClt = clt;

    if(!validarNickname())
    {
        threads->interrupt_all();
    }

    for(;;)
    {

    }


    threads->interrupt_all();
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


    while(!mClt->reveiverQueueIsEmpty())
    {
        Mensagem msgRcv(mClt->getAndPopReceiverQueue());

        //se o nickname é invalido
        if(msgRcv.origem().empty() && msgRcv.destino().empty())
        {
            cerr << "nickname existente!" << endl;
            return false;
        }

        //se o nickname é valido
        if(!msgRcv.origem().empty() && msgRcv.destino().empty())
        {
            mNickname = msgRcv.origem();
            continue;
        }

        //recebendo o primeiro broadcast de usuários conectados
        if(msgRcv.origem() == BROADCAST_KEY && msgRcv.destino() == BROADCAST_CONECTADO)
        {

        }

//        if(){}


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
