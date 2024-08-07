#include "PrintManager.h"
#include "Player.h"
#include "ConsoleManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Graphics.h"
#include <iostream>




//==========================================�ؽ�Ʈ��==========================================
char _winMessage[20][40] =
{
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
{'9','0','8','0','0','0','8','0','8','0','8','0','0','0','8','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
{'9','0','8','0','8','0','8','0','8','0','8','8','0','0','8','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
{'9','0','8','0','8','0','8','0','8','0','8','0','8','0','8','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
{'9','0','8','0','8','0','8','0','8','0','8','0','0','8','8','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
{'9','0','0','8','0','8','0','0','8','0','8','0','0','0','8','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
{'9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'}
};
char _dieMessage[20][40] =
{
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9','9','9'},
{'9','9','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9','9','9'},
{'9','9','9','0','0','0','0','0','0','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','0','0','0','0','0','0','8','8','0','0','0','9','9','9'},
{'9','9','9','0','0','0','8','8','8','8','8','8','8','8','0','0','8','8','0','0','0','0','0','0','8','8','8','8','0','0','0','0','8','8','0','0','0','9','9','9'},
{'9','9','9','0','0','0','8','8','8','8','8','8','8','8','0','0','8','8','0','0','0','0','0','8','8','8','8','8','8','0','0','0','8','8','0','0','0','9','9','9'},
{'9','9','9','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','8','8','0','0','8','8','8','0','0','8','8','8','0','0','8','8','0','0','0','9','9','9'},
{'9','9','9','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','8','8','0','0','8','8','0','0','0','0','8','8','0','0','8','8','0','0','0','9','9','9'},
{'9','9','9','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','0','0','0','0','8','8','0','0','0','0','8','8','0','0','8','8','0','0','0','9','9','9'},
{'9','9','9','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','0','0','0','0','8','8','8','0','0','8','8','8','0','0','8','8','0','0','0','9','9','9'},
{'9','9','9','0','0','0','8','8','8','8','8','8','8','8','0','0','8','8','0','0','0','0','0','8','8','8','8','8','8','0','0','0','8','8','0','0','0','9','9','9'},
{'9','9','9','0','0','0','8','8','8','8','8','8','8','8','0','0','8','8','0','0','0','0','0','0','8','8','8','8','0','0','0','0','8','8','0','0','0','9','9','9'},
{'9','9','9','0','0','0','0','0','0','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','0','0','0','0','0','0','8','8','0','0','0','9','9','9'},
{'9','9','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'}
};
char _bbingMessage[9][30] =
{
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','2','0','2','0','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','2','0','2','0','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','2','2','2','2','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','2','0','2','0','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','2','2','2','2','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}

};
char _ddaDangMessage[9][30] =
{
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','c','c','c','c','c','0','0','c','c','c','c','c','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','c','0','c','0','0','0','0','c','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','c','0','c','0','0','0','0','c','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','c','0','c','0','0','0','0','c','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','c','c','c','c','c','0','0','c','c','c','c','c','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
};
char _callMessage[9][30] =
{
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
};
char _quarterMessage[9][30] =
{
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','7','7','7','7','0','0','7','7','7','7','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','7','0','0','7','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','7','7','7','7','0','0','7','7','7','7','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','7','0','0','7','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','7','0','0','7','7','7','7','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
};
char _halfMessage[9][30] =
{
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','6','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','6','6','6','6','6','0','0','6','6','6','6','6','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','6','6','6','0','0','0','0','6','0','6','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','6','0','6','0','0','0','0','6','0','6','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','6','6','6','0','0','0','6','6','6','6','6','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}

};
//==========================================�ؽ�Ʈ��==========================================

PrintManager& PrintManager::Instance()
{
	static PrintManager* PM = new PrintManager();
	return *PM;
}
void PrintManager::PrintGameTitle()
{
	ConsoleManager::Instance().ChangeConsoleSize(95, 24);
	cout << endl << endl << endl;
	ConsoleManager::Instance().GoToXY(0, 2);
	printf("\t\t#     #     #     #        #          ####        #    #  #####  \n");
	printf("\t\t#     #    # #    #        #         #    #       #    #  #    # \n");
	printf("\t\t#     #   #   #   #        #        #      #      #    #  #     #\n");
	printf("\t\t#     #  #     #  #        #        #      #      #    #  #    # \n");
	printf("\t\t#######  #######  #        #        #      #      #    #  #####  \n");
	printf("\t\t#     #  #     #  #        #        #      #      #    #  #      \n");
	printf("\t\t#     #  #     #  #        #        #      #      #    #  #      \n");
	printf("\t\t#     #  #     #  #        #         #    #       #    #  #      \n");
	printf("\t\t#     #  #     #  #######  #######    ####         ####   #      \n");
}
void PrintManager::GameInfoDraw()
{
	ConsoleManager::Instance().ChangeConsoleSize(200, 80);
	cout << endl << endl;
	printf("\t\t\t\t\t\t\t\t\t\t\t\t   [ ���۹� ]\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t        �̵� : W, A, S, D\n\n");
	printf("\t\t\t\t\t\t   Hallo Up�� 3�� ������ ��Ģ�� ������, �ҷ��� ī�� 2-3������ ������ ����� �� ���� ������ ����� �¸��ϴ� �����Դϴ�.\n\n");
	printf("\t\t\t\t\t\t   ���� ������ �÷��̾�� �� ���帶�� ī�� 2���� �ް�, ���� �� �ٽ� 1���� �߰��� �ް� �˴ϴ�.							   \n\n\n");
	printf("\t\t\t\t\t\t   �÷��̾�� �̵� �� �� 2���� ������ �ִ��� ���� ������ ������ �ϰ�,													 \n");
	printf("\t\t\t\t\t\t   ��� �÷��̾���� ������ �Ϸ��ϸ� ������ �е��� ��ο��� �����Ǹ�, ���� ���ΰ� �������ϴ�.								 \n\n");
	printf("\t\t\t\t\t\t   �� ���尡 ������ ��, 1�� �÷��̾�� '0'�� �Է��� �� ���带 ������ �� �ֽ��ϴ�. 								 \n\n");
	printf("\t\t\t\t\t\t   																													 \n");
	printf("\t\t\t\t\t\t   �÷��̾���� ����(Candy)�� ���øӴϷ� Ȱ���� �� �ְ�, �̴� �÷��̾��� �����͵� ����˴ϴ�.									\n");
	printf("\t\t\t\t\t\t   ������ ��� �� �������� ��� ���ӿ��� �й��ϸ�, �� ����鿡 ������ �� �����ϴ�.										 \n");
	printf("\t\t\t\t\t\t   																													 \n");
	printf("\t\t\t\t\t\t   ���� ������ �� 20���� ī�尡 �����մϴ�.																				\n");
	printf("\t\t\t\t\t\t   ��� ī�忡�� ���ϴܿ� 1 - 10�� ���ڰ� �ϳ��� ���� �ִµ�,															   \n");
	printf("\t\t\t\t\t\t   �� �̹����� �ϳ��� ���ھ� �����Ǿ�����, �� �̹����� 2���� �־� �� 20���� �Ǵ� ���Դϴ�.									 \n");
	printf("\t\t\t\t\t\t   																													 \n");
	printf("\t\t\t\t\t\t   ī���� �»�ܿ��� ���� �۴����� 1 - 2�� �׷��� �ִµ�,																   \n");
	printf("\t\t\t\t\t\t   ���� �۴�Ⱑ �ϳ��� ��� ī���� �Ϸù�ȣ�� ���ϴ��� ���ڿ� ���� 1 - 10,												  \n");
	printf("\t\t\t\t\t\t   ���� ��� ���� �����ϰ� �����ϵ� 10�� ���� 10 + N��° ī��� �����մϴ�.												   \n");
	printf("\t\t\t\t\t\t   																													 \n");
	printf("\t\t\t\t\t\t   1, 3, 8��° ī�� �� �Ϻ��� ��쿡�� ������ ���̾Ƹ�� ����� �ִµ�, �̴� ���ٿ����� '��'�� �����ϴ�.						 \n\n");
	printf("\t\t\t\t\t\t   ������ �÷��̸� ���� 2�� ���� �� ���������� �̸� ������ ����ϴ� ���� ������ ������,						 \n\n");
	printf("\t\t\t\t\t\t   �� 3��, �׷��� ��� �а� ���������� �����Ǿ��� ��, ȭ���� ���ϴܿ��� ������ ������ ǥ�õ˴ϴ�.							 \n\n");
	printf("\t\t\t\t\t\t   																													 \n");
	printf("\t\t\t\t\t\t   �÷��̾�� �� �Ǹ��� �� 6���� ������ ������ �� �� ������, �̴� ���ʴ��(����), (��), (����), (��), (����), (����)�Դϴ�.	  \n\n");
	printf("\t\t\t\t\t\t   (����)�� ���� ������ ������ �����ϴ� �����Դϴ�.																		\n");
	printf("\t\t\t\t\t\t   (��)�� ó�� ������ �ߴ� ĵ���� ������ŭ �����մϴ�.																		\n");
	printf("\t\t\t\t\t\t   (����)�� �ռ� ���õ� ĵ�� ���� �� �踦 �����մϴ�.																		 \n");
	printf("\t\t\t\t\t\t   (��)�� �ռ� ���õ� ĵ�� ���� ���� ���� �����մϴ�.																		 \n");
	printf("\t\t\t\t\t\t   (����)�� ���� ���� ĵ���� 1 / 4�� �ش��ϴ� ���� �����մϴ�.															   \n");
	printf("\t\t\t\t\t\t   (����)�� ���� ���� ĵ���� ���ݿ� �ش��ϴ� ���� �����մϴ�.																  \n");
	printf("\t\t\t\t\t\t   																													 \n");
	printf("\t\t\t\t\t\t   <���� ���>																										  \n");
	printf("\t\t\t\t\t\t   - ���� : �����θ� ������ ����																							\n");
	printf("\t\t\t\t\t\t   - �� : ���� �׸��� �� 2��																							   \n");
	printf("\t\t\t\t\t\t   - �߰����� : Ư�� �׸��� �������� �̷������ ���� �� ������ Ư���� ����													  \n");
	printf("\t\t\t\t\t\t   - Ư������ : Ư�� ���� ����Ǵ� ������ ����																			   \n");
	printf("\t\t\t\t\t\t   - �� : �� ���� ������ ���� ���� ���ڸ� ����(����)�� ũ�� �¸�.														  \n");
	printf("\t\t\t\t\t\t             																											 \n");
	printf("\t\t\t\t\t\t                                ������ : �輺�� �輺�� �ֹμ� ���¿�\n\n");
	printf("\t\t\t\t\t\t                            �����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.\n");

	while (true)
	{
		if (InputManager::Instance().KeyBoardControl() == SELECT)
		{
			ConsoleManager::Instance().ChangeConsoleSize(95, 24);
			break;
		}
	}
}
void PrintManager::DrawMainGameScreen(Player* p_player)
{
	DrawMainBoard(p_player);
}
void PrintManager::DrawCardCombination(Player p_player)
{
	// ù��° ����
	ConsoleManager::Instance().GoToXY(56, 45);
	cout << p_player.myCard[0].GetcardNumber() << " , " << p_player.myCard[1].GetcardNumber();
	ConsoleManager::Instance().GoToXY(56, 55);
	cout << "[1]";

	// �ι�° ����
	ConsoleManager::Instance().GoToXY(86, 45);
	cout << p_player.myCard[1].GetcardNumber() << " , " << p_player.myCard[2].GetcardNumber();
	ConsoleManager::Instance().GoToXY(86, 55);
	cout << "[2]";

	// ����° ����
	ConsoleManager::Instance().GoToXY(116, 45);
	cout << p_player.myCard[0].GetcardNumber() << " , " << p_player.myCard[2].GetcardNumber();
	ConsoleManager::Instance().GoToXY(116, 55);
	cout << "[3]";
}
void PrintManager::DrawPlayerCard(int curPlayerNumber, int cardNumber)
{
	CardArea tempArea = CardArea::MAIN1;
	switch (handOutIndex)
	{
		case 1:
			tempArea = CardArea::MAIN1;
			ConsoleManager::Instance().GoToXY(56, 55);
			cout << "[1]";
			break;
		case 2:
			tempArea = CardArea::MAIN2;
			ConsoleManager::Instance().GoToXY(86, 55);
			cout << "[2]";
			break;

		case 3:
			tempArea = CardArea::MAIN3;
			ConsoleManager::Instance().GoToXY(116, 55);
			cout << "[3]";
			break;
	}

	PrintImage(tempArea, GetDrawImage(cardNumber));

	handOutIndex++;
	if (handOutIndex == 4)
	{
		handOutIndex = 1;
	}
}
char(*PrintManager::GetDrawImage(int cardNumber))[20]
{
	char(*temp)[20] = _ghost1;
	switch (cardNumber)
	{
		case 1:
			temp = _ghost1;
			break;
		case 2:
			temp = _pumpkin1;
			break;
		case 3:
			temp = _spider1;
			break;
		case 4:
			temp = _coffin1;
			break;
		case 5:
			temp = _fox1;
			break;
		case 6:
			temp = _hat1;
			break;
		case 7:
			temp = _cat1;
			break;
		case 8:
			temp = _bat1;
			break;
		case 9:
			temp = _skull1;
			break;
		case 10:
			temp = _bone1;
			break;
		case 11:
			temp = _ghost2;
			break;
		case 12:
			temp = _pumpkin2;
			break;
		case 13:
			temp = _spider2;
			break;
		case 14:
			temp = _coffin2;
			break;
		case 15:
			temp = _fox2;
			break;
		case 16:
			temp = _hat2;
			break;
		case 17:
			temp = _cat2;
			break;
		case 18:
			temp = _bat2;
			break;
		case 19:
			temp = _skull2;
			break;
		case 20:
			temp = _bone2;
			break;
		default:
			temp = back;
			break;
	}
	return temp;
}
void PrintManager::PrintAllPlayerOpenCard()
{
	while (true)
	{
		if ((players[0].isGameOver || players[0].myOpenCard.cardNumber != 0) &&
			(players[1].isGameOver || players[1].myOpenCard.cardNumber != 0) &&
			(players[2].isGameOver || players[2].myOpenCard.cardNumber != 0) &&
			(players[3].isGameOver || players[3].myOpenCard.cardNumber != 0))		{
			break;
		}
	}
	if (!players[0].isGameOver)
	{
		PrintImage(CardArea::P1_1, GetDrawImage(players[0].myOpenCard.cardNumber));
	}
	if (!players[1].isGameOver)
	{
		PrintImage(CardArea::P2_1, GetDrawImage(players[1].myOpenCard.cardNumber));
	}
	if (!players[2].isGameOver)
	{
		PrintImage(CardArea::P3_1, GetDrawImage(players[2].myOpenCard.cardNumber));
	}
	if (!players[3].isGameOver)
	{
		PrintImage(CardArea::P4_1, GetDrawImage(players[3].myOpenCard.cardNumber));
	}
}
void PrintManager::FirstAllPlayerCandyRePrint()
{
	// �÷��̾�1 ĵ�����
	ConsoleManager::Instance().GoToXY(125, 14);
	std::cout << "Candy : " << players[0].candy;
	// �÷��̾�2 ĵ�����
	ConsoleManager::Instance().GoToXY(125, 37);
	std::cout << "Candy : " << players[1].candy;
	// �÷��̾�3 ĵ�����
	ConsoleManager::Instance().GoToXY(25, 14);
	std::cout << "Candy : " << players[2].candy;
	// �÷��̾�4 ĵ�����
	ConsoleManager::Instance().GoToXY(25, 37);
	std::cout << "Candy : " << players[3].candy;

	// ���� �� ĵ�� ���
	ConsoleManager::Instance().GoToXY(105, 25);
	std::cout << "Game Candy : " << totalGameCandy;
}
void PrintManager::PrintBettingInfo(int playerIndex, int betInfoIndex)
{
	string str = "";
	switch (betInfoIndex)
	{
		case 4:
			str = "����";
			break;
		case 5:
			str = "��";
			break;
		case 6:
			str = "����";
			break;
		case 7:
			str = "��";
			break;
		case 8:
			str = "����";
			break;
		case 9:
			str = "����";
			break;
	}
	switch (playerIndex)
	{
		case 0:
			EraseArea(true, 124, 35, 127, 35);
			EraseArea(true, 24, 12, 27, 12);
			EraseArea(true, 24, 35, 27, 35);

			ConsoleManager::Instance().GoToXY(124, 12);
			cout << str;
			break;

		case 1:
			EraseArea(true, 124, 12, 127, 12);
			EraseArea(true, 24, 12, 27, 12);
			EraseArea(true, 24, 35, 27, 35);

			ConsoleManager::Instance().GoToXY(124, 35);
			cout << str;
			break;

		case 2:
			EraseArea(true, 124, 12, 127, 12);
			EraseArea(true, 124, 35, 127, 35);
			EraseArea(true, 24, 35, 27, 35);

			ConsoleManager::Instance().GoToXY(24, 12);
			cout << str;
			break;

		case 3:
			EraseArea(true, 124, 12, 127, 12);
			EraseArea(true, 124, 35, 127, 35);
			EraseArea(true, 24, 12, 27, 12);

			ConsoleManager::Instance().GoToXY(24, 35);
			cout << str;
			break;
	}
}
void PrintManager::PrintPlayerCandy(int playerIndex)
{
	switch (playerIndex)
	{
		case 0:
			EraseArea(true, 133, 14, 138, 14);
			ConsoleManager::Instance().GoToXY(133, 14);
			cout << players[playerIndex].candy;
			break;
		case 1:
			EraseArea(true, 133, 37, 138, 37);
			ConsoleManager::Instance().GoToXY(133, 37);
			cout << players[playerIndex].candy;
			break;
		case 2:
			EraseArea(true, 33, 14, 38, 14);
			ConsoleManager::Instance().GoToXY(33, 14);
			cout << players[playerIndex].candy;
			break;
		case 3:
			EraseArea(true, 33, 37, 38, 37);
			ConsoleManager::Instance().GoToXY(33, 37);
			cout << players[playerIndex].candy;
			break;
	}
}
void PrintManager::PrintTotalGameCandy()
{
	ConsoleManager::Instance().GoToXY(118, 25);
	cout << totalGameCandy;
}
void PrintManager::DeleteBettingInfo()
{
	EraseArea(true, 124, 12, 128, 12);
	EraseArea(true, 124, 35, 128, 35);
	EraseArea(true, 24, 12, 28, 12);
	EraseArea(true, 24, 35, 28, 35);
}
void PrintManager::PrintArrow(int playerNumber)
{
	switch (playerNumber)
	{
		case 0:
			DrawPlayerArrow(1);
			break;
		case 1:
			DrawPlayerArrow(2);
			break;
		case 2:
			DrawPlayerArrow(3);
			break;
		case 3:
			DrawPlayerArrow(4);
			break;
	}
}
void PrintManager::DleteArrow()
{
	ErasePlayerArrow(1);
	ErasePlayerArrow(2);
	ErasePlayerArrow(3);
	ErasePlayerArrow(4);
}
void PrintManager::PrintAllPlayerMatchCard()
{
	while (true)
	{
		if ((players[0].isSelectMatchCard || players[0].isDie || players[0].isGameOver) &&
			(players[1].isSelectMatchCard || players[1].isDie || players[1].isGameOver) &&
			(players[2].isSelectMatchCard || players[2].isDie || players[2].isGameOver) &&
			(players[3].isSelectMatchCard || players[3].isDie || players[3].isGameOver))
		{
			break;
		}
	}
	if (!players[0].isDie && !players[0].isGameOver)
	{
		PrintImage(CardArea::P1_1, GetDrawImage(players[0].mySelectCard[0].cardNumber));
		PrintImage(CardArea::P1_2, GetDrawImage(players[0].mySelectCard[1].cardNumber));
	}
	if (!players[1].isDie && !players[1].isGameOver)
	{
		PrintImage(CardArea::P2_1, GetDrawImage(players[1].mySelectCard[0].cardNumber));
		PrintImage(CardArea::P2_2, GetDrawImage(players[1].mySelectCard[1].cardNumber));
	}
	if (!players[2].isDie && !players[2].isGameOver)
	{
		PrintImage(CardArea::P3_1, GetDrawImage(players[2].mySelectCard[0].cardNumber));
		PrintImage(CardArea::P3_2, GetDrawImage(players[2].mySelectCard[1].cardNumber));
	}
	if (!players[3].isDie && !players[3].isGameOver)
	{
		PrintImage(CardArea::P4_1, GetDrawImage(players[3].mySelectCard[0].cardNumber));
		PrintImage(CardArea::P4_2, GetDrawImage(players[3].mySelectCard[1].cardNumber));
	}
}
void PrintManager::PrintPlayerState(Player* p_player)
{
	if (p_player[0].isGameOver == true)
	{
		ConsoleManager::Instance().GoToXY(128, 11);
		cout << "Game Over!";
	}
	if (p_player[1].isGameOver == true)
	{
		ConsoleManager::Instance().GoToXY(128, 34);
		cout << "Game Over!";
	}
	if (p_player[2].isGameOver == true)
	{
		ConsoleManager::Instance().GoToXY(28, 11);
		cout << "Game Over!";
	}
	if (p_player[3].isGameOver == true)
	{
		ConsoleManager::Instance().GoToXY(28, 34);
		cout << "Game Over!";
	}
}
void PrintManager::PrintCurrentMyCandy(int playerIndex)
{
	switch (playerIndex)
	{
		case 0:
			EraseArea(true, 133, 14, 138, 14);
			break;

		case 1:
			EraseArea(true, 133, 37, 138, 37);
			break;

		case 2:
			EraseArea(true, 33, 14, 38, 14);
			break;

		case 3:
			EraseArea(true, 33, 37, 38, 37);
			break;
	}
}
void PrintManager::ShowBettingInfo(int playerIndex, int bettingInfo)
{
	BetInfo betInfo = BetInfo::BBING;
	switch (bettingInfo)
	{
		case 4:
			betInfo = BetInfo::DDIE;
			break;
		case 5:
			betInfo = BetInfo::BBING;
			break;
		case 6:
			betInfo = BetInfo::DDADANG;
			break;
		case 7:
			betInfo = BetInfo::CALL;
			break;
		case 8:
			betInfo = BetInfo::QUARTER;
			break;
		case 9:
			betInfo = BetInfo::HALF;
			break;
	}
	PrintDie(playerIndex);

	///PrintDie(betInfo, playerIndex);

	/*string str = "";
	switch (bettingInfo)
	{
		case FOUR:
			str = "����";
			break;

		case FIVE:
			str = "��";
			break;

		case SIX:
			str = "����";
			break;

		case SEVEN:
			str = "��";
			break;

		case EIGHT:
			str = "����";
			break;

		case NINE:
			str = "����";
			break;
	}

	switch (playerIndex)
	{
		case 0:
			ConsoleManager::Instance().GoToXY(124, 12);
			break;

		case 1:
			ConsoleManager::Instance().GoToXY(124, 35);
			break;

		case 2:
			ConsoleManager::Instance().GoToXY(24, 12);
			break;

		case 3:
			ConsoleManager::Instance().GoToXY(24, 35);
			break;
	}
	cout << str;*/
}
void PrintManager::ShowAllplayerOpenCard(int playerIndex)
{
	switch (playerIndex)
	{
		case 0:
			PrintImage(CardArea::P1_1, GetDrawImage(players[playerIndex].myOpenCard.cardNumber));
			break;
		case 1:
			PrintImage(CardArea::P2_1, GetDrawImage(players[playerIndex].myOpenCard.cardNumber));
			break;
		case 2:
			PrintImage(CardArea::P3_1, GetDrawImage(players[playerIndex].myOpenCard.cardNumber));
			break;
		case 3:
			PrintImage(CardArea::P4_1, GetDrawImage(players[playerIndex].myOpenCard.cardNumber));
			break;
	}
}
void PrintManager::ShowCardCombination(Player player)
{
	if (player.isDie == true || player.isGameOver == true) return;

	JOKBO tempJokbo[3] = { JOKBO::YET,JOKBO::YET,JOKBO::YET };
	JokboGubun(&player, tempJokbo);
	InfoArea tempArea = InfoArea::INFO1;
	string str = "";


	for (int i = 0; i < 3; i++)
	{
		if (i == 0) 	tempArea = InfoArea::INFO1;
		else if (i == 1) tempArea = InfoArea::INFO2;
		else if (i == 2) tempArea = InfoArea::INFO3;

		switch (tempJokbo[i])
		{
			case GT38:
				str = "3.8 ����";
				break;
			case AHOS:
				str = "������";
				break;
			case GT18:
				str = "1.8 ����";
				break;
			case GT13:
				str = "1.3 ����";
				break;
			case ZTT:
				str = "�嶯(10��)";
				break;
			case TTJ:
				str = "������";
				break;
			case TT9:
				str = "9��";
				break;
			case TT8:
				str = "8��";
				break;
			case TT7:
				str = "7��";
				break;
			case TT6:
				str = "6��";
				break;
			case TT5:
				str = "5��";
				break;
			case TT4:
				str = "4��";
				break;
			case TT3:
				str = "3��";
				break;
			case TT2:
				str = "2��";
				break;
			case TT1:
				str = "1��";
				break;
			case ALI:
				str = "�˸�";
				break;
			case DS:
				str = "����";
				break;
			case GBB:
				str = "����";
				break;
			case ZBB:
				str = "���";
				break;
			case ZS:
				str = "���";
				break;
			case SYG:
				str = "����/���";
				break;
			case KKT9:
				str = "����";
				break;
			case KKT8:
				str = "8��";
				break;
			case KKT7:
				str = "7��";
				break;
			case KKT6:
				str = "6��";
				break;
			case KKT5:
				str = "5��";
				break;
			case KKT4:
				str = "4��";
				break;
			case KKT3:
				str = "3��";
				break;
			case KKT2:
				str = "2��";
				break;
			case KKT1:
				str = "1��";
				break;
			case KKT0:
				str = "����";
				break;
			default:
				break;
		}
		PrintInfo(tempArea, str);
	}
}
void PrintManager::DeleteAllImage()
{
	EraseArea(CardArea::MAIN1);
	EraseArea(CardArea::MAIN2);
	EraseArea(CardArea::MAIN3);
	EraseArea(CardArea::P1_1);
	EraseArea(CardArea::P1_2);
	EraseArea(CardArea::P2_1);
	EraseArea(CardArea::P2_2);
	EraseArea(CardArea::P3_1);
	EraseArea(CardArea::P3_2);
	EraseArea(CardArea::P4_1);
	EraseArea(CardArea::P4_2);
}
void PrintManager::ResetTextColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | 0);
}
void PrintManager::AddDecoration()
{
	ConsoleManager::Instance().GoToXY(0, 52);
	DrawRow(0, 0, 100);

	ConsoleManager::Instance().GoToXY(199, 79);
}
void PrintManager::PrintImage(CardArea _area, char _arr[][20])
{
	int _x = 0;
	int _y = 0;
	if (_area == CardArea::MAIN1)
	{
		_x = 48;
		_y = 60;
	}
	else if (_area == CardArea::MAIN2)
	{
		_x = 78;
		_y = 60;
	}
	else if (_area == CardArea::MAIN3)
	{
		_x = 108;
		_y = 60;
	}
	else if (_area == CardArea::P1_1)
	{
		_x = 141;
		_y = 5;
	}
	else if (_area == CardArea::P1_2)
	{
		_x = 166;
		_y = 5;
	}
	else if (_area == CardArea::P2_1)
	{
		_x = 141;
		_y = 28;
	}
	else if (_area == CardArea::P2_2)
	{
		_x = 166;
		_y = 28;
	}
	else if (_area == CardArea::P3_1)
	{
		_x = 42;
		_y = 5;
	}
	else if (_area == CardArea::P3_2)
	{
		_x = 66;
		_y = 5;
	}
	else if (_area == CardArea::P4_1)
	{
		_x = 42;
		_y = 28;
	}
	else if (_area == CardArea::P4_2)
	{
		_x = 66;
		_y = 28;
	}
	else
	{
		cout << "wrong parameter";
	}
	ConsoleManager::Instance().GoToXY(_x, _y);
	//��ü 20, �ε����� -1
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (_arr[i][j] == '1')
			{
				ConsoleManager::Instance().SetColor(WHITE, WHITE);
				cout << " ";
			}
			else if (_arr[i][j] == '0')
			{
				ConsoleManager::Instance().SetColor(BLACK, BLACK);
				cout << " ";
			}
			else if (_arr[i][j] == '2')
			{
				ConsoleManager::Instance().SetColor(DARKYELLOW, DARKYELLOW);
				cout << " ";
			}
			else if (_arr[i][j] == '3')
			{
				ConsoleManager::Instance().SetColor(RED, RED);
				cout << " ";
			}
			else if (_arr[i][j] == '4')
			{
				ConsoleManager::Instance().SetColor(YELLOW, YELLOW);
				cout << " ";
			}
			else if (_arr[i][j] == '5')
			{
				ConsoleManager::Instance().SetColor(PURPLE, PURPLE);
				cout << " ";
			}
			//cout << smallGhost[i][j];
		}
		ConsoleManager::Instance().GoToXY(_x, _y + i);
	}
	ResetTextColor();
	ConsoleManager::Instance().GoToXY(199, 79);
}
void PrintManager::PrintInfo(InfoArea _area, string _str)
{
	if (_area == InfoArea::INFO1)
	{
		ConsoleManager::Instance().GoToXY(4, 60);
		cout << _str;
	}
	else if (_area == InfoArea::INFO2)
	{
		ConsoleManager::Instance().GoToXY(4, 67);
		cout << _str;
	}
	else if (_area == InfoArea::INFO3)
	{
		ConsoleManager::Instance().GoToXY(4, 74);
		cout << _str;
	}
	else
	{
		cout << "wrong parameter";
	}
	ConsoleManager::Instance().GoToXY(199, 79);
}
void PrintManager::FillArea(bool _isShort, int _startX, int _startY, int _endX, int _endY)
{
	if (_isShort)
	{//�Ϲ� ����, 1ĭ�� ũ�⸦ ���� ������ ä���.
		int tempX = _startX;
		int tempY = _startY;
		ConsoleManager::Instance().GoToXY(tempX, tempY);
		for (int i = tempY; i <= _endY; i++)
		{
			for (int j = tempX; j <= _endX; j++)
			{
				printf("0");
			}
			tempY++;
			ConsoleManager::Instance().GoToXY(tempX, tempY);
		}
	}
	else
	{//�Ϲ� ����, 2ĭ�� ũ�⸦ ���� ������ ä���.
		int tempX = _startX;
		int tempY = _startY;
		ConsoleManager::Instance().GoToXY(tempX, tempY);
		for (int i = 0; i <= (_endY - _startY); i++)
		{
			for (int j = 0; j <= (_endX - _startX) / 2; j++)
			{
				printf("��");
			}
			ConsoleManager::Instance().GoToXY(tempX, tempY + i);
		}
	}
}
void PrintManager::EraseArea(bool _isShort, int _startX, int _startY, int _endX, int _endY)
{
	if (_startY == _endY)
	{
		ConsoleManager::Instance().GoToXY(_startX, _startY);
		for (int i = _startX; i <= _endX; i++)
		{
			printf(" ");
		}
	}
	else
	{
		if (_isShort)
		{
			//�Ϲ� ����, 1ĭ�� ũ�⸦ ���� ������ �����.
			int tempX = _startX;
			int tempY = _startY;
			ConsoleManager::Instance().GoToXY(tempX, tempY);
			for (int i = tempY; i <= _endY; i++)
			{
				for (int j = tempX; j <= _endX; j++)
				{
					printf(" ");
				}
				tempY++;
				ConsoleManager::Instance().GoToXY(tempX, tempY);
			}
		}
		else
		{
			//�Ϲ� ����, 2ĭ�� ũ�⸦ ���� ������ �����.
			int tempX = _startX;
			int tempY = _startY;
			ConsoleManager::Instance().GoToXY(tempX, tempY);
			for (int i = 0; i <= (_endY - _startY); i++)
			{
				for (int j = 0; j <= (_endX - _startX) / 2; j++)
				{
					printf("  ");
				}
				ConsoleManager::Instance().GoToXY(tempX, tempY + i);
			}
		}
	}

}
void PrintManager::EraseArea(InfoArea _area)
{
	int _startX, _startY, _endX, _endY;

	if (_area == InfoArea::INFO1)
	{
		_startX = 4;
		_startY = 60;

	}
	else if (_area == InfoArea::INFO2)
	{
		_startX = 4;
		_startY = 67;
	}
	else if (_area == InfoArea::INFO3)
	{
		_startX = 4;
		_startY = 74;
	}
	_endX = _startX + 26;
	_endY = _startY + 3;
	//�Ϲ� ����, 2ĭ�� ũ�⸦ ���� ������ �����.
	ConsoleManager::Instance().GoToXY(_startX, _startY);
	for (int i = 0; i <= (_endY - _startY); i++)
	{
		for (int j = 0; j <= (_endX - _startX) / 2; j++)
		{
			printf("  ");
		}
		ConsoleManager::Instance().GoToXY(_startX, _startY + i);
	}
	ConsoleManager::Instance().GoToXY(199, 79);
}
void PrintManager::EraseArea(CardArea _area)
{
	int _startX, _startY, _endX, _endY;
	if (_area == CardArea::MAIN1)
	{
		_startX = 48;
		_startY = 60;
	}
	else if (_area == CardArea::MAIN2)
	{
		_startX = 78;
		_startY = 60;
	}
	else if (_area == CardArea::MAIN3)
	{
		_startX = 108;
		_startY = 60;
	}
	else if (_area == CardArea::P1_1)
	{
		_startX = 141;
		_startY = 5;
	}
	else if (_area == CardArea::P1_2)
	{
		_startX = 166;
		_startY = 5;
	}
	else if (_area == CardArea::P2_1)
	{
		_startX = 141;
		_startY = 28;
	}
	else if (_area == CardArea::P2_2)
	{
		_startX = 166;
		_startY = 28;
	}
	else if (_area == CardArea::P3_1)
	{
		_startX = 42;
		_startY = 5;
	}
	else if (_area == CardArea::P3_2)
	{
		_startX = 66;
		_startY = 5;
	}
	else if (_area == CardArea::P4_1)
	{
		_startX = 42;
		_startY = 28;
	}
	else if (_area == CardArea::P4_2)
	{
		_startX = 66;
		_startY = 28;
	}

	_endX = _startX + 19;
	_endY = _startY + 18;
	//�Ϲ� ����, 2ĭ�� ũ�⸦ ���� ������ �����.
	ConsoleManager::Instance().GoToXY(_startX, _startY);
	for (int i = 0; i <= (_endY - _startY); i++)
	{
		for (int j = 0; j <= (_endX - _startX) / 2; j++)
		{
			printf("  ");
		}
		ConsoleManager::Instance().GoToXY(_startX, _startY + i);
	}
	ConsoleManager::Instance().GoToXY(199, 79);
}
void PrintManager::PrintWin(int playerNo)
{
	int _x = -1, _y = -1;
	int* p_x = &_x;
	int* p_y = &_y;
	switch (playerNo)
	{
		case 1:
			*p_x = 103; // +3 +5
			*p_y = 11;
			break;
		case 2:
			*p_x = 103;
			*p_y = 34;
			break;
		case 3:
			*p_x = 4;
			*p_y = 11;
			break;
		case 4:
			*p_x = 4;
			*p_y = 34;
			break;
		default:
			cout << "wrong parameter";
			break;
	}
	ConsoleManager::Instance().GoToXY(_x, _y);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (_winMessage[i][j] == '0')
			{
				ConsoleManager::Instance().SetColor(WHITE, WHITE);
				cout << " ";
			}
			else if (_winMessage[i][j] == '8')
			{
				ConsoleManager::Instance().SetColor(RED, RED);
				cout << " ";
			}
			else if (_winMessage[i][j] == '9')
			{
				ConsoleManager::Instance().SetColor(YELLOW, YELLOW);
				cout << " ";
			}
		}
		ConsoleManager::Instance().GoToXY(_x, _y + i);
	}
	ResetTextColor();
}
void PrintManager::DrawRow(int _x, int _y, int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << "��";
	}
}
void PrintManager::DrawColumn(int _x, int _y, int length)
{
	int localX = _x;
	int localY = _y;
	for (int i = 0; i < length; i++)
	{
		ConsoleManager::Instance().GoToXY(localX, localY);
		cout << "��";
		localY += 1;
	}
}
void PrintManager::DrawPlayerArrow(int playerNo) //�Ű����� int = �÷��̾� ��ȣ
{
	switch (playerNo)
	{
	case 1:
		////player1

		ConsoleManager::Instance().GoToXY(125, 12);
		cout << "��";

		break;
	case 2:
		//player2
		ConsoleManager::Instance().GoToXY(125, 35);
		cout << "��";

		break;
	case 3:
		////player3
		ConsoleManager::Instance().GoToXY(25, 12);
		cout << "��";

		break;
	case 4:
		////player4
		ConsoleManager::Instance().GoToXY(25, 35);
		cout << "��";

		break;
	default:
		cout << "wrong parameter";
		break;
	}
}
void PrintManager::ErasePlayerArrow(int playerNo)
{
	switch (playerNo)
	{
	case 1:
		////player1

		ConsoleManager::Instance().GoToXY(125, 12);
		cout << "  ";

		break;
	case 2:
		//player2
		ConsoleManager::Instance().GoToXY(125, 35);
		cout << "  ";

		break;
	case 3:
		////player3
		ConsoleManager::Instance().GoToXY(25, 12);
		cout << "  ";

		break;
	case 4:
		////player4
		ConsoleManager::Instance().GoToXY(25, 35);
		cout << "  ";

		break;
	default:
		cout << "wrong parameter";
		break;
	}
}
void PrintManager::DrawPlayerCardsOnBoard(int playerNo)
{
	switch (playerNo)
	{
		case 1:
			ConsoleManager::Instance().GoToXY(129, 12); //y�� -2
			cout << "player1";

			ConsoleManager::Instance().GoToXY(139, 4); //y�� -2
			cout << "��";
			DrawRow(0, 0, 10);
			DrawColumn(139, 5, 18); //y�� -2
			ConsoleManager::Instance().GoToXY(160, 4);
			cout << "��";
			DrawColumn(161, 5, 18);//y�� -2
			ConsoleManager::Instance().GoToXY(160, 23);
			cout << "��";
			ConsoleManager::Instance().GoToXY(139, 23);
			cout << "��";
			DrawRow(0, 0, 10);

			ConsoleManager::Instance().GoToXY(165, 4);
			cout << "��";
			DrawRow(0, 0, 10);
			DrawColumn(165, 5, 18);
			ConsoleManager::Instance().GoToXY(185, 4);
			cout << "��";
			DrawColumn(185, 5, 18);
			ConsoleManager::Instance().GoToXY(185, 23);
			cout << "��";
			ConsoleManager::Instance().GoToXY(165, 23);
			cout << "��";
			DrawRow(0, 0, 9);

			break;
		case 2:
			ConsoleManager::Instance().GoToXY(129, 35);
			cout << "player2";

			ConsoleManager::Instance().GoToXY(139, 27);
			cout << "��";
			DrawRow(0, 0, 10);
			DrawColumn(139, 28, 18);
			ConsoleManager::Instance().GoToXY(160, 27);
			cout << "��";
			DrawColumn(161, 28, 18);
			ConsoleManager::Instance().GoToXY(161, 46);
			cout << "��";
			ConsoleManager::Instance().GoToXY(139, 46);
			cout << "��";
			DrawRow(0, 0, 10);

			ConsoleManager::Instance().GoToXY(165, 27);
			cout << "��";
			DrawRow(0, 0, 10);
			DrawColumn(165, 28, 18);
			ConsoleManager::Instance().GoToXY(185, 27);
			cout << "��";
			DrawColumn(185, 28, 18);
			ConsoleManager::Instance().GoToXY(165, 46);
			cout << "��";
			DrawRow(0, 0, 10);
			ConsoleManager::Instance().GoToXY(185, 46);
			cout << "��";

			break;
		case 3:
			ConsoleManager::Instance().GoToXY(29, 12);
			cout << "player3";

			ConsoleManager::Instance().GoToXY(39, 4);
			cout << "��";
			DrawRow(0, 0, 10);
			DrawColumn(39, 5, 18);
			ConsoleManager::Instance().GoToXY(60, 4);
			cout << "��";
			DrawColumn(61, 5, 18);
			ConsoleManager::Instance().GoToXY(60, 23);
			cout << "��";
			ConsoleManager::Instance().GoToXY(39, 23);
			cout << "��";
			DrawRow(0, 0, 10);

			ConsoleManager::Instance().GoToXY(65, 4);
			cout << "��";
			DrawRow(0, 0, 10);
			DrawColumn(65, 5, 18);
			ConsoleManager::Instance().GoToXY(86, 4);
			cout << "��";
			DrawColumn(87, 5, 18);
			ConsoleManager::Instance().GoToXY(86, 23);
			cout << "��";
			ConsoleManager::Instance().GoToXY(65, 23);
			cout << "��";
			DrawRow(0, 0, 10);
			break;
		case 4:
			ConsoleManager::Instance().GoToXY(29, 35);
			cout << "player4";

			ConsoleManager::Instance().GoToXY(39, 27);
			cout << "��";
			DrawRow(0, 0, 10);
			DrawColumn(39, 28, 18);
			ConsoleManager::Instance().GoToXY(60, 27);
			cout << "��";
			DrawColumn(61, 28, 18);
			ConsoleManager::Instance().GoToXY(60, 46);
			cout << "��";
			ConsoleManager::Instance().GoToXY(39, 46);
			cout << "��";
			DrawRow(0, 0, 10);

			ConsoleManager::Instance().GoToXY(65, 27);
			cout << "��";
			DrawRow(0, 0, 10);
			DrawColumn(65, 28, 18);
			ConsoleManager::Instance().GoToXY(86, 27);
			cout << "��";
			DrawColumn(87, 28, 18);
			ConsoleManager::Instance().GoToXY(86, 46);
			cout << "��";
			ConsoleManager::Instance().GoToXY(65, 46);
			cout << "��";
			DrawRow(0, 0, 10);
			break;
		default:
			cout << "wrong parameter";
			break;
	}
}
void PrintManager::PutCardFrames()
{
	ConsoleManager::Instance().GoToXY(45, 59); //�������� y���� 1�� ��
	cout << "��";
	DrawRow(0, 0, 11);
	DrawColumn(45, 60, 18); //�������� y���� 1�� ��, ���� 18��
	ConsoleManager::Instance().GoToXY(45, 78); //y�� 1�߰�.
	cout << "��";
	DrawRow(0, 0, 11);
	ConsoleManager::Instance().GoToXY(69, 78);
	cout << "��";
	DrawColumn(69, 60, 18);
	ConsoleManager::Instance().GoToXY(69, 59);
	cout << "��";

	ConsoleManager::Instance().GoToXY(75, 59);
	cout << "��";
	DrawRow(0, 0, 11);
	DrawColumn(75, 60, 18);
	ConsoleManager::Instance().GoToXY(75, 78);
	cout << "��";
	DrawRow(0, 0, 11);
	ConsoleManager::Instance().GoToXY(99, 78);
	cout << "��";
	DrawColumn(99, 60, 18);
	ConsoleManager::Instance().GoToXY(99, 59);
	cout << "��";

	ConsoleManager::Instance().GoToXY(105, 59);
	cout << "��";
	DrawRow(0, 0, 11);
	DrawColumn(105, 60, 18);
	ConsoleManager::Instance().GoToXY(105, 78);
	cout << "��";
	DrawRow(0, 0, 11);
	ConsoleManager::Instance().GoToXY(129, 78);
	cout << "��";
	DrawColumn(129, 60, 18);
	ConsoleManager::Instance().GoToXY(129, 59);
	cout << "��";
}
void PrintManager::DrawGameButtons()
{
	//�÷��̾� ī�� ����. //-20�� ��Ű��.
	ConsoleManager::Instance().GoToXY(39, 57);
	cout << "��";
	DrawRow(38, 60, 47);
	DrawColumn(39, 58, 22);
	ConsoleManager::Instance().GoToXY(134, 57);
	cout << "��";
	DrawColumn(135, 58, 22);
	//
	ConsoleManager::Instance().GoToXY(149, 55);
	cout << "��";
	DrawRow(0, 0, 11);
	DrawColumn(149, 56, 23);
	ConsoleManager::Instance().GoToXY(149, 79);
	cout << "��";
	DrawRow(0, 0, 11);
	//
	ConsoleManager::Instance().GoToXY(149, 63);
	cout << "��";
	DrawRow(0, 0, 11);
	//
	ConsoleManager::Instance().GoToXY(149, 71);
	cout << "��";
	DrawRow(0, 0, 11);
	//���
	ConsoleManager::Instance().GoToXY(173, 55);
	cout << "��";
	DrawRow(0, 0, 12);
	DrawColumn(173, 56, 7);
	ConsoleManager::Instance().GoToXY(173, 63);
	cout << "��";
	DrawRow(0, 0, 12);
	DrawColumn(173, 64, 7);
	ConsoleManager::Instance().GoToXY(173, 71);
	cout << "��";
	DrawRow(0, 0, 12);
	DrawColumn(173, 72, 7);
	ConsoleManager::Instance().GoToXY(173, 79);
	cout << "��";
	DrawRow(0, 0, 12);

	PrintAllBettingButton();


	//ī�� ���� �˷��ִ� �κ�.

	ConsoleManager::Instance().GoToXY(0, 57);
	cout << "��";
	DrawRow(0, 0, 15);
	ConsoleManager::Instance().GoToXY(32, 57);
	cout << "��";
	DrawColumn(32, 58, 6);
	ConsoleManager::Instance().GoToXY(32, 64);
	cout << "��";
	DrawColumn(32, 65, 6);
	ConsoleManager::Instance().GoToXY(32, 71);
	cout << "��";
	DrawColumn(32, 72, 6);
	ConsoleManager::Instance().GoToXY(32, 78);
	cout << "��";
	ConsoleManager::Instance().GoToXY(0, 78);
	cout << "��";
	DrawRow(0, 0, 15);
	ConsoleManager::Instance().GoToXY(0, 71);
	cout << "��";
	DrawRow(0, 0, 15);
	ConsoleManager::Instance().GoToXY(0, 64);
	cout << "��";
	DrawRow(0, 0, 15);
}
void PrintManager::PrintDie(int playerNo) // 0-3���� �ϱ�. 
{
	int tempX = 0;
	int tempY = 0;

	switch (playerNo)
	{
	case 0:
		tempX = 143;
		tempY = 6;
		break;
	case 1:
		tempX = 143;
		tempY = 31;
		break;
	case 2:
		tempX = 44;
		tempY = 6;
		break;
	case 3:
		tempX = 44;
		tempY = 31;
		break;
	default:
		cout << "wrong parameter";
		break;
	}

	switch (playerNo)
	{
	case 0:
		EraseArea(CardArea::P1_1);
		EraseArea(CardArea::P1_2);
		break;
	case 1:
		tempY -= 2;
		EraseArea(CardArea::P2_1);
		EraseArea(CardArea::P2_2);
		break;
	case 2:
		EraseArea(CardArea::P3_1);
		EraseArea(CardArea::P3_2);
		break;
	case 3:
		tempY -= 2;
		EraseArea(CardArea::P4_1);
		EraseArea(CardArea::P4_2);
		break;
	default:
		cout << "wrong parameter";
		break;
	}
	ConsoleManager::Instance().GoToXY(tempX, tempY);
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (_dieMessage[i][j] == '0')
			{
				ConsoleManager::Instance().SetColor(DARKRED, DARKRED);
				cout << " ";
			}
			else if (_dieMessage[i][j] == '8')
			{
				ConsoleManager::Instance().SetColor(WHITE, WHITE);
				cout << " ";
			}
			else if (_dieMessage[i][j] == '9')
			{
				ConsoleManager::Instance().SetColor(GRAY, GRAY);
				cout << " ";
			}
		}
		ConsoleManager::Instance().GoToXY(tempX, tempY + i);
	}
	ResetTextColor();
}


void PrintManager::DrawMainBoard(Player* p_player)
{
	system("mode con:cols=200 lines=80 | title=HallowUp");

	DrawPlayerCardsOnBoard(1);
	DrawPlayerCardsOnBoard(2);
	DrawPlayerCardsOnBoard(3);
	DrawPlayerCardsOnBoard(4);

	DrawGameButtons();
	AddDecoration();
	PutCardFrames();

	ConsoleManager::Instance().GoToXY(25, 60);
	cout << "[1]";
	ConsoleManager::Instance().GoToXY(25, 67);
	cout << "[2]";
	ConsoleManager::Instance().GoToXY(25, 74);
	cout << "[3]";

	ConsoleManager::Instance().GoToXY(199, 79);
}

void PrintManager::PrintAllBettingButton()
{
	if (player.isDie) return;
	ConsoleManager::Instance().GoToXY(158, 59);
	cout << "[4] ����";
	ConsoleManager::Instance().GoToXY(158, 67);
	cout << "[5] ��";
	ConsoleManager::Instance().GoToXY(158, 75);
	cout << "[6] ����";

	ConsoleManager::Instance().GoToXY(182, 59);
	cout << "[7] ��";
	ConsoleManager::Instance().GoToXY(182, 67);
	cout << "[8] ����";
	ConsoleManager::Instance().GoToXY(182, 75);
	cout << "[9] ����";
}

void PrintManager::DeleteSpecificBettingButton(bool isBbing, bool isDD, bool isCall,bool isQuarter, bool isHalf)
{
	if (isBbing == false)
	{
		EraseArea(true, 158, 67, 171, 67);
	}
	if (isDD == false)
	{
		EraseArea(true, 158, 75, 171, 75);
	}
	if (isCall == false)
	{
		EraseArea(true, 182, 59, 195, 59);
	}
	if (isQuarter == false)
	{
		EraseArea(true, 182, 67, 195,67);
	}
	if (isHalf == false)
	{
		EraseArea(true, 182, 75, 195, 75);
	}
}

void PrintManager::DeleteAllBettingButton()
{
	EraseArea(true, 158, 67, 171, 67);
	EraseArea(true, 158, 75, 171, 75);
	EraseArea(true, 182, 59, 195, 59);
	EraseArea(true, 182, 67, 195, 67);
	EraseArea(true, 182, 75, 195, 75);
	EraseArea(true, 158, 59, 171, 59);
}
