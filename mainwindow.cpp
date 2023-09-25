#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), n(0, 0, 0, 0, 0, 0, 0.0)
{
    ui->setupUi(this);
    n = Neurona(0, 0, 0, 0, 0, 0, 0.0);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(buscarPorNeurona()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(llenarTabla()));

    // Inicializar administrarNeuronas
    administrarNeuronas = administradora();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString valor1Str = ui->lineEdit->text();
    QString valor2Str = ui->lineEdit_2->text();
    QString valor3Str = ui->lineEdit_3->text();
    QString valor4Str = ui->lineEdit_4->text();
    QString valor5Str = ui->lineEdit_5->text();
    QString valor6Str = ui->lineEdit_6->text();
    QString valor7Str = ui->lineEdit_7->text();

    // Verificar si algún campo está vacío antes de continuar
    if (valor1Str.isEmpty() || valor2Str.isEmpty() || valor3Str.isEmpty() ||
        valor4Str.isEmpty() || valor5Str.isEmpty() || valor6Str.isEmpty() || valor7Str.isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, complete todos los campos.");
        return;
    }

    // Convertir valores a números
    int valor1 = valor1Str.toInt();
    float valor2 = valor2Str.toFloat();
    int valor3 = valor3Str.toInt();
    int valor4 = valor4Str.toInt();
    int valor5 = valor5Str.toInt();
    int valor6 = valor6Str.toInt();
    int valor7 = valor7Str.toInt();

    n.setID(valor1);
    n.setVolt(valor2);
    n.setPX(valor3);
    n.setPY(valor4);
    n.setRed(valor5);
    n.setGreen(valor7);
    n.setBlue(valor6);

    administrarNeuronas.agregarInicio(n);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}


void MainWindow::on_pushButton_3_clicked()
{
    QString valor1Str = ui->lineEdit->text();
    QString valor2Str = ui->lineEdit_2->text();
    QString valor3Str = ui->lineEdit_3->text();
    QString valor4Str = ui->lineEdit_4->text();
    QString valor5Str = ui->lineEdit_5->text();
    QString valor6Str = ui->lineEdit_6->text();
    QString valor7Str = ui->lineEdit_7->text();

    // Verificar si algún campo está vacío antes de continuar
    if (valor1Str.isEmpty() || valor2Str.isEmpty() || valor3Str.isEmpty() ||
        valor4Str.isEmpty() || valor5Str.isEmpty() || valor6Str.isEmpty() || valor7Str.isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, complete todos los campos.");
        return;
    }

    // Convertir valores a números
    int valor1 = valor1Str.toInt();
    float valor2 = valor2Str.toFloat();
    int valor3 = valor3Str.toInt();
    int valor4 = valor4Str.toInt();
    int valor5 = valor5Str.toInt();
    int valor6 = valor6Str.toInt();
    int valor7 = valor7Str.toInt();

    n.setID(valor1);
    n.setVolt(valor2);
    n.setPX(valor3);
    n.setPY(valor4);
    n.setRed(valor5);
    n.setGreen(valor7);
    n.setBlue(valor6);

    administrarNeuronas.agregarFinal(n);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}



void MainWindow::on_pushButton_2_clicked()
{
    QString contenido = QString::fromStdString(administrarNeuronas.mostrar());
    ui->plainTextEdit->setPlainText(contenido);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Abrir Archivo de Datos", "", "Archivos de Texto (*.txt);;Todos los Archivos (*.*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            while (!in.atEnd()) {
                QString linea = in.readLine();
                QStringList tokens = linea.split(":");

                if (tokens.size() == 2) {
                    QString etiqueta = tokens[0].trimmed();
                    QString valorStr = tokens[1].trimmed();
                    bool conversionOk = false;
                    float valorFloat = valorStr.toFloat(&conversionOk);

                    if (conversionOk) {
                        if (etiqueta == "ID") {
                            int id = static_cast<int>(valorFloat);
                            n.setID(id);
                        }
                        else if (etiqueta == "Posicion x") {
                            int posX= static_cast<int>(valorFloat);
                            n.setPX(posX);
                        }
                        else if (etiqueta == "Posicion y") {
                            int posY= static_cast<int>(valorFloat);
                            n.setPY(posY);
                        }
                        else if (etiqueta == "Red") {
                            int r = static_cast<int>(valorFloat);
                            n.setRed(r);
                        }
                        else if (etiqueta == "Green") {
                            int g = static_cast<int>(valorFloat);
                            n.setGreen(g);
                        }
                        else if (etiqueta == "Blue") {
                            int b = static_cast<int>(valorFloat);
                            n.setBlue(b);
                        }
                        else if (etiqueta == "Voltaje") {
                            int v = static_cast<int>(valorFloat);
                            n.setVolt(v);
                            administrarNeuronas.agregarFinal(n);
                        }
                    }
                }
            }
            file.close();
        } else {
            qDebug() << "Error al abrir el archivo:" << file.errorString();
        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Guardar Datos", "", "Archivos de Texto (*.txt);;Todos los Archivos (*.*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QString contenido =  QString::fromStdString(administrarNeuronas.mostrar());
            out << contenido;
            file.close();
        } else {
            qDebug() << "Error al abrir el archivo:" << file.errorString();
        }
    }
}

void MainWindow::llenarTabla(){
    // Limpiar la tabla antes de llenarla
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Obtener el número de neuronas en la lista administradora
    int neuronasCount = administrarNeuronas.numeroDeNeuronas();

    // Establecer el número de filas en la tabla
    ui->tableWidget->setRowCount(neuronasCount);

    // Recorrer las neuronas y agregar cada neurona a la tabla
    for (int i = 0; i < neuronasCount; i++) {
        Neurona* neurona = administrarNeuronas.obtenerNeuronaEnPosicion(i);

        // Configurar celdas de la fila con los valores de la neurona
        QTableWidgetItem *itemID = new QTableWidgetItem(QString::number(neurona->getID()));
        QTableWidgetItem *itemPosX = new QTableWidgetItem(QString::number(neurona->getPX()));
        QTableWidgetItem *itemPosY = new QTableWidgetItem(QString::number(neurona->getPY()));
        QTableWidgetItem *itemRed = new QTableWidgetItem(QString::number(neurona->getRed()));
        QTableWidgetItem *itemGreen = new QTableWidgetItem(QString::number(neurona->getGreen()));
        QTableWidgetItem *itemBlue = new QTableWidgetItem(QString::number(neurona->getBlue()));
        QTableWidgetItem *itemVoltaje = new QTableWidgetItem(QString::number(neurona->getaVolt()));

        ui->tableWidget->setItem(i, 0, itemID);
        ui->tableWidget->setItem(i, 1, itemPosX);
        ui->tableWidget->setItem(i, 2, itemPosY);
        ui->tableWidget->setItem(i, 3, itemRed);
        ui->tableWidget->setItem(i, 4, itemGreen);
        ui->tableWidget->setItem(i, 5, itemBlue);
        ui->tableWidget->setItem(i, 6, itemVoltaje);
    }
}

void MainWindow::buscarPorNeurona() {
    QString idBuscado = ui->lineEdit_8->text();
    // Convierte el ID buscado de QString a int
    int id = idBuscado.toInt();
    llenarTabla();

    // Recorre todas las filas de la tabla
    bool encontrado = false;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        qDebug() << "Dentro del bucle, fila:" << row;
        Neurona* neurona = administrarNeuronas.obtenerNeuronaEnPosicion(row);
        if (neurona && neurona->getID() == id) {
            // Si la neurona coincide con la búsqueda, muestra la fila
            ui->tableWidget->setRowHidden(row, false);
            encontrado = true;
            qDebug() << "ID encontrado en fila:" << row;
        } else {
            // Si no coincide, oculta la fila
            ui->tableWidget->setRowHidden(row, true);
        }
   }
    if(encontrado){
        qDebug () <<"a";
        QMessageBox::information(this, "ID no encontrado", "No se encontró una neurona con ese ID.");
    }
}




