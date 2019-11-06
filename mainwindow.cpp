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
int cT = 1, cE = 1;

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
        ui->Token->setReadOnly(true);
        ui->Error->setReadOnly(true);
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
    switch(e){
        case 100:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Palabra Reservada\n";
            cT++;
            break;
        case 101:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t -> Identificador\n";
            cT++;
            break;
        case 102:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Constante Entera\n";
            cT++;
            break;
        case 103:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Constante Decimal\n";
            cT++;
            break;
        case 104:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t -> Cons. Notación Científica\n";
            cT++;
            break;
        case 105:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Constante Caracter\n";
            cT++;
            break;
        case 106:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Constante String\n";
            cT++;
            break;
        case 107:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Comentario\n";
            cT++;
            break;
        case 108:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Mas\n";
            cT++;
            break;
        case 109:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Menos\n";
            cT++;
            break;
        case 110:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Multiplicación\n";
            cT++;
            break;
        case 111:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador División\n";
            cT++;
            break;
        case 112:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Módulo\n";
            cT++;
            break;
        case 113:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Igual\n";
            cT++;
            break;
        case 114:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Asignación\n";
            cT++;
            break;
        case 115:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador NOT\n";
            cT++;
            break;
        case 116:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Diferente\n";
            cT++;
            break;
        case 117:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Menor\n";
            cT++;
            break;
        case 118:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Menor Igual\n";
            cT++;
            break;
        case 119:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Mayor\n";
            cT++;
            break;
        case 120:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador Mayor Igual\n";
            cT++;
            break;
        case 121:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador AND\n";
            cT++;
            break;
        case 122:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Operador OR\n";
            cT++;
            break;
        case 123:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Punto y Coma\n";
            cT++;
            break;
        case 124:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Punto\n";
            cT++;
            break;
        case 125:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Dos Puntos\n";
            cT++;
            break;
        case 126:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Parentesis que Abre\n";
            cT++;
            break;
        case 127:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Parentesis que Cierra\n";
            cT++;
            break;
        case 128:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Corchete que Abre\n";
            cT++;
            break;
        case 129:
            Tokens += temp + "\t -> " + textoA.trimmed() + "\t\t -> Corchete que Cierra\n";
            cT++;
            break;
        /*
        case 132:
            Tokens+=textoA+" Palabra reservada end\n";
            break;
        case 133:
            Tokens+=textoA+" Palabra reservada begin\n";
            break;
        case 134:
            Tokens+=textoA+" Palabra reservada class\n";
            break;
        case 135:
            Tokens+=textoA+" Palabra reservada import\n";
            break;
        case 136:
            Tokens+=textoA+" Palabra reservada def\n";
            break;
        case 137:
            Tokens+=textoA+" Palabra reservada as\n";
            break;
        case 138:
            Tokens+=textoA+" Palabra reservada integer\n";
            break;
        case 139:
            Tokens+=textoA+" Palabra reservada float\n";
            break;
        case 140:
            Tokens+=textoA+" Palabra reservada char\n";
            break;
        case 141:
            Tokens+=textoA+" Palabra reservada string\n";
            break;
        case 142:
            Tokens+=textoA+" Palabra reservada boolean\n";
            break;
        case 143:
            Tokens+=textoA+" Palabra reservada if\n";
            break;
        case 144:
            Tokens+=textoA+" Palabra reservada endif\n";
            break;
        case 145:
            Tokens+=textoA+" Palabra reservada else";
            break;
        case 146:
            Tokens+=textoA+" Palabra reservada endwhile\n";
            break;
        case 147:
            Tokens+=textoA+" Palabra reservada while\n";
            break;
        case 148:
            Tokens+=textoA+" Palabra reservada endfor\n";
            break;
        case 149:
            Tokens+=textoA+" Palabra reservada for\n";
            break;
        case 150:
            Tokens+=textoA+" Palabra reservada enter\n";
            break;
        case 151:
            Tokens+=textoA+" Palabra reservada write\n";
            break;
        case 152:
            Tokens+=textoA+" Palabra reservada read\n";
            break;*/
    }

}

QString errores;
void Errores(int e){
    temp = QString::number(cE);
    switch(e){
        case 500:
            errores += temp + "\t -> " + textoA.trimmed() + "\t -> Error 500: No corresponde al lenguaje\n";
            cE++;
            break;
        case 501:
            errores += temp + "\t -> " + textoA.trimmed() + "\t -> Error 501: Se esperaba digito despues de \".\"\n";
            cE++;
            break;
        case 502:
            errores += temp + "\t -> " + textoA.trimmed() + "\t -> Error 502: Se esperaba digito despues de \"E\", \"e\"\n";
            cE++;
            break;
        case 503:
            errores += temp + "\t -> " + textoA.trimmed() + "\t -> Error 503: Se esperaba digito despues de \"+\", \"-\"\n";
            cE++;
            break;
        case 504:
            errores += temp + "\t -> " + textoA.trimmed() + "\t -> Error 504: Caracter mal formado\n";
            cE++;
            break;
        case 505:
            errores += temp + "\t -> " + textoA.trimmed() + "\t -> Error 505: Caracter mal formado\n";
            cE++;
            break;
        case 506:
            errores += temp + "\t -> " + textoA.trimmed() + "\t -> Error 506: Operador AND mal formado\n";
            cE++;
            break;
        case 507:
            errores += temp + "\t -> " + textoA.trimmed() + "\t -> Error 507: Operador OR mal formado\n";
            cE++;
            break;
    }

}

/* Método para verificar que se trata de una palabra reservada */
/*int evaluaPalabraReservada(){
    int conta = 0;
    std::string cadenaStd = textoA.toStdString();
    for(int i = 0; i < textoA.length(); i++){
        char car = cadenaStd[i];
        if(car == '\n' || car == '\t' || car == 32)
            conta++;
    }
    QString temp = textoA.mid(conta, textoA.length());

    if(textoA=="import" || temp=="import"){
        return 135;
    }
    if(textoA=="class" || temp=="class"){
        return 134;
    }
    if(textoA=="begin" || temp=="begin"){
        return 133;
    }
    if(textoA=="end" || temp=="end"){
        return 132;
    }
    if(textoA=="def" || temp=="def"){
        return 136;
    }
    if(textoA=="as" || temp=="as"){
        return 137;
    }
    if(textoA=="integer" || temp=="integer"){
        return 138;
    }
    if(textoA=="float" || temp=="float"){
        return 139;
    }
    if(textoA=="char" || temp=="char"){
        return 140;
    }
    if(textoA=="string" || temp=="string"){
        return 141;
    }
    if(textoA=="boolean" || temp=="boolean"){
        return 142;
    }
    if(textoA=="if" || temp=="if"){
        return 143;
    }
    if(textoA=="endif" || temp=="endif"){
        return 144;
    }
    if(textoA=="else" || temp=="else"){
        return 145;
    }
    if(textoA=="endwhile" || temp=="endwhile"){
        return 146;
    }
    if(textoA=="while" || temp=="while"){
        return 147;
    }
    if(textoA=="endfor" || temp=="endfor"){
        return 148;
    }
    if(textoA=="for" || temp=="for"){
        return 149;
    }
    if(textoA=="enter" || temp=="enter"){
        return 150;
    }
    if(textoA=="write" || temp=="write"){
        return 151;
    }
    if(textoA=="read" || temp=="read"){
        return 152;
    }
    if((textoA=="principal" || temp=="principal")  ||
       (textoA=="elseif" || temp=="elseif")  ||
       (textoA=="do" || temp=="do") ||

       (textoA=="function" || temp=="function") ||
       (textoA=="endfunction" || temp=="endfunction") || (textoA=="null" || temp=="null") ||
       (textoA=="include" || temp=="include")){
        return 100;
    }
    return 101;
}*/

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

        if(edo < 100 || edo >= 500)
            textoA.append(car);

        if(edo == 103 && (car == 'e' || car == 'E')){
            if(car == 'e')
                textoA.append('e');
            if(car == 'E')
                textoA.append('E');
            edo = 6;
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

        //if(edo==100)
            //edo=evaluaPR();

        if(edo==106 && car=='"'){
            textoA.append(car);
            edo=106;
        }

        car=cadenaStd[numero];

        numero++;
        cout<<edo<<endl;
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
    Tokens = "";
    errores = "";
    cT = 0;
    cE = 0;
    ui->Token->setPlainText("");
    ui->Error->setPlainText("");
    texto=ui->textoAnalizar->toPlainText();
    while(texto!="")
        Analiza(texto);

    ui->Token->appendPlainText(Tokens);
    ui->Error->appendPlainText(errores);
    //std::cout << texto.toUtf8().constData() << std::endl;

}

/* ABRIR EL ARCHIVO */
void MainWindow::on_pushButton_2_clicked(){
   QString ruta=QFileDialog::getOpenFileName(
                this,tr("Abrir archivo"),"","ISC Files (*.isc)");
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

/* LIMPIAR LOS CUADROS */
void MainWindow::on_pushButton_3_clicked(){
    ui->textoAnalizar->setPlainText("");
    ui->Token->setPlainText("");
    ui->Error->setPlainText("");
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
