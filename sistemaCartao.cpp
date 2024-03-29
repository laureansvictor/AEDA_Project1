//
// Created by Gabriel Rocco on 23/10/2019.
//

#include "sistemaCartao.h"

//-----------------------
sistemaCartao::sistemaCartao() {
};

void sistemaCartao::venderBilhete(Cliente *cliente, Bilhete &b, Evento *evento) {
    int lot;
    if (evento->getLotacao() < evento->getCapacidadeMaxima()) {
        cliente->addBilhete(b);
        lot = evento->getLotacao() + 1;
        evento->setLotacao(lot);
    } else
        cout << "Lotação máxima atingida" << endl;
    int i = 0;
    i = searchSalaEspetaculo(evento->getNome());
    salas[i].setLotacao(evento->getLotacao());
    i = searchEvento(evento->getNome());
    eventos[i].setLotacao(evento->getLotacao());

}

void sistemaCartao::createTicket(Cliente *cliente, Bilhete &b, Evento *ev) {
    float basePrice = 45.9;
    if (ev->getLotacao() <= (ev->getCapacidadeMaxima() * 0.20) &&
        ((!cliente->temCartao() && ev->isAderente()) || (cliente->temCartao() && !ev->isAderente())))
        b.setValor(basePrice);
    if (ev->getLotacao() <= (ev->getCapacidadeMaxima() * 0.60) &&
        ((!cliente->temCartao() && ev->isAderente()) || (cliente->temCartao() && !ev->isAderente()))) {
        basePrice += (basePrice * 0.20);
        b.setValor(basePrice);
    }
    if (ev->getLotacao() <= (ev->getCapacidadeMaxima() * 0.80) &&
        ((!cliente->temCartao() && ev->isAderente()) || (cliente->temCartao() && !ev->isAderente()))) {
        basePrice += (basePrice * 0.40);
        b.setValor(basePrice);
    }
    if (ev->getLotacao() <= (ev->getCapacidadeMaxima() * 0.90) &&
        ((!cliente->temCartao() && ev->isAderente()) || (cliente->temCartao() && !ev->isAderente()))) {
        basePrice += (basePrice * 0.50);
        b.setValor(basePrice);
    }
    if (ev->getLotacao() <= (ev->getCapacidadeMaxima() * 0.1) &&
        ((!cliente->temCartao() && ev->isAderente()) || (cliente->temCartao() && !ev->isAderente()))) {
        basePrice += (basePrice * 0.60);
        b.setValor(basePrice);
    } //Protótipo para se o cliente é silver ! :)
    if((ev->getLotacao() <= (ev->getCapacidadeMaxima()*0.50)) && cliente->getIdade() >= 65 && cliente->temCartao() == true ){
        basePrice = 0;
        b.setValor(basePrice);
    }
    if (cliente->temCartao() && ev->isAderente() && cliente->getIdade() < 65) {
        basePrice -= (basePrice * 0.25);
        b.setValor(basePrice);
    }
}


void sistemaCartao::addSalaEspetaculo() {
    SalaEspetaculo newSala;
    string handler;
    cout << "Nome: ";
    getline(cin, handler);
    newSala.setNome(handler);
    newSala.setCapacidadeMaxima(readInteger("capacidade: "));
    newSala.setLotacao(0);
    cin.clear();
    cout << "\n *No formato Rua / Nº Porta / Freguesia / Código-Postal / Distrito* \nEndereço: " << endl;
    getline(cin, handler);
    Address endereco(handler);
    newSala.setEndereco(endereco);
    newSala.setAderente(readInteger("0 pra falso e 1 para verdadeiro \n aderente: "));
    newSala.setId(salas[salas.size()-1].getId()+1);
    salas.push_back(newSala);
}

void sistemaCartao::readSalaEspetaculo() {
    if (salas.size() == NULL) {
        cout << "Não há salas de espetáculo!\n";
    } else {
        for (auto it = this->salas.begin(); it != this->salas.end(); it++) {
            cout << (*it) << "\n";
        }
    }
}

void sistemaCartao::readSala() {
    if (salas.size() == NULL) {
        cout << "Não há salas de espetáculo!\n";
    } else {
        string sala;
        cout << "\nDIGITE O NOME DA SALA: \n";
        getline(cin, sala);
        int idx = searchSalaEspetaculo(sala);
        if (idx != -1) {
            cout << salas[idx];
        }
    }
}

void sistemaCartao::deleteSalaEspetaculo() {
    if (salas.size() == 0) {
        cout << "Não há salas de espetáculo!\n";
    } else {
        string name;
        cout << "Nome da sala para remover: ";
        getline(cin, name);
        for (auto it = salas.begin(); it == salas.end(); it++) {
            if ((*it).getNome() == name) {
                cout << "Sala de espetáculo encontrada!" << endl;
                cout << salas.size();
                salas.erase(it);
            }
        }
        cout << "A sala ' " << name << "' foi removida com sucesso! \n";
    }
}

void sistemaCartao::updateSalaEspetaculo() {
    if (salas.size() == 0) {
        cout << "Não há salas de espetáculo para atualizar! " << endl;
    } else {
        string line, text;
        cout << "Nome da sala que deseja atualizar: ";
        getline(cin, text);
        vector<string> menu = {"Nome: ", "Capacidade: ", "Endereco: ", "Aderente: "};
        cout << endl;
        for (size_t i = 0; i < salas.size(); i++) {
            if (salas[i].getNome() == text) {
                int op = readOptions(menu);
                if (op == 1) {
                    cout << "Novo nome da sala: ";
                    getline(cin, line);
                    salas[i].setNome(line);
                }
                if (op == 2) {
                    salas[i].setCapacidadeMaxima(readInteger("Nova Capacidade: "));
                }

                if (op == 3) {
                    cout << "Novo Endereço: ";
                    getline(cin, line);
                    Address aux(line);
                    salas[i].setEndereco(aux);
                }
                if (op == 4) {
                    salas[i].setAderente(readInteger("Aderente: "));
                }
                if (op == 5) {
                    salas[i].setId(readInteger("Aderente: "));
                }
            }
        }
    }

    cout << "Sala de Espetaculo atualizada com sucesso! \n";
}

void sistemaCartao::addCliente() {
    Cliente newClient;
    Date thisYear;
    thisYear.actualDate();
    srand(time(NULL));
    string handler = to_string(thisYear.getYear()) + "00" + to_string(rand() % 9999);
    newClient.setN_cartao(handler);
    cin.clear();
    cout << endl << "--- Criando novo cliente ---\npor favor digite seu nome completo: ";
    getline(cin, handler);
    newClient.setNome(handler);

    handler = readString("\n dia/mes/ano\nData de Nascimento: ");
    Date nascimento;
    cin.clear();
    bool isDate = nascimento.verifyDate(handler); // verify if the input is actualy a date
    while (isDate == false) {
        cin.clear();
        handler = readString("Data de Nascimento: ");
        isDate = nascimento.verifyDate(handler);
    }
    nascimento.setDateString(handler);
    newClient.setNascimento(nascimento);
    newClient.setContacto(readString("Contacto: "));
    cout << "\n *No formato Rua / Nº Porta / Freguesia / Código-Postal / Distrito* \nEndereço: " << endl;
    getline(cin, handler);
    Address end(handler);
    newClient.setMorada(end);

    int univ = readInteger("\nÉ universitário?\n1- SIM\n0-NÃO");
    if (univ == 1)
        newClient.setUniversitario(true);
    cin.clear();
    newClient.aderirCartao();
    newClient.printCliente();
    clientes.push_back(newClient);

    cout << "cliente novo adicionado!";
    cout << endl << "*************************************************************************" << endl;
    cout << "Parabéns " << newClient.getNome() << ", você acaba de completar seu cadastro com sucesso! " << endl;
    cout << "AVISO: O número de seu cartão é " << newClient.getN_cartao() << endl;
    cout << "Por favor compareca à qualquer Museu da Rede Portuguesa " << endl
         << "para a emissão do seu cartão, não se esqueca de " << endl;
    cout << "levar um documento com foto e Cartão de estudante caso necessário.";
    cout << endl << endl;
    cout << endl << "*************************************************************************" << endl << endl << endl;
}

void sistemaCartao::readClients() {
    if (clientes.size() == 0) {
        cout << "Não há clientes" << endl;
    } else {
        for (auto it = clientes.begin(); it != clientes.end(); it++) {
            (*it).printCliente();
        }
    }
}

void sistemaCartao::readClient() {
    if (clientes.size() == 0) {
        cout << "Não há clientes" << endl;
    } else {
        string card = readString("\nDIGITE O Nº DO CARTÃO CLIENTE: ");
        int idx = searchUser(card);
        if (idx != -1)
            clientes[idx].printCliente();
    }
}

void sistemaCartao::deleteCliente() {
    if (clientes.size() == 0) {
        cout << "NÃO HÁ CLIENTES!" << endl;
    } else {
        readClients();
        string card = readString("\nDIGITE O Nº DO CARTÃO CLIENTE: ");
        int idx = searchUser(card);
        if (idx != -1) {
            clientes.erase(clientes.begin() + idx);
            cout << "Cliente removido com sucesso!";
        }
    }
}


void sistemaCartao::updateCliente(string card) {
    if (clientes.size() == 0) {
        cout << "Não há clientes" << endl;
    } else {
        string line;
        vector<string> menu = {"Endereco: ", "Contacto: ", "Vínculo universitário: "};
        for (size_t i = 0; i < clientes.size(); i++) {
            if (clientes[i].getN_cartao() == card) {
                Date oldDate(clientes[i].getCartao().getDataAcquisition());
                int op = readOptions(menu);
                if (op == 1) {

                    cout << "Novo Endereço: ";
                    getline(cin, line);
                    Address aux(line);
                    clientes[i].setMorada(aux);
                    clientes[i].aderirCartao();
                    CartaoAmigo *novo = const_cast<CartaoAmigo *>(&(clientes[i].getCartao()));
                    novo->setDataAcquisition(oldDate);
                    clientes[i].setCartao(novo);
                }
                if (op == 2) {
                    cout << "Novo contacto: ";
                    getline(cin, line);
                    clientes[i].setContacto(line);
                    clientes[i].aderirCartao();
                }
                if (op == 3) {
                    if (clientes[i].getUniversitario() == true) {
                        cout
                                << "Deseja alterar seu status de membro académico? \nAtualmente você tem um vínculo com uma universidade\n";
                        cout << "Valor atual da anuidade: " << clientes[i].getCartao().getAnuidade() << endl;
                        op = readInteger("\n1 = SIM \n2 = NÃO\n");
                        if (op == 1) {
                            clientes[i].setUniversitario(false);
                            clientes[i].aderirCartao();
                            CartaoAmigo *novo = const_cast<CartaoAmigo *>(&(clientes[i].getCartao()));
                            novo->setDataAcquisition(oldDate);
                            clientes[i].setCartao(novo);
                            cout << "Nova anuidade: " << clientes[i].getCartao().getAnuidade();
                        } else {
                            cout << "Sábia escolha!\n";
                        }
                    } else {
                        cout
                                << "Deseja alterar seu status de membro académico? \nAtualmente você nao possui um vínculo com uma universidade\n";
                        cout << "Valor atual da anuidade: " << clientes[i].getCartao().getAnuidade() << endl;
                        op = readInteger("\n1 = SIM \n2 = NÃO\n");
                        if (op == 1) {
                            clientes[i].setUniversitario(true);
                            clientes[i].aderirCartao();
                            CartaoAmigo *novo = const_cast<CartaoAmigo *>(&(clientes[i].getCartao()));
                            novo->setDataAcquisition(oldDate);
                            clientes[i].setCartao(novo);
                            cout << "Sábia escolha! Nova anuidade: " << clientes[i].getCartao().getAnuidade();
                        } else
                            cout << "Não desista! As portas da Academia estarão sempre abertas. \n";
                    }
                }
            }
        }
    }
}

void sistemaCartao::updateClienteAdm() {
    if (clientes.size() == 0) {
        cout << "Não há clientes" << endl;
    } else {
        readClients();
        string line;
        string card = readString("\nDIGITE O Nº DO CARTÃO CLIENTE: ");
        int idx = searchUser(card);
        if (idx != -1) {
            vector<string> menu = {"Nome", "Data de Nascimento", "Endereco", "Contacto", "Vínculo universitário"};
            if (clientes[idx].getN_cartao() == card) {
                Date oldDate(clientes[idx].getCartao().getDataAcquisition());
                int op = readOptions(menu);
                if (op == 1) {
                    cout << "Nome completo alterado:";
                    getline(cin, line);
                    clientes[idx].setNome(line);
                }
                if (op == 2) {
                    cout << "Nova Data de nascimento:";
                    getline(cin, line);
                    Date newBorn(line);
                    clientes[idx].setNascimento(newBorn);
                }
                if (op == 3) {
                    cout << "Novo Endereço: ";
                    getline(cin, line);
                    Address aux(line);
                    clientes[idx].setMorada(aux);
                    clientes[idx].aderirCartao();
                }
                if (op == 4) {
                    cout << "Novo contacto: ";
                    getline(cin, line);
                    clientes[idx].setContacto(line);
                    clientes[idx].aderirCartao();
                }
                if (op == 5) {
                    if (clientes[idx].getUniversitario() == true) {
                        cout << "Atualmente o cliente " << clientes[idx].getNome()
                             << "tem um vínculo com uma universidade\n";
                        cout << "Valor atual da anuidade: " << clientes[idx].getCartao().getAnuidade() << endl;
                        op = readInteger("\n1 = SIM \n2 = NÃO\n");
                        if (op == 1) {
                            clientes[idx].setUniversitario(false);
                            clientes[idx].aderirCartao();
                            cout << "Nova anuidade: " << clientes[idx].getCartao().getAnuidade();
                        }
                    } else {
                        cout << "Atualmente o cliente " << clientes[idx].getNome()
                             << "não tem um vínculo com uma universidade\n";
                        cout << "Valor atual da anuidade: " << clientes[idx].getCartao().getAnuidade() << endl;
                        op = readInteger("\n1 = SIM \n2 = NÃO\n");
                        if (op == 1) {
                            clientes[idx].setUniversitario(true);
                            clientes[idx].aderirCartao();
                            cout << "Nova anuidade: " << clientes[idx].getCartao().getAnuidade();
                        }
                    }
                }
                CartaoAmigo *novo = const_cast<CartaoAmigo *>(&(clientes[idx].getCartao()));
                novo->setDataAcquisition(oldDate);
                clientes[idx].setCartao(novo);
            }
        }
    }
}

void sistemaCartao::WriteAllClients() {
    //Apaga o arquivo do cliente
    deleteFileToRewrite("../clientes.txt");
    ofstream outClients("../clientes.txt");
    if (outClients.is_open()) {
        for (auto it = clientes.begin(); it != clientes.end(); it++) {
            outClients << (*it);
        }
        outClients.close();
    }
}

void sistemaCartao::WriteAllSalas() {
    //Apaga o arquivo do cliente
    deleteFileToRewrite("../salaEspetaculos.txt");
    ofstream outSalas("../salaEspetaculos.txt");
    ofstream outClients("../salaEspetaculos.txt");
    cout.clear();
    if (outClients.is_open()) {
        for (auto it = salas.begin(); it != salas.end(); it++) {
            outClients << (*it);
        }
        outClients.close();
    }
}

void sistemaCartao::WriteAllEventos() {
    //Apaga o arquivo do cliente
    deleteFileToRewrite("../eventos.txt");
    ofstream outEventos("../eventos.txt");
    if (outEventos.is_open()) {
        for (auto it = eventos.begin(); it != eventos.end(); it++) {
            outEventos << (*it).getNomeEvento() << endl << (*it).getNome() << (*it).getData() << endl;
        }
        outEventos.close();
    }
}


int sistemaCartao::searchUser(string card) {
    for (size_t i = 0; i < getClientes().size(); i++) {
        if (card == getClientes().at(i).getN_cartao()) {
            return i;
        }
    }
    if (card == "12345678")
        cout << "Olá admnistrator \n";
    else
        cout << "Cliente cujo nº do cartão é '" << card << "' não foi encontrado!\n";
    return -1;
}

int sistemaCartao::searchSalaEspetaculo(string nome) {
    for (size_t i = 0; i < salas.size(); i++) {
        if (nome == salas.at(i).getNome()) {
            return i;
        }
    }
    cout << "Não foi encontrada uma sala com o nome '" << nome << " '\n";
    return -1;
}

int sistemaCartao::searchEvento(string nome) {
    for (size_t i = 0; i < getEventos().size(); i++) {
        if (nome == getEventos().at(i).getNome()) {
            return i;
        }
    }
    return -1;
}

//Tela inicial quando o programa é aberto, aparece apenas uma vez.
void sistemaCartao::loadClients() {
    vector<string> lines;
    string newline;
    ifstream myfile("../clientes.txt");
    if (myfile.is_open()) {
        for (string line; getline(myfile, line);) {
            lines.push_back(line);
        }
        for (int i = 0; i < lines.size(); i++) {
            Cliente user;
            user.setN_cartao(lines[i]);
            i++;
            user.setNome(lines[i]);
            i++;
            Date tempNascimento;
            tempNascimento.setDateString(lines[i]);
            user.setNascimento(tempNascimento);
            i++;
            Date oldDate;
            oldDate.setDateString(lines[i]);
            i++;
            user.setContacto(lines[i]);
            i++;
            user.setMorada(lines[i]);
            i++;
            if (lines[i] == "1") {
                user.setUniversitario(true);
            } else {
                user.setUniversitario(false);
            }
            i++;
            user.aderirCartao();
            cout << user.getN_cartao() << endl;
            CartaoAmigo *novo = const_cast<CartaoAmigo *>(&(user.getCartao()));
            novo->setDataAcquisition(oldDate);
            user.setCartao(novo);
            setClientes(user);
        }
        myfile.close();
        cout << endl << "DADOS CLIENTES CARREGADOS COM SUCESSO" << endl << endl;
    } else {
        cout << endl << "PROBLEMA NO CARREGAMENTO DE BASE DE DADOS DE CLIENTES" << endl << endl;
    }
};


void sistemaCartao::loadSalaEspetaculos() {
    vector<string> lines;
    string newline;
    ifstream myfile("../salaEspetaculos.txt");
    if (myfile.is_open()) {
        for (string line; getline(myfile, line);) {
            lines.push_back(line);
        }
        for (int i = 0; i < lines.size(); i++) {
            SalaEspetaculo newSala;
            newSala.setNome(lines[i]);
            i++;
            istringstream cap(lines[i]);
            int capAux;
            cap >> capAux;
            newSala.setCapacidadeMaxima(capAux);
            i++;
            istringstream lot(lines[i]);
            int lotAux;
            lot >> lotAux;
            newSala.setLotacao(lotAux);
            i++;
            Address novoEnd(lines[i]);
            newSala.setEndereco(novoEnd);
            i++;
            istringstream id(lines[i]);
            int idAux;
            id >> idAux;
            newSala.setId(idAux);
            i++;
            if (lines[i] == "1") {
                newSala.setAderente(true);
            } else {
                newSala.setAderente(false);
            }
            this->salas.push_back(newSala);
        }
        myfile.close();
        cout << endl << "DADOS DE SALAS DE ESPETACULO CARREGADOS COM SUCESSO" << endl << endl;
    } else {
        cout << endl << "PROBLEMA NO CARREGAMENTO DE BASE DE DADOS DAS SALAS DE ESPETACULO" << endl << endl;
    }
}

void sistemaCartao::loadEventos() {
    vector<string> lines;
    string newline;
    ifstream myfile("../eventos.txt");
    int sala;
    if (myfile.is_open()) {
        for (string line; getline(myfile, line);) {
            lines.push_back(line);
        }
        for (int i = 0; i < lines.size(); i++) {
            sala = searchSalaEspetaculo(lines[i]);
            if (sala != -1) {
                i++;
                string eventName = lines[i];
                i++;
                Date eventDate;
                eventDate.setDateString(lines[i]);
                i++;
                Time eventTime;
                eventTime.setTimeString(lines[i]);
                Evento newEvent(getSalas()[sala].getNome(), getSalas()[sala].getCapacidadeMaxima(),
                                getSalas()[sala].getLotacao(), getSalas()[sala].getEndereco(), getSalas()[sala].getId(),
                                getSalas()[sala].isAderente(), eventName, eventDate,eventTime);
                eventos.push_back(newEvent);
            }
        }
        myfile.close();
        cout << endl << "DADOS DE EVENTOS CARREGADOS COM SUCESSO" << endl << endl;
    } else {
        cout << endl << "PROBLEMA NO CARREGAMENTO DE BASE DE DADOS DOS EVENTOS" << endl << endl;
    }
}

const vector<Cliente> &sistemaCartao::getClientes() const {
    return clientes;
}

void sistemaCartao::setClientes(const Cliente &cliente) {
    this->clientes.push_back(cliente);
}

const vector<Evento> &sistemaCartao::getEventos() const {
    return eventos;
}

void sistemaCartao::setEventos(const Evento &evento) {
    this->eventos.push_back(evento);
}

const vector<SalaEspetaculo> &sistemaCartao::getSalas() const {
    return salas;
}

void sistemaCartao::setSalas(SalaEspetaculo sala) {
    this->salas.push_back(sala);
}

const vector<Museum> &sistemaCartao::getMuseu() const {
    return museus;
}

void sistemaCartao::setMuseu(const Museum &museu) {
    this->museus.push_back(museu);
}

sistemaCartao::sistemaCartao(const vector<SalaEspetaculo> &salas) {
}

