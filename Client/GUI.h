//
// Created by ioana on 05.01.2018.
//

#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include "pugixml/src/pugixml.hpp"
#include "pugixml/src/pugixml.cpp"
#include "pugixml/src/pugiconfig.hpp"

using namespace pugi;

#include <iostream>
using namespace std;

class GUI {

public:
    void createMainWindow(){
        cout << "Window created" << endl;
    }

    void populateWindowWithOperations(char* operationsBuffer){
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

};


#endif //CLIENT_GUI_H
