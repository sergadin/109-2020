#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <list>
#include "S.h"
#include <fstream>
#include <vector>
#include <typeinfo>
#include "unistd.h"


int main(int argc, char *argv[])
{
    int as, ms;
	DataBase UserBase;
	setlocale(LC_ALL, "Russian");
 
    struct sockaddr_in server;
    char buf[1024]; /* буфер для приема сообщений от клиентов */

    as = socket(AF_INET, SOCK_STREAM, 0 ); /* Создаем сокет для работы по TCP/IP */

    /* Заполняем структуру адреса, на котором будет работать сервер */
    server.sin_family = AF_INET; /* IP */
    server.sin_addr.s_addr = INADDR_ANY; /* любой сетевой интерфейс */
    server.sin_port = htons(1234); /* порт */


    /* сопоставляем адрес с сокетом */
    bind(as, (struct sockaddr *) &server, sizeof(server));

    listen(as, 5); /* сокет as используется для приема соединений; 5 - длина очереди */
	
	
	cout << "Укажите имя файла, где лежит список продавцов и покупателей: " << endl;
    char nameS[40];
    cin.getline(nameS, 40);
	// ofstream out1(nameS, ios::app);
	cout << "Укажите имя файла, где хранятся сделки: " << endl;
    char nameM[40];
    cin.getline(nameM, 40);
	cout << "___Список доступных команд___" << endl;
	cout << "1. Добавить сделку" << endl;
	cout << "2. Распечатать список лиц, между которыми происходили сделки" << endl;
	cout << "3. Распечатать все сделки" << endl;
	cout << "4. Поиск и распечатывание сделок по имени продавца" << endl;
	cout << "5. Поиск и распечатывание сделок по имени покупателя" << endl;
	cout << "6. Удаление сделок по имени продавца" << endl;
	cout << "7. Удаление сделок по имени покупателя" << endl;
	cout << "8. Удаление сделок по имени покупателя и продавца" << endl;
	
    /* цикл обработки клиентов */
    while( 1 ) {
        ms = accept( as, 0, 0 ); /* выбираем первое соединение из очереди */
        bzero( buf, sizeof(buf)); /* обнуляем буфер сообщения */
        read(ms, buf, sizeof(buf)); /* читаем сообщение от клиента */
		
		if (buf[0] == '1') {//strcmp
			cout << "Пожалуйста, введите запрос в формате: Продавец  Покупатель  Сумма сделки  День сделки  Месяц  Год" << endl;
			string NewDeal;
			cin >> NewDeal;
			UserBase.AddDeal(NewDeal);	
		}	
		
        close( ms ); /* закрываем соединение с клиентом */
        printf("message is = %s\n", buf );
        if ( strcmp(buf, "quit") == 0 ) break;
    }
    close( as ); /* закрываем порт 1234; клиенты больше не могут подключаться */
    return 0;
}

//поиск продавца
//удалить что-нибудь по одинаковому условию

/*
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <list>
#include "S.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(){
	DataBase UserBase;
	setlocale(LC_ALL, "Russian");
 
    cout << "Укажите имя файла, где лежит список продавцов и покупателей: " << endl;
    char nameS[40];
    cin.getline(nameS, 40);
	// ofstream out1(nameS, ios::app);
	cout << "Укажите имя файла, где хранятся сделки: " << endl;
    char nameM[40];
    cin.getline(nameM, 40);
   // ofstream out2(nameM, ios::app);
	UserBase.GetNames(nameS, nameM);
	//UserBase.showNames();	
	//UserBase.RecordDeals(nameM);
	UserBase.showDeals();
	return 0;
}*/