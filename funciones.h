//
// Created by Gonzalo on 28/11/2022.
//

#ifndef MAIN_CPP_FUNCIONES_H
#define MAIN_CPP_FUNCIONES_H

#endif //MAIN_CPP_FUNCIONES_H


#include <iostream>
#include "clases/CFiguraGeometrica.h"
#include "clases/CLinea.h"
#include "clases/Coordenada.h"
#include "clases/CRectangulo.h"
#include "clases/Circulo.h"
#include "clases/Triangulo.h"
#include <vector>
#include "clases/Pizarra.h"
#include "helpers/TextTable.h"
#include <cmath>
using namespace std;

Pizarra* pizarra;

void imprimir_tabla(){
    TextTable t( '-', '|', '+' );
    t.add( "Nro" );
    t.add( "Tpo de figura" );
    t.add( "Datos" );
    t.endOfRow();
    cout <<"tamaño"<< pizarra->get_figuras().size()<< endl;
    if(pizarra->get_figuras().empty()){
        t.add("No hay figuras");
        t.endOfRow();
    }else{
        for(auto d: pizarra->get_figuras()){
            t.add(to_string(d->get_id()));
            t.add(d->get_nombre_figura());
            for(auto i : d->get_coordenadas()){
                t.add("("+to_string(i->get_x())+","+to_string(i->get_y())+")");
            }
            t.endOfRow();
        }
    }
    t.setAlignment( 2, TextTable::Alignment::RIGHT );
    std::cout << t;
}

vector<Coordenada*> obtener_coordenadas(int numero){
    vector<Coordenada*> c;
    int x=0;
    int y=0;
    int condition=0;
    condition = numero == 4 ? 3 : 2;
    condition = numero == 3 ? 1 : condition;
    for(int i=0;i<condition;i++){
        cout << "ingrese el x: "<< endl;
        cin>> x;
        cout << "ingrese el y: "<< endl;
        cin>> y;
        if (x < 0 || y < 0){
            cout << "No se permiten valores negativos" << endl;
            i--;
        }else if (x > 20 || y > 20){
            cout << "No se permiten valores mayores a 20" << endl;
            i--;
        }else {
            c.push_back(new Coordenada(x, y));
        }
    }
    return c;
}
int pedir_numero(){
    int numero=0;
    cout << "Ingrese una Figura"<< endl;
    cout << "1.-Linea"<< endl;
    cout << "2.-Rectangulo"<< endl;
    cout << "3.-Ciruclo"<< endl;
    cout <<"4.-Triangulo"<< endl;
    cin >> numero;
    return numero;
}

void agregar_figura() {
    int numero = pedir_numero();
    vector<Coordenada *> c = obtener_coordenadas(numero);
    if (numero == 1) {
        //LINEA
        pizarra->set_figura(new CLinea(c));
    } else if (numero == 2) {
        //PARA EL RECTANGULO
        pizarra->set_figura(new CRectangulo(c));
    } else if (numero == 3) {
        //PARA EL CIRCULO
        int r;
        cout << "Ingrese el radio: "<< endl;
        cin >> r;
        if (r < 0){
            cout << "No se permiten valores negativos" << endl;}
        else if (r > 10){
            cout << "No se permiten valores mayores a 10" << endl;}
        else if(c[0]->get_x() + r > 19 || c[0]->get_y() + r > 19 || c[0]->get_x() - r < 1 || c[0]->get_y() - r < 1){
            cout << "El circulo ingresado no cabe en el lienzo." << endl;}
        else{
            pizarra->set_figura(new Circulo(c, r));
        }
    } else {
        //PARA EL TRIANGULO
        pizarra->set_figura(new Triangulo(c));
    }
    // imprimir_tabla();
}

int eliminar_figura(){
    int id;
    imprimir_tabla();
    cout << "Que figura desea eliminar?" << endl;
    cin >> id;
    pizarra->eliminar_figura(id);
    return id;
}

void rotar(){
    int id, rotacion;
    imprimir_tabla();
    cout << "Que triangulo desea rotar?" << endl;
    cin >> id;
    cout << "Ingrese el angulo de rotacion: (90/180/270/360/-90/-180/-270/-360)" << endl;
    cin >> rotacion;
    if (pizarra->get_figuras()[id-1]->get_nombre_figura() != "Triangulo") {
        cout << "No se puede rotar una figura que no sea un triangulo" << endl;
        return;
    }

    int rotaciones = 0;

    if (rotacion == 90 || rotacion == -270) {
        rotaciones = 1;
    } else if (rotacion == 180 || rotacion == -180) {
        rotaciones = 2;
    } else if (rotacion == 270 || rotacion == -90) {
        rotaciones = 3;
    } else {
        cout << "Angulo invalido" << endl;
        return;
    }


    for(int rotacion_act = 0; rotacion_act < rotaciones; rotacion_act++){
        Coordenada esquina0 = *pizarra->get_figuras()[id-1]->get_coordenadas()[0];
        Coordenada esquina1 = *pizarra->get_figuras()[id-1]->get_coordenadas()[1];
        Coordenada esquina2 = *pizarra->get_figuras()[id-1]->get_coordenadas()[2];
        vector<Coordenada*> nuevas_coords;

        /* debug*/
        cout << "ants del cambio" << endl;
        cout << "#0 y: " << esquina0.get_y() << " x: " << esquina0.get_x() << endl;
        cout << "#1 y:" << esquina1.get_y() << " x: " << esquina1.get_x() << endl;
        cout << "#2 y:" << esquina2.get_y() << " x: " << esquina2.get_x() << endl;
        /**/

        int otro_y = 0;
        int x_menor = 20;

        for (int i = 0; i < 3; i++) {
            if(pizarra->get_figuras()[id-1]->get_coordenadas()[i]->get_x() < x_menor){
                x_menor = pizarra->get_figuras()[id-1]->get_coordenadas()[i]->get_x();
            }
        }

        if(esquina0.get_y() == esquina1.get_y()) {
            otro_y = 2;
        }
        else if(esquina0.get_y() == esquina2.get_y()) {
            otro_y = 1;
        }
        else {
            otro_y = 0;
        }

        if (pizarra->get_figuras()[id-1]->get_coordenadas()[otro_y]->get_y() != esquina0.get_y()) {
            Coordenada temporal_otro_y(pizarra->get_figuras()[id - 1]->get_coordenadas()[otro_y]->get_x(),
                                       pizarra->get_figuras()[id - 1]->get_coordenadas()[otro_y]->get_y());
            Coordenada temporal_para_cambiar = esquina0;

            esquina0.set_x(temporal_otro_y.get_x());
            esquina0.set_y(temporal_otro_y.get_y());
            if (otro_y == 1){
                esquina1.set_x(temporal_para_cambiar.get_x());
                esquina1.set_y(temporal_para_cambiar.get_y());
            } else {
                esquina2.set_x(temporal_para_cambiar.get_x());
                esquina2.set_y(temporal_para_cambiar.get_y());
            }
        }

        /* Debug */
        cout << "dsps del cambio" << endl;
        cout << "#0 y: " << esquina0.get_y() << " x: " << esquina0.get_x() << endl;
        cout << "#1 y:" << esquina1.get_y() << " x: " << esquina1.get_x() << endl;
        cout << "#2 y:" << esquina2.get_y() << " x: " << esquina2.get_x() << endl;
        /**/

        if(esquina0.get_y() < esquina1.get_y() && esquina0.get_x() > x_menor){
            //   0
            // * *
            nuevas_coords.push_back(new Coordenada(esquina0.get_x(), esquina0.get_y()));
            if (esquina1.get_x() > esquina2.get_x()) {
                //   0
                // 2 1
                nuevas_coords.push_back(new Coordenada(esquina1.get_x(), esquina1.get_y()));
                cout << "1" << endl;
                // Se usa el y de 0
                // 2 0
                //   1
                nuevas_coords.push_back(new Coordenada(esquina2.get_x(), esquina0.get_y()));
            } else{
                cout << "2" << endl;
                //   0
                // 1 2
                nuevas_coords.push_back(new Coordenada(esquina2.get_x(), esquina2.get_y()));
                // Se usa el y de 0
                // 1 0
                //   2
                nuevas_coords.push_back(new Coordenada(esquina1.get_x(), esquina0.get_y()));
            }
        }
        else if(esquina0.get_y() < esquina1.get_y() && esquina0.get_x() == x_menor){
            // 0
            // * *

            nuevas_coords.push_back(new Coordenada(esquina1.get_x(), esquina1.get_y()));
            nuevas_coords.push_back(new Coordenada(esquina2.get_x(), esquina2.get_y()));
            if (esquina1.get_x() > x_menor){
                cout << "3" << endl;
                nuevas_coords.push_back(new Coordenada(esquina1.get_x(), esquina0.get_y()));
            }
            else{
                cout << "4" << endl;
                nuevas_coords.push_back(new Coordenada(esquina2.get_x(), esquina0.get_y()));
            }
        }

        else if(esquina0.get_y() > esquina1.get_y() && esquina0.get_x() > x_menor){
            // * *
            //   0
            if (esquina1.get_x() == x_menor){
                // 1 2
                //   0
                cout << "5" << endl;
                nuevas_coords.push_back(new Coordenada(esquina1.get_x(), esquina0.get_y()));
                nuevas_coords.push_back(new Coordenada(esquina1.get_x(), esquina1.get_y()));
                nuevas_coords.push_back(new Coordenada(esquina0.get_x(), esquina1.get_y()));
            }
            else if (esquina2.get_x() == x_menor){
                // 2 1
                //   0
                cout << "6" << endl;
                nuevas_coords.push_back(new Coordenada(esquina2.get_x(), esquina0.get_y()));
                nuevas_coords.push_back(new Coordenada(esquina2.get_x(), esquina2.get_y()));
                nuevas_coords.push_back(new Coordenada(esquina0.get_x(), esquina2.get_y()));
            }
        }

        else if(esquina0.get_y() > esquina1.get_y() && esquina0.get_x() == x_menor){
            // *
            // 0 *
            if (esquina1.get_x() == x_menor){
                // 1
                // 0 2
                cout << "7" << endl;
                nuevas_coords.push_back(new Coordenada(esquina0.get_x(), esquina0.get_y()));
                nuevas_coords.push_back(new Coordenada(esquina2.get_x(), esquina1.get_y()));
                nuevas_coords.push_back(new Coordenada(esquina2.get_x(), esquina2.get_y()));
            }
            else if (esquina1.get_x() > x_menor){
                // 2
                // 0 1
                cout << "8" << endl;
                nuevas_coords.push_back(new Coordenada(esquina0.get_x(), esquina0.get_y()));
                nuevas_coords.push_back(new Coordenada(esquina1.get_x(), esquina2.get_y()));
                nuevas_coords.push_back(new Coordenada(esquina1.get_x(), esquina1.get_y()));
            }
        }
        else {cout << "No funciono" << endl; return;}

        cout << "Nuevas coordenadas" << endl;
        for (int i = 0; i < 3; i++){
            cout << "y: " << nuevas_coords[i]->get_y() << " x: " << nuevas_coords[i]->get_x() << endl;
        }
        pizarra->set_figura(new Triangulo(nuevas_coords));
        pizarra->eliminar_figura(id-1);

    }

}


void redimensionar_figura() {
    int id;
    int mult;
    imprimir_tabla();
    if (pizarra->get_figuras().empty()) {
        cout << "No hay figuras para redimensionar" << endl;
        return;
    }

    cout << "Que figura desea redimensionar?" << endl;
    cin >> id;
    if (pizarra->get_figuras()[id-1] == nullptr) {
        cout << "No existe la figura" << endl;
        return;
    }
    if (pizarra->get_figuras()[id-1]->get_nombre_figura() != "Circulo" && pizarra->get_figuras()[id-1]->get_nombre_figura() != "Rectangulo") {
        cout << "Solo se pueden redimensionar figuras con doble simetria (circulos y rectangulos)." << endl;
        return;
    }
    cout << "Ingrese el multiplicador de tamaño: " << endl;
    cin >> mult;
    if (pizarra->get_figuras()[id - 1]->get_nombre_figura() == "Circulo") {
        int radio_actual = pizarra->get_figuras()[id - 1]->get_coordenadas()[0]->get_y() -
                           pizarra->get_figuras()[id - 1]->coordenadas_centro[0]->get_y();
        int radio_nuevo = radio_actual * mult;
        bool valido = true;
        if (pizarra->get_figuras()[id - 1]->coordenadas_centro[0]->get_x() - radio_nuevo < 0 ||
            pizarra->get_figuras()[id - 1]->coordenadas_centro[0]->get_x() + radio_nuevo > 20 ||
            pizarra->get_figuras()[id - 1]->coordenadas_centro[0]->get_y() - radio_nuevo < 0 ||
            pizarra->get_figuras()[id - 1]->coordenadas_centro[0]->get_y() + radio_nuevo > 20) {
            cout << "No se puede redimensionar la figura, se sale del area de trabajo." << endl;
            valido = false;
        }
        if (valido) {
            pizarra->set_figura(new Circulo(pizarra->get_figuras()[id - 1]->coordenadas_centro, radio_nuevo));
            pizarra->eliminar_figura(id);
        }
    } else if (pizarra->get_figuras()[id - 1]->get_nombre_figura() == "Rectangulo") {
        vector<Coordenada *> coordenadas_nuevas;
        int tamanoX = abs(pizarra->get_figuras()[id - 1]->get_coordenadas()[2]->get_x() -
                          pizarra->get_figuras()[id - 1]->get_coordenadas()[0]->get_x());
        int tamanoY = abs(pizarra->get_figuras()[id - 1]->get_coordenadas()[2]->get_y() -
                          pizarra->get_figuras()[id - 1]->get_coordenadas()[0]->get_y());
        coordenadas_nuevas.push_back(
                new Coordenada(pizarra->get_figuras()[id - 1]->get_coordenadas()[0]->get_x() - tamanoX * mult / 4,
                               pizarra->get_figuras()[id - 1]->get_coordenadas()[0]->get_y() - tamanoY * mult / 4));
        coordenadas_nuevas.push_back(
                new Coordenada(pizarra->get_figuras()[id - 1]->get_coordenadas()[2]->get_x() + tamanoX * mult / 4,
                               pizarra->get_figuras()[id - 1]->get_coordenadas()[2]->get_y() + tamanoY * mult / 4));
        bool valido = true;
        for (auto coordenada: coordenadas_nuevas) {
            if (coordenada->get_x() < 1 || coordenada->get_y() < 1 || coordenada->get_x() > 20 ||
                coordenada->get_y() > 20) {
                cout << "No se puede redimensionar la figura, se sale del area de trabajo." << endl;
                valido = false;
            }
        }
        if (valido) {
            pizarra->set_figura(new CRectangulo(coordenadas_nuevas));
            pizarra->eliminar_figura(id-1);
        }

    }
}
