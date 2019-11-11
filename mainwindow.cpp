#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QStack>

using namespace std;

static int edo;
int cT = 0, cE = 0;
QList<QString> tokenLeido;
QList<QString> descripcionToken;
QList<QString> errorLeido;
QList<QString> descripcionError;

/* --------------------------------------------------------------------------- FUNCIÓN DE TRANSICIÓN --------------------------------------------------------------------------- */
                /*   0   1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30  */
                /*   l    L   d    _    .    E    e    +    -    '    "    #    *    /    %    &    |    =    >    <    !    :    ;    (    )    [    ]   !=   \b   \n   \t  */
int M[19][31] = {
     /* 0 */     {   1,   2,   3, 500, 124, 500, 500, 108, 109,   9,  11,  12, 110, 111, 112,  17,  18,  13,  16,  15,  14, 125, 123, 126, 127, 128, 129, 500,   0,   0,   0 },
     /* 1 */     {   1,   2,   2,   2, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 },
     /* 2 */     {   2,   2,   2,   2, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101 },
     /* 3 */     { 102, 102,   3, 102,   4, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102 },
     /* 4 */     { 501, 501,   5, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501 },
     /* 5 */     { 103, 103,   5, 103, 103,   6,   6, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103 },
     /* 6 */     { 502, 502,   8, 502, 502, 502, 502,   7,   7, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502 },
     /* 7 */     { 503, 503,   8, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503 },
     /* 8 */     { 104, 104,   8, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104 },
     /* 9 */     {  10,  10,  10,  10,  10,  10,  10,  10,  10, 504,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10 },
    /* 10 */     { 505, 505, 505, 505, 105, 505, 505, 505, 505, 105, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505 },
    /* 11 */     {  11, 11,   11,  11,  11,  11,  11,  11,  11,  11, 106,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11 },
    /* 12 */     {  12, 12,   12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12, 107,  12 },
    /* 13 */     { 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 114, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113 },
    /* 14 */     { 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 116, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115 },
    /* 15 */     { 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 118, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117 },
    /* 16 */     { 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 120, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119 },
    /* 17 */     { 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 121, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506 },
    /* 18 */     { 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 122, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507 },
            };

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
        ui->setupUi(this);
        /*ui->Token->setReadOnly(true);
        ui->Error->setReadOnly(true);*/
}

MainWindow::~MainWindow(){
    delete ui;
}

int Relaciona(char c){
   int valor;
   if(c >= 97 && c <= 122)
       return 0;
   if(c >= 65 && c <= 90)
       return 1;
   if(c >= 48 && c <= 57)
       return 2;
    switch(c){
        case '_': valor = 3;
            break;
        case '.': valor = 4;
            break;
        case 'E': valor = 5;
            break;
        case 'e': valor = 6;
            break;
        case '+': valor = 7;
            break;
        case '-': valor = 8;
            break;
        case 39: valor = 9;
            break;
        case '"': valor = 10;
            break;
        case '#': valor = 11;
            break;
        case '*': valor = 12;
            break;
        case '/': valor = 13;
            break;
        case '%': valor = 14;
            break;
        case '&': valor = 15;
            break;
        case '|': valor = 16;
            break;
        case '=': valor = 17;
            break;
        case '>': valor = 18;
            break;
        case '<': valor = 19;
            break;
        case '!': valor = 20;
            break;
        case ':': valor = 21;
            break;
        case ';': valor = 22;
            break;
        case '(': valor = 23;
            break;
        case ')': valor = 24;
            break;
        case '[': valor = 25;
            break;
        case ']': valor = 26;
            break;
        case 32: valor = 28;
            break;
        case '\n': valor = 29;
            break;
        case '\t': valor = 30;
            break;
        default: valor = 27;
    }
    return valor;
}

QString Tokens;
QString textoA;
QString texto;
QString temp;
void Token(int e){
    temp = QString::number(cT);
    tokenLeido << textoA.trimmed();
    switch(e){
        case 100:
            //Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Palabra Reservada\n";
            textoA.trimmed();
            descripcionToken << "Palabra Reservada";
            cT++;
            break;
        case 101:
            //Tokens += temp + "\t -> " + textoA.trimmed() + "\t -> Identificador\n";
            textoA.trimmed();
            descripcionToken << "Identificador";
            cT++;
            break;
        case 102:
            textoA.trimmed();
            descripcionToken << "Constante Entera";
            cT++;
            break;
        case 103:
            textoA.trimmed();
            descripcionToken << "Constante Decimal";
            cT++;
            break;
        case 104:
            textoA.trimmed();
            descripcionToken << "Constante Notación Científica";
            cT++;
            break;
        case 105:
            textoA.trimmed();
            descripcionToken << "Constante Caracter";
            cT++;
            break;
        case 106:
            textoA.trimmed();
            descripcionToken << "Constante String";
            cT++;
            break;
        case 107:
            descripcionToken << "Comentario";
            textoA.trimmed();
            cT++;
            break;
        case 108:
            descripcionToken << "Operador Mas";
            textoA.trimmed();
            cT++;
            break;
        case 109:
            descripcionToken << "Operador Menos";
            textoA.trimmed();
            cT++;
            break;
        case 110:
            descripcionToken << "Operador Multiplicación";
            textoA.trimmed();
            cT++;
            break;
        case 111:
            descripcionToken << "Operador División";
            textoA.trimmed();
            cT++;
            break;
        case 112:
            descripcionToken << "Operador Módulo";
            textoA.trimmed();
            cT++;
            break;
        case 113:
            descripcionToken << "Operador Igual\n";
            textoA.trimmed();
            cT++;
            break;
        case 114:
            descripcionToken << "Operador Asignación";
            textoA.trimmed();
            cT++;
            break;
        case 115:
            descripcionToken << "Operador NOT";
            textoA.trimmed();
            cT++;
            break;
        case 116:
            descripcionToken << "Operador Diferente";
            textoA.trimmed();
            cT++;
            break;
        case 117:
            descripcionToken << "Operador Menor";
            textoA.trimmed();
            cT++;
            break;
        case 118:
            descripcionToken << "Operador Menor Igual";
            textoA.trimmed();
            cT++;
            break;
        case 119:
            descripcionToken << "Operador Mayor";
            textoA.trimmed();
            cT++;
            break;
        case 120:
            descripcionToken << "Operador Mayor Igual";
            textoA.trimmed();
            cT++;
            break;
        case 121:
            descripcionToken << "Operador AND";
            textoA.trimmed();
            cT++;
            break;
        case 122:
            descripcionToken << "Operador OR";
            textoA.trimmed();
            cT++;
            break;
        case 123:
            descripcionToken << "Punto y Coma";
            textoA.trimmed();
            cT++;
            break;
        case 124:
            descripcionToken << "Punto";
            textoA.trimmed();
            cT++;
            break;
        case 125:
            descripcionToken << "Dos Puntos";
            textoA.trimmed();
            cT++;
            break;
        case 126:
            descripcionToken << "Parentesis que Abre";
            textoA.trimmed();
            cT++;
            break;
        case 127:
            descripcionToken << "Parentesis que Cierra";
            textoA.trimmed();
            cT++;
            break;
        case 128:
            descripcionToken << "Corchete que Abre";
            textoA.trimmed();
            cT++;
            break;
        case 129:
            descripcionToken << "Corchete que Cierra";
            textoA.trimmed();
            cT++;
            break;
    }

}

QString errores;
void Errores(int e){
    temp = QString::number(cE);
    switch(e){
        case 500:
            descripcionError << "Error 500: No corresponde al lenguaje";
            errorLeido << textoA.trimmed();
            cE++;
            break;
        case 501:
            descripcionError << "Error 501: Se esperaba digito despues de \".\"";
            errorLeido << textoA.trimmed();
            cE++;
            break;
        case 502:
            descripcionError << "Error 502: Se esperaba digito despues de \"E\", \"e\"";
            errorLeido << textoA.trimmed();
            cE++;
            break;
        case 503:
            descripcionError << "Error 503: Se esperaba digito despues de \"+\", \"-\"";
            errorLeido << textoA.trimmed();
            cE++;
            break;
        case 504:
            descripcionError << "Error 504: Caracter mal formado, falto un caracter";
            errorLeido << textoA.trimmed();
            cE++;
            break;
        case 505:
            descripcionError << "Error 505: Caracter mal formado, falto una \'";
            errorLeido << textoA.trimmed();
            cE++;
            break;
        case 506:
            descripcionError << "Error 506: Operador AND mal formado";
            errorLeido << textoA.trimmed();
            cE++;
            break;
        case 507:
            descripcionError << "Error 507: Operador OR mal formado";
            errorLeido << textoA.trimmed();
            cE++;
            break;
    }

}

/* Método para verificar que se trata de una palabra reservada */
int evaluaPalabraReservada(){
    int conta = 0;
    std::string cadenaStd = textoA.toStdString();
    for(int i = 0; i < textoA.length(); i++){
        char car = cadenaStd[i];
        if(car == '\n' || car == '\t' || car == 32)
            conta++;
    }
    QString temp = textoA.mid(conta, textoA.length());
    if((textoA=="function" || temp=="function")  || (textoA=="if" || temp=="if")  ||
       (textoA=="else" || temp=="else") ||  (textoA=="for" || temp=="for") ||
       (textoA=="main" || temp=="main") || (textoA=="while" || temp=="while") ||
       (textoA=="endif" || temp=="endif")){
        return 100;
    }
    return 101;
}

int Analiza(QString cadena){
    std::string cadenaStd = cadena.toStdString();
    edo = 0;
    int col;
    char car=cadenaStd[0];
    textoA = "";

    int numero = 1;
    while(edo <= 31){
        col = Relaciona(car);
        edo = M[edo][col];
        if(edo==108)
            textoA.append('+');
        if(edo==109)
            textoA.append('-');
        if(edo==110)
            textoA.append('*');
        if(edo==124)
            textoA.append('.');
        if(edo==128)
            textoA.append('[');
        if(edo==129)
            textoA.append(']');
        if(edo==126)
            textoA.append('(');
        if(edo==127)
            textoA.append(')');
        if(edo==123)
            textoA.append(';');
        if(edo==125)
            textoA.append(':');
        if(edo==112)
            textoA.append('%');
        if(edo==121)
            textoA.append("&");
        if(edo==122)
            textoA.append("|");

        if(edo < 100 || edo >= 500)
            textoA.append(car);

        if(edo == 103 && (car == 'e' || car == 'E')){
            if(car == 'e')
                textoA.append('e');
            if(car == 'E')
                textoA.append('E');
            edo = 6;
        }


        if(edo==114 && car=='='){
            textoA.append('=');
            edo=114;
        }


        if(edo==120 && car=='='){
            textoA.append('=');
            edo=120;
        }

        if(edo==118 && car=='='){
            textoA.append('=');
            edo=118;
        }

        if(edo==116 && car=='='){
            textoA.append('=');
            edo=116;
        }

        if(edo==115 && car=='='){
            textoA.append('=');
            edo=116;
        }

        if(edo==113 && car=='='){
            textoA.append('=');
            edo=113;
        }

        if(edo==107 && car=='#'){
            textoA.append('#');
            edo=107;
        }

        if(edo==9 && car!=39){
            textoA.append(car);
            edo=10;
        }else if(edo==9 && car!=39){
            textoA.append(car);
            edo=105;
        }

        if(edo==105 && car==39){
            textoA.append(car);
            edo=105;
        }

        if(edo==100)
            edo=evaluaPalabraReservada();

        if(edo==106 && car=='"'){
            textoA.append(car);
            edo=106;
        }

        car=cadenaStd[numero];

        numero++;
    }
        if(textoA=="&&" || textoA.contains("&&")){
            edo = 121;
        }else if (textoA.contains("&")) {
            edo = 506;
        }
        if(textoA=="||" || textoA.contains("||")){
            edo = 122;
        }else if (textoA.contains("|")) {
            edo = 507;
        }

        int conta=0;
        std::string cadenaStd2 = textoA.toStdString();
        for(int i=0;i<textoA.length();i++){
            char car=cadenaStd[i];
            if(car==' ' || car=='\t' || car==32 )
                conta++;
        }
        int longitud=textoA.length();
        texto=texto.remove(0,longitud);
        if(conta!=0){
            textoA.remove(0,conta);
        }


        if(edo>=100 && edo<=199){
            Token(edo);
        }else{
            Errores(edo);
        }

    return edo;
}

/* ANALIZAR */
void MainWindow::on_pushButton_clicked(){
    //Tokens = "";
    //errores = "";
    cT = 0;
    cE = 0;

    texto=ui->textoAnalizar->toPlainText();
    while(texto!="")
        Analiza(texto);

    /* Tabla TOKENS */
    ui->tableTokens->setColumnCount(2);
    QStringList t;
    t << "Token" << "Descripción Token";
    ui->tableTokens->setHorizontalHeaderLabels(t);
    ui->tableTokens->setColumnWidth(0, 100);
    ui->tableTokens->setColumnWidth(1, 420);
    for(int c = 0; c < cT; c++){
        ui->tableTokens->insertRow(ui->tableTokens->rowCount());
        ui->tableTokens->setItem(ui->tableTokens->rowCount()-1, 0, new QTableWidgetItem(tokenLeido[c]));
        ui->tableTokens->setItem(ui->tableTokens->rowCount()-1, 1, new QTableWidgetItem(descripcionToken[c]));
    }

    /* Tabla Errores */
    ui->tableErrores->setColumnCount(2);
    QStringList e;
    e << "Error" << "Descripción Error";
    ui->tableErrores->setHorizontalHeaderLabels(e);
    ui->tableErrores->setColumnWidth(0, 100);
    ui->tableErrores->setColumnWidth(1, 420);
    for(int c = 0; c < cE; c++){
        ui->tableErrores->insertRow(ui->tableErrores->rowCount());
        ui->tableErrores->setItem(ui->tableErrores->rowCount()-1, 0, new QTableWidgetItem(errorLeido[c]));
        ui->tableErrores->setItem(ui->tableErrores->rowCount()-1, 1, new QTableWidgetItem(descripcionError[c]));
    }


    //ui->Token->appendPlainText(Tokens);
    //ui->Error->appendPlainText(errores);

}

/* ABRIR EL ARCHIVO */
void MainWindow::on_pushButton_2_clicked(){
   QString ruta=QFileDialog::getOpenFileName(
                this,tr("Abrir archivo"),"C:\\Users\\Duuvi\\Desktop\\Analizador","ISC Files (*.isc)");
    if(ruta!=""){
        QFile inputFile(ruta);
        if (inputFile.open(QIODevice::ReadOnly)){
            QTextStream in(&inputFile);
            while (!in.atEnd()){
                QString line = in.readLine();
                ui->textoAnalizar->appendPlainText(line);
            }
            inputFile.close();
        }
    }
}

/* GUARDAR EL ARCHIVO */
void MainWindow::on_pushButton_4_clicked(){
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Guardar como..."), "",
            tr("ISC Files (*.isc)"));
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Imposible realizar la operación"),
                    file.errorString());
                return;
            }
    }
    QFile file(fileName);
    if ( file.open(QIODevice::ReadWrite) ){
        QTextStream stream( &file );
        stream <<ui->textoAnalizar->toPlainText()<<endl;
    }

}

void MainWindow::on_pushButton_3_clicked(){
    close();
}

void MainWindow::on_cleanTables_clicked(){
    ui->tableTokens->clearContents();
    ui->tableTokens->model()->removeRows(0, ui->tableTokens->rowCount());
    ui->tableErrores->clearContents();
    ui->tableErrores->model()->removeRows(0, ui->tableErrores->rowCount());
    ui->textoAnalizar->setPlainText("");

    tokenLeido.clear();
    errorLeido.clear();
    descripcionError.clear();
    descripcionToken.clear();
}
