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

    clt = new clienteBoost("127.0.0.1", 1312);
    ui = new Interface();

    boost::thread t1(std::bind(&clienteBoost::readyReadLoop, clt));
    boost::thread t2(std::bind(&clienteBoost::senderMsgLoop, clt));
    boost::thread t3(boost::bind(&Interface::mainLoop, ui, clt, &threads));



    threads.add_thread(&t1);
    threads.add_thread(&t2);
    threads.add_thread(&t3);

    threads.join_all();

    delete clt;
    delete ui;

    return 0;
}
