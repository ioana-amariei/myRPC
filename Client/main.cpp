#include <iostream>
using namespace std;

#include "Client.h"
#include "UI.h"

int main(int argc, char* argv[]){

    UI* ui = new UI(nullptr);
    ui->startUserInteraction();

    return 0;
}




