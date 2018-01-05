//
// Created by ioana on 05.01.2018.
//
#include "GUI.h"
#include <iostream>

#include "pugixml/src/pugixml.hpp"
#include "pugixml/src/pugiconfig.hpp"
#include "pugixml/src/pugixml.cpp"

using namespace pugi;
using namespace std;


GUI::GUI(Client *client) {
    this->client = client;
}

void GUI::createMainWindow(){
    cout << "Window created" << endl;
}

void GUI::populateWindowWithOperations(char* operationsBuffer){
    xml_document doc;
    xml_parse_result result = doc.load_string(operationsBuffer);

    if (!result) {
        cout << "parsed with errors" << endl;
        cout << result.description() << endl;
    }

    xml_node operations = doc.document_element();
    for (xml_node operation : operations.children()) {
        cout << "detalii" << endl;
        cout << operation.child("name").child_value() << endl;
        cout << operation.child("resultType").child_value() << endl;
        cout << endl;
    }
}