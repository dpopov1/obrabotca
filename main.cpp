#include <iostream>
#include "sglazivanie.h"
#include "sortirovka.h"

int main()
{
	points(',','.',0);
	viravnivanie(0);
	sglazivanie();
	points('.', ',',0);
	viravnivanie(1);
	points('.', ',', 1);
	system("pause");
}