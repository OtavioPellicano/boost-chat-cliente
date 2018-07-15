#include <iostream>
#include <boost/thread.hpp>
#include "clienteboost.h"
#include "interface.h"

using namespace std;

int main()
{

    clienteBoost *clt;
    Interface *ui;
    boost::thread_group threads;

    try {
        clt = new clienteBoost("127.0.0.1", 1312);
    } catch (boost::system::system_error &e) {
        cerr << "Servidor desconectado.\nErro: " << e.code() << " - " << e.what() << endl;
        return e.code().value();
    }

    ui = new Interface(clt, &threads);

    boost::thread t1(std::bind(&clienteBoost::readyReadLoop, clt));
    boost::thread t2(std::bind(&clienteBoost::senderMsgLoop, clt));
    boost::thread t3(std::bind(&Interface::mainLoop, ui));
    boost::thread t4(std::bind(&Interface::senderLoop, ui));

    threads.add_thread(&t1);
    threads.add_thread(&t2);
    threads.add_thread(&t3);
    threads.add_thread(&t4);

    threads.join_all();

//    delete ui;
//    delete clt;


    return 0;
}
