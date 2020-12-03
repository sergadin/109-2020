#include <iostream>
#include "list.h"
#include "queue.h"

int main(void)
{
	queue <int> Q;
	Q.add_item(1);
	Q.add_item(2);
	Q.add_item(3);
	Q.del_item();
	std::cout << Q << "\n";
	std::cout << (Q == Q) << "\n";
	queue <int> QQ;
	QQ.add_item(1);
	QQ.add_item(2);
	QQ.add_item(3);
	Q = QQ;
	std::cout << Q << "\n";
	return 0;
}
