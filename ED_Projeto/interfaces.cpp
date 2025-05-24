// ======================
// ARQUIVO: interfaces.cpp
// FUNCIONALIDADES:
//      Respons�vel por controlar a interface textual do sistema. Cont�m os menus e a l�gica de navega��o entre as telas
//      principais, incluindo: tela principal, telas de cadastro, listagem e emerg�ncia. Tamb�m cont�m os menus que
//      direcionam para as respectivas funcionalidades em outros m�dulos.
// ======================

#include <bits\stdc++.h>
#include "header/cadastros.h"
#include "header/interfaces.h"
#include "header/atendimentos.h"

using namespace std;

// Inicializa��o e declara��o de vari�veis reus�veis.
extern FilaAtendimento fila_ambulancia;
extern FilaAtendimento fila_bombeiro;
extern FilaAtendimento fila_policia;
extern int tempo_simulado;
string cpf_login;
string nome_login;


//  Limpa a tela
void limpar_tela()
{
    system("cls");
    return ;
}



// ----- TELAS ----- // ----- Interface da interface das telas


//  Interface da tela principal
void tela_principal()
{   
    setlocale(LC_ALL, "");
    int op;
    
    do{
        cout << "/* Simulador de Atendimentos de Emerg�ncias *\\ \n";
        cout << "(1) - Cadastrar\n";
        cout << "(2) - Listar\n";
        cout << "(3) - Atendimento\n";
        cout << "(4) - Sair\n";
        cout << "\n";
        cout << "Op��o: ";
        cin >> op;
        cin.ignore();

        menu_principal(op);
        limpar_tela();

    } while(op != 4);

    return ;
}


//  Interface da tela de cadastro
void tela_cadastro()
{
    setlocale(LC_ALL, "");
    int op;
    do{
        limpar_tela();

        cout << "/* Cadastrar *\\ \n";
        cout << "(1) - Cadastrar Cidad�os\n";
        cout << "(2) - Cadastrar Unidades de servi�os\n";
        cout << "(3) - Voltar\n";
        cout << "\n";
        cout << "Op��o: ";
    
        cin >> op;
        cin.ignore();

        menu_cadastro(op);
        limpar_tela();

    } while (op != 3);

    return ;
}


//  Interface da tela de listagem
void tela_listar()
{
    setlocale(LC_ALL, "");

    int op;
    do{
        limpar_tela();

        cout << "/* Listar *\\ \n";
        cout << "(1) - Listar Bairros\n";
        cout << "(2) - Listar Cidad�os\n";
        cout << "(3) - Listar Unidades de servi�o por bairros\n";
        cout << "(4) - Voltar\n";
        cout << "\n";
        cout << "Op��o: ";
    
        cin >> op;
        cin.ignore();

        menu_listar(op);
        limpar_tela();

    } while (op != 4);

    return ;
}


//  Interface da tela de atendimentos. Acesso somente a cidad�o cadastrado, via CPF.
void tela_atendimentos()
{
    setlocale(LC_ALL, "");

    limpar_tela();
    if(!login(&nome_login, &cpf_login)) return ; // Verifica o login

    int op;

    do
    {
        limpar_tela();
        cout << "/* Painel de Atendimentos */\n";
        cout << "Bem vindo, " << nome_login << "\n\n";
        cout << "Tempo atual simulado: " << tempo_simulado << "\n\n";
        cout << "(1) - Registrar nova ocorr�ncia\n";
        cout << "(2) - Visualizar fila de atendimentos\n";
        cout << "(3) - Visualizar hist�rico do cidad�o\n";
        cout << "(4) - Simular pr�xima unidade de tempo (1 atendimento)\n";
        cout << "(5) - Voltar\n";
        cout << "Entre com a op��o: ";
        cin >> op;
        cin.ignore();

        limpar_tela();
        
        menu_atendimentos(op);

    } while (op != 5);
    

    return ;
}



// ----- MENUS ----- // ----- Interface dos menus nas respectivas telas


//  Menu da tela principal
void menu_principal(int op)
{
    switch(op)
    {
        case 1:
            tela_cadastro();
        
        break;

        case 2:
            tela_listar();

        break;

        case 3:
            tela_atendimentos();

        break;

        default:
        break;
    }
    
    return ;
}


//  Menu da tela de cadastro
void menu_cadastro(int op)
{
    limpar_tela();
    switch(op)
    {
        case 1:
            cadastrar_cidadaos();

        break;

        case 2:
            cadastrar_unidades();

        break;

        default:
        break;
    }
    return ;
}


//  Menu da tela de listagem
void menu_listar(int op)
{
    limpar_tela();
    switch(op)
    {
        case 1:
            listar_bairros();
            system("pause");

        break;
        
        case 2:
            listar_cidadaos();
            system("pause");

        break;
        
        case 3:
        {
            string nome_bairro;
            cout << "Entre com o nome do bairro: ";
            getline(cin, nome_bairro);

            limpar_tela();  
            listar_unidades_por_bairros(nome_bairro);
            system("pause");
        break;
        }

        default:
        break;
    }
    return ;
}


// Menu da tela de atendimentos
// obs: observando essa fun��o d� para refatorar os cases em outras fun��es. N�o sei se � a melhor op��o para 
// legibilidade, as vezes menos � mais...
void menu_atendimentos(int op)
{
    switch(op)
    {
        case 1:
        {
            Ocorrencia *nova = criar_ocorrencia(tempo_simulado);
            if(nova->tipo_servico == "bombeiro")
            {
                enfileirar(&fila_bombeiro, nova);
            }
            else if(nova->tipo_servico == "ambulancia")
            {
                enfileirar(&fila_ambulancia, nova);
            }
            else if(nova->tipo_servico == "policia")
            {
                enfileirar(&fila_policia, nova);
            }
            else
            {
                cout << "Tipo de servi�o inv�lido! Ocorr�ncia n�o pode ser completada!\n";
                delete nova;
            }
            system("pause");
            break;
        }

        case 2:
        {
            listar_fila(&fila_bombeiro, "Bombeiros");
            listar_fila(&fila_ambulancia, "Ambul�ncia");
            listar_fila(&fila_policia, "Pol�cia");
            system("pause");
            break;
        }

        case 3:
            listar_historico(cpf_login);
            system("pause");
        break;

        case 4:
        {
            tempo_simulado++;
            cout << "/* Fila de ocorr�ncias *\\ \n\n";
            if(fila_bombeiro.inicio)
            {
                Ocorrencia *atendida = desenfileirar(&fila_bombeiro);
                cout << "[Bombeiro] Atendendo ocorr�ncia: " << atendida->descricao << "\n";
                delete(atendida);
            }

            if(fila_ambulancia.inicio)
            {
                Ocorrencia *atendida = desenfileirar(&fila_ambulancia);
                cout << "[Ambul�ncia] Atendendo ocorr�ncia: " << atendida->descricao << "\n";
                delete(atendida);
            }

            if(fila_policia.inicio)
            {
                Ocorrencia *atendida = desenfileirar(&fila_policia);
                cout << "[Pol�cia] Atendendo ocorr�ncia: " << atendida->descricao << "\n";
                delete(atendida);
            }
            system("pause");
            break;
        }

        default:
        break;
    }

    return ;
}


