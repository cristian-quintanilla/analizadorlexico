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
    /* 10 */     { 505, 505, 505, 505, 105, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505 },
    /* 11 */     {  11, 11,   11,  11,  11,  11,  11,  11,  11,  11, 106,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11 },
    /* 12 */     {  12, 12,   12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12, 107,  12 },
    /* 13 */     { 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 114, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113 },
    /* 14 */     { 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 116, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115 },
    /* 15 */     { 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 118, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117 },
    /* 16 */     { 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 120, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119 },
    /* 17 */     { 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 121, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506 },
    /* 18 */     { 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 122, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507 },
            };



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->Token->setReadOnly(true);
    ui->Error->setReadOnly(true);
}

MainWindow::~MainWindow(){
    delete ui;
}

/* ---------- relaciona ---------- */
int Relaciona(char c){
   if(c >= 48 && c <= 57){
       return 2;
   }
   if(c >= 65 && c <= 90){
       return 1;
   }
   if(c >= 97 && c <= 122){
       return 0;
   }

   switch(c){
        case '.': return 4;
        case '_': return 3;
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
        case ';': return 22;
        case '(': return 23;
        case ')': return 24;
        case '[': return 25;
        case ']': return 26;
        case ' ': return 28;
        case '\n': return 29;
        case '\t': return 30;

        default: return 27;
   }
}

int counterToken = 1;
QString Tokens;
QString textoLeido;
QString texto;

void Token(int e){
    switch(e){
        case 100:
            Tokens += QString(counterToken) + textoLeido + " -> Palabra reservada\n";
            counterToken++;
            break;
        case 101:
            Tokens += QString(counterToken) + textoLeido + " -> Identificador\n";
            counterToken++;
            break;
        case 102:
            Tokens += QString(counterToken) + textoLeido + " -> Constante Entera\n";
            counterToken++;
            break;
        case 103:
            Tokens += QString(counterToken) + textoLeido + " -> Constante Real\n";
            counterToken++;
            break;
        case 104:
            Tokens += QString(counterToken) + textoLeido + " -> Constante Notación C.\n";
            counterToken++;
            break;
        case 105:
            Tokens += QString(counterToken) + textoLeido + " -> Constante Caracter\n";
            counterToken++;
            break;
        case 106:
            Tokens += QString(counterToken) + textoLeido + " -> Constante String\n";
            counterToken++;
            break;
        case 107:
            Tokens += QString(counterToken) + textoLeido + " -> Comentario\n";
            counterToken++;
            break;
        case 108:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Mas\n";
            counterToken++;
            break;
        case 109:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Menos\n";
            counterToken++;
            break;
        case 110:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Multiplicación\n";
            counterToken++;
            break;
        case 111:
            Tokens += QString(counterToken) + textoLeido + " -> Operador División\n";
            counterToken++;
            break;
        case 112:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Módulo\n";
            counterToken++;
            break;
        case 113:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Igual\n";
            counterToken++;
            break;
        case 114:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Asignación\n";
            counterToken++;
            break;
        case 115:
            Tokens += QString(counterToken) + textoLeido + " -> Operador NOT\n";
            counterToken++;
            break;
        case 116:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Diferente\n";
            counterToken++;
            break;
        case 117:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Menor\n";
            counterToken++;
            break;
        case 118:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Menor Igual\n";
            counterToken++;
            break;
        case 119:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Mayor\n";
            counterToken++;
            break;
        case 120:
            Tokens += QString(counterToken) + textoLeido + " -> Operador Mayor Igual\n";
            counterToken++;
            break;
        case 121:
            Tokens += QString(counterToken) + textoLeido + " -> Operador AND\n";
            counterToken++;
            break;
        case 122:
            Tokens += QString(counterToken) + textoLeido + " -> Operador OR\n";
            counterToken++;
            break;
        case 123:
            Tokens += QString(counterToken) + textoLeido + " -> Punto y Coma\n";
            counterToken++;
            break;
        case 124:
            Tokens += QString(counterToken) + textoLeido + " -> Punto\n";
            counterToken++;
            break;
        case 125:
            Tokens += QString(counterToken) + textoLeido + " -> Dos Puntos\n";
            counterToken++;
            break;
        case 126:
            Tokens += QString(counterToken) + textoLeido + " -> Paréntesis que Abre\n";
            counterToken++;
            break;
        case 127:
            Tokens += QString(counterToken) + textoLeido + " -> Paréntesis que Cierra\n";
            counterToken++;
            break;
        case 128:
            Tokens += QString(counterToken) + textoLeido + " -> Corchete que Abre\n";
            counterToken++;
            break;
        case 129:
            Tokens += QString(counterToken) + textoLeido + " -> Corchete que Cierra\n";
            counterToken++;
            break;
    /*case 130:
        //cout<<"Es una coma"<<endl;
        Tokens+=textoA+" Es una coma\n";
        break;
    case 131:
        //cout<<#Es una libreria"<<endl;
        Tokens+=textoA+" Es una libreria\n";
        break;
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
        break;
    */
    }

}

int counterErrores = 1;
QString errores;

void Errores(int e){
    switch(e){
    case 500:
        errores += QString(counterErrores) + textoLeido + " -> Error 500: No forma parte del lenguaje\n";
        counterErrores++;
        break;
    case 501:
        errores += QString(counterErrores) + textoLeido + " -> Error 501: Se esperaba digito despues de \'.\'\n";
        counterErrores++;
        break;
    case 502:
        errores += QString(counterErrores) + textoLeido + " -> Error 502: Se esperaba digito despues de \'E\' o \'e\'\n";
        counterErrores++;
        break;
    case 503:
        errores += QString(counterErrores) + textoLeido + " -> Error 503: Se esperaba digito despues de \'+\' o \'-\'\n";
        counterErrores++;
        break;
    case 504:
        errores += QString(counterErrores) + textoLeido + " -> Error 504: Error de Caracter\n";
        counterErrores++;
        break;
    case 505:
        errores += QString(counterErrores) + textoLeido + " -> Error 505: Error de Caracter\n";
        counterErrores++;
        break;
    case 506:
        errores += QString(counterErrores) + textoLeido + " -> Error 506: Error Operador AND\n";
        counterErrores++;
        break;

    }

}


int Analiza(QString cadena){
    std::string cadenaStd = cadena.toStdString();
    edo=0;
    int col;
    char car=cadenaStd[0];
    textoLeido = "";
    int numero=1;
    while(edo<=32){
        col = Relaciona(car);
        edo = M[edo][col];
        if(edo == 108)
            textoLeido.append('+');
        if(edo == 109)
            textoLeido.append('-');
        if(edo == 110)
            textoLeido.append('*');
        if(edo == 124)
            textoLeido.append('.');
        if(edo == 128)
            textoLeido.append('[');
        if(edo == 129)
            textoLeido.append(']');
        if(edo == 126)
            textoLeido.append('(');
        if(edo == 127)
            textoLeido.append(')');
        if(edo == 123)
            textoLeido.append(';');
        if(edo == 125)
            textoLeido.append(':');
        if(edo == 112)
            textoLeido.append('%');

        if(edo<100 || edo>=500)
            textoLeido.append(car);

        if(edo == 104 && (car == 'e' || car == 'E')){
            if(car == 'e')
                textoLeido.append('e');
            if(car == 'E')
                textoLeido.append('E');
            edo = 7;
        }


        /*
        if(edo==119 && car=='='){
            textoLeido.append('=');
            edo=119;
        }

        if(edo==121 && car=='='){
            textoLeido.append('=');
            edo=121;
        }

        if(edo==116 && car=='='){
            textoA.append('=');
            edo=116;
        }

        if(edo==115 && car=='='){
            textoA.append('=');
            edo=116;
        }

        if(edo==117 && car=='='){
            textoA.append('=');
            edo=117;
        }



        if(edo==112 && car=='/'){
            textoA.append('/');
            edo=112;
        }

        if(edo==10 && car!=39){
            textoA.append(car);
            edo=11;
        }else if(edo==10 && car!=39){
            textoA.append(car);
            edo=105;
        }

        if(edo==105 && car==39){
            textoA.append(car);
            edo=105;
        }



        if(edo==100){
            edo=evaluaPR();
        }

        if(edo==22 && car=='l'){
            edo=22;
        }

        if(edo==22 && car=='y'){
            edo=22;
        }

        if(edo==22 && car=='e'){
            edo=131;
        }

        if(edo==101 && car=='.'){
            textoA.append('.');
            edo=22;
        }*/

        /*if(edo==509){
            QString texto1=textoA.mid(textoA.length()-4,textoA.length());
            QString texto2=textoA.mid(textoA.length()-5,textoA.length());
            //std::cout << texto1.toUtf8().constData() << std::endl;
            if(texto1.contains(".lye") || texto2.contains(".lyes")){
                edo=131;
            }
        }*/

        if(edo==106 && car=='"'){
            textoLeido.append(car);
            edo=106;
        }

        car=cadenaStd[numero];

        numero++;
        //cout<<edo<<endl;
    }

    /*if(textoA=="&&" || textoA.contains("&&")){
        edo=113;
    }else if (textoA.contains("&")) {
        edo=507;
    }
    if(textoA=="||" || textoA.contains("||")){
        edo=114;
    }else if (textoA.contains("|")) {
        edo=508;
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
    }*/



    return edo;
}


void MainWindow::on_pushButton_clicked(){
    Tokens = "";
    errores = "";
    ui->Token->setPlainText("");
    ui->Error->setPlainText("");
    Analiza(texto);
    ui->Token->appendPlainText(Tokens);
    ui->Error->appendPlainText(errores);
}

void MainWindow::on_pushButton_2_clicked(){
   QString ruta=QFileDialog::getOpenFileName(
                this,tr("Abrir archivo"), "", "ISC Files (*.isc)");
    if(ruta!=""){
    QFile inputFile(ruta);
    if (inputFile.open(QIODevice::ReadOnly)){
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          ui->textoAnalizar->appendPlainText(line);
       }
       inputFile.close();
    }


}

}

void MainWindow::on_pushButton_3_clicked(){
    ui->textoAnalizar->setPlainText("");
    ui->Token->setPlainText("");
    ui->Error->setPlainText("");
}

void MainWindow::on_pushButton_4_clicked(){
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Guardar como.."), "",
            tr("ISC Files (*.isc)"));
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }
    }
    QFile file(fileName);
    if ( file.open(QIODevice::ReadWrite) ){
        QTextStream stream( &file );
        stream <<ui->textoAnalizar->toPlainText()<< endl;
    }

}
