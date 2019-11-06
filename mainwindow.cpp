#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QStandardItemModel>
#include <QTableWidget>
//using namespace std;

/* --------------------------------------------------------------------------- FUNCIÓN DE TRANSICIÓN --------------------------------------------------------------------------- */
                /*   0   1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31  */
                /*   l    L   d    _    .    E    e    +    -    '    "    #    *    /    %    &    |    =    >    <    !    :    ,    ;    (    )    [    ]   !=   \b   \n   \t  */
int static M[19][32] = {
     /* 0 */     {   1,   2,   3, 500, 124, 500, 500, 108, 109,   9,  11,  12, 110, 111, 112,  17,  18,  13,  16,  15,  14, 125, 124, 123, 126, 127, 128, 129, 500,   0,   0,   0 },
     /* 1 */     {   1,   2,   2,   2, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 },
     /* 2 */     {   2,   2,   2,   2, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101 },
     /* 3 */     { 102, 102,   3, 102,   4, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102 },
     /* 4 */     { 501, 501,   5, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501 },
     /* 5 */     { 103, 103,   5, 103, 103,   6,   6, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103 },
     /* 6 */     { 502, 502,   8, 502, 502, 502, 502,   7,   7, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502 },
     /* 7 */     { 503, 503,   8, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503 },
     /* 8 */     { 104, 104,   8, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104 },
     /* 9 */     {  10,  10,  10,  10,  10,  10,  10,  10,  10, 504,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10 },
    /* 10 */     { 505, 505, 505, 505, 105, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505 },
    /* 11 */     {  11, 11,   11,  11,  11,  11,  11,  11,  11,  11, 106,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11 },
    /* 12 */     {  12, 12,   12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12, 107,  12 },
    /* 13 */     { 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 114, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113 },
    /* 14 */     { 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 116, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115 },
    /* 15 */     { 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 118, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117 },
    /* 16 */     { 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 120, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119 },
    /* 17 */     { 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 121, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506 },
    /* 18 */     { 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 122, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507 },
                };
int cTokens = 0, cErrores = 0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}


/* ---------- buscar y abrir el archivo ---------- */
void MainWindow::on_btnAbrir_clicked(){
    QString texto;
    /* Se muestra un cuadro de dialogo para buscar el archivo a analizar */
    QFile archivo(QFileDialog::getOpenFileName(this,
                                               tr("Abrir Archivo"), "", tr("ISC Files (*.isc)")));
    archivo.open(QIODevice::ReadOnly | QIODevice::Text);

    /* Se carga el contenido del archivo y se muestra en un cuadro */
    QTextStream stream(&archivo);
    texto = stream.readAll();
    ui->textoAnalizar->appendPlainText(texto);
}


/* ---------- guardar el archivo ---------- */
void MainWindow::on_btnGuardar_clicked(){
    QString archivo = QFileDialog::getSaveFileName(this,
            tr("Guardar como..."), "",
            tr("ISC Files (*.isc)"));
    if (archivo.isEmpty())
            return;
        else {
            QFile file(archivo);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("No se puede abrir este tipo de archivo"),
                    file.errorString());
                return;
            }
    }
    QFile file(archivo);
    if ( file.open(QIODevice::ReadWrite) ){
        QTextStream stream( &file );
        stream << ui->textoAnalizar->toPlainText()<< endl;
    }

}

/* ---------- botón analizar ---------- */
void MainWindow::on_btnAnalizar_clicked(){
    /*analizar(ui->archivo->toPlainText());
    ui->tokens->setText(_tokens);
    ui->errores->setText(_errores);*/

    /* Encabezado de las tablas */
    ui->tablaTokens->setColumnCount(2);
    QStringList t;
    t << "Token" << "Descripción";
    ui->tablaTokens->setHorizontalHeaderLabels(t);
    ui->tablaTokens->setColumnWidth(0, 100);
    ui->tablaTokens->setColumnWidth(1, 230);

    ui->tablaErrores->setColumnCount(2);
    QStringList e;
    e << "Error" << "Descripción";
    ui->tablaErrores->setHorizontalHeaderLabels(e);
    ui->tablaErrores->setColumnWidth(0, 100);
    ui->tablaErrores->setColumnWidth(1, 230);

    /* Llenado de las tablas */
    for(int i=0; i < cTokens; i++){
        ui->tablaTokens->insertRow(ui->tablaTokens->rowCount());
        ui->tablaTokens->setItem(ui->tablaTokens->rowCount()-1, 0, new QTableWidgetItem("Token"));
        ui->tablaTokens->setItem(ui->tablaTokens->rowCount()-1, 1, new QTableWidgetItem("Descripción"));
    }

    for(int i=0; i < cErrores; i++){
        ui->tablaErrores->insertRow(ui->tablaErrores->rowCount());
        ui->tablaErrores->setItem(ui->tablaErrores->rowCount()-1, 0, new QTableWidgetItem("Error"));
        ui->tablaErrores->setItem(ui->tablaErrores->rowCount()-1, 1, new QTableWidgetItem("Descripción"));
    }
}

/* ---------- relaciona ---------- */
int Relaciona(char c){
    /* Minúsculas, Mayúsculas y Digitos */
    if(c >= 48 && c <= 57){
        return 2;
    }
    if(c >= 65 && c <= 90){
        return 1;
    }
    if(c >= 97 && c <= 122){
        return 0;
    }
    /* Otras carácteres */
    switch(c){
        case '_': return 3;
        case '.': return 4;
        case 'E': return 5;
        case 'e': return 6;
        case '+': return 7;
        case '-': return 8;
        case '\'': return 9;
        case '\"': return 10;
        case '#': return 11;
        case '*': return 12;
        case '/': return 13;
        case '%': return 14;
        case '&': return 15;
        case '|': return 16;
        case '=': return 17;
        case '>': return 18;
        case '<': return 19;
        case '!': return 20;
        case ':': return 21;
        //case ',': return 22;
        case ';': return 23;
        case '(': return 24;
        case ')': return 25;
        case '[': return 26;
        case ']': return 27;
        case 32: return 29;
        case '\n': return 30;
        case '\t': return 31;
        default: return 28;
    }
}

/* ---------- tokens ---------- */
QString Tokens;
QString textoA;
QString texto;
QList<QString> listaDescripcionTokens;
QList<QString> listaTokens;
void Token(int e){
    switch(e){
        case 100:
            listaDescripcionTokens << "Palabra reservada";
            break;
        case 101:
            //Tokens+=textoA+" Identificador\n";
            listaDescripcionTokens << "Identificador";
            break;
        case 102:
            listaDescripcionTokens << "Constante Entera";
            break;
        case 103:
            listaDescripcionTokens << "Constante Real";
            break;
        case 104:
            listaDescripcionTokens << "Constante Notación Científica";
            break;
        case 105:
            listaDescripcionTokens << "Constante Caracter";
            break;
        case 106:
            listaDescripcionTokens << "Constante String";
            break;
        case 107:
            listaDescripcionTokens << "Comentario";
            break;
        case 108:
            listaDescripcionTokens << "Operador Suma";
            break;
        case 109:
            listaDescripcionTokens << "Operador Menos";
            break;
        case 110:
            listaDescripcionTokens << "Operador Multiplicación";
            break;
        case 111:
            listaDescripcionTokens << "Operador División";
            break;
        case 112:
            listaDescripcionTokens << "Operador Módulo";
            break;
        case 113:
            listaDescripcionTokens << "Operador Igual";
            break;
        case 114:
            listaDescripcionTokens << "Operador Asignación";
            break;
        case 115:
            listaDescripcionTokens << "Operador Negación";
            break;
        case 116:
            listaDescripcionTokens << "Operador Diferente";
            break;
        case 117:
            listaDescripcionTokens << "Operador Menor";
            break;
        case 118:
            listaDescripcionTokens << "Operador Menor Igual";
            break;
        case 119:
            listaDescripcionTokens << "Operador Mayor";
            break;
        case 120:
            listaDescripcionTokens << "Operador Mayor Igual";
            break;
        case 121:
            listaDescripcionTokens << "Operador AND";
            break;
        case 122:
            listaDescripcionTokens << "Operador OR";
            break;
        case 123:
            listaDescripcionTokens << "Signo Punto y Coma";
            break;
        case 124:
            listaDescripcionTokens << "Signo Punto";
            break;
        case 125:
            listaDescripcionTokens << "Signo Dos Puntos";
            break;
        case 126:
            listaDescripcionTokens << "Parentesis que Abre";
            break;
        case 127:
            listaDescripcionTokens << "Parentesis que Cierra";
            break;
        case 128:
            listaDescripcionTokens << "Corchete que Abre";
            break;
        case 129:
            listaDescripcionTokens << "Corchete que Cierra";
            break;
        /* Palabras reservadas */
        case 132:
            listaDescripcionTokens << "Palabra Reservada 1";
            break;
        case 133:
            listaDescripcionTokens << "Palabra Reservada 2";
            break;
        case 134:
            listaDescripcionTokens << "Palabra Reservada 3";
            break;
        case 135:
            listaDescripcionTokens << "Palabra Reservada 4";
            break;
        case 136:
            listaDescripcionTokens << "Palabra Reservada 5";
            break;
        case 137:
            listaDescripcionTokens << "Palabra Reservada 6";
            break;
        case 138:
            listaDescripcionTokens << "Palabra Reservada 7";
            break;
        case 139:
            listaDescripcionTokens << "Palabra Reservada 8";
            break;
        case 140:
            listaDescripcionTokens << "Palabra Reservada 9";
            break;
        case 141:
            listaDescripcionTokens << "Palabra Reservada 10";
            break;
        case 142:
            listaDescripcionTokens << "Palabra Reservada 11";
            break;
        case 143:
            listaDescripcionTokens << "Palabra Reservada 12";
            break;
        case 144:
            listaDescripcionTokens << "Palabra Reservada 13";
            break;
        case 145:
            listaDescripcionTokens << "Palabra Reservada 14";
            break;
        case 146:
            listaDescripcionTokens << "Palabra Reservada 15";
            break;
        case 147:
            listaDescripcionTokens << "Palabra Reservada 16";
            break;
        case 148:
            listaDescripcionTokens << "Palabra Reservada 17";
            break;
        case 149:
            listaDescripcionTokens << "Palabra Reservada 18";
            break;
        case 150:
            listaDescripcionTokens << "Palabra Reservada 19";
            break;
        case 151:
            listaDescripcionTokens << "Palabra Reservada 20";
            break;
        case 152:
            listaDescripcionTokens << "Palabra Reservada 21";
            break;
        }

}

/* ---------- errores ---------- */
QString errores;
QList<QString> listaDescripcionErrores;
QList<QString> listaErrores;
void Errores(int e){
    switch(e){
        case 500:
            listaDescripcionErrores << "Error 500: El simbolo no forma parte del lenguaje";
            break;
        case 501:
            listaDescripcionErrores << "Error 501: Se esperaba digito después de \'.\'";
            break;
        case 502:
            listaDescripcionErrores << "Error 502: Se esperaba digito después de \'E\', \'e\'";
            break;
        case 503:
            listaDescripcionErrores << "Error 503: Se esperaba digito después de +/-";
            break;
        case 504:
            listaDescripcionErrores << "Error 504: Se esperaba carácter";
            break;
        case 505:
            listaDescripcionErrores << "Error 505: Faltó una \'";
            break;
        case 506:
            listaDescripcionErrores << "Error 506: Se esperaba la comparación AND";
            break;
        case 507:
            listaDescripcionErrores << "Error 507: Se esperaba la comparación OR";
            break;
    }
}


/* ---------- método analiza ---------- */
