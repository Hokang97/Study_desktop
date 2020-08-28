#include <stdio.h>

#include <time.h>

#include <stdlib.h>

#include <Windows.h>

void Game();


void main()

{
    int retry = 1;

    do
    {

        Game();

        printf("������ ����Ǿ����ϴ�.\n\n�ٽ��Ϸ��� 1, �����Ϸ��� 1�� ������ ���� �Է����ּ���");

        scanf_s("%d", &retry);

    } while (retry == 1);

}

void Game()

{

    int Player[25];

    int Ai[25];

    int i, j;

    int bingo = 0; int aibingo = 0;

    int Mode;

    srand((unsigned)time(NULL));



    for (i = 0; i < 25; i++) // �迭�� 1 ~ 25���� ���� �ֱ�

    {

        Player[i] = i + 1;

        Ai[i] = i + 1;

    }

    for (i = 0; i < 100; i++) // ���� ����

    {

        int idx1 = rand() % 25;

        int idx2 = rand() % 25;

        int temp = Player[idx1];

        Player[idx1] = Player[idx2];

        Player[idx2] = temp;



        idx1 = rand() % 25;

        idx2 = rand() % 25;

        temp = Ai[idx1];

        Ai[idx1] = Ai[idx2];

        Ai[idx2] = temp;

    }

    enum SelectMode // ��弱�ÿ�

    {

        Easy = 1,

        Hard

    };

    enum Line // �ϵ��� ���μ��ÿ�

    {

        x1,

        x2,

        x3,

        x4,

        x5,

        y1,

        y2,

        y3,

        y4,

        y5,

        xy, // �»�� �밢��

        yx// ���� �밢��



    };

    const char* mode_s = "";

    while (true)       // ���̵� ����

    {

        system("cls");

        printf("���̵��� �������ּ���\n");

        printf("1. Easy   2. Hard : ");

        int input;

        scanf_s("%d", &input);

        getchar();

        if (input == Easy)

        {

            Mode = Easy; mode_s = "<Easy Mode>";



        }

        else if (input == Hard)

        {

            Mode = Hard; mode_s = "<Hard Mode>";

        }

        else

        {

            printf("�߸��Է��ϼ̽��ϴ�. �ٽ��Է����ּ���\n");

            getchar();

            continue;

        }

        break;

    }



    // ���ӽ��� 



    while (true)

    {

        system("cls");

        printf("===============Player==============\n"); // �÷��̾� ������

        for (i = 0; i < 5; i++)

        {

            for (j = 0; j < 5; j++)

            {

                if (Player[i * 5 + j] == INT_MAX)

                    printf("*\t");

                else printf("%d\t", Player[i * 5 + j]);

            }

            printf("\n\n");

        }



        printf("================AI==================  "); // AI ������

        if (Mode == Easy)

        {

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

            printf("%s\n", mode_s);

        }

        if (Mode == Hard)

        {

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

            printf("%s\n", mode_s);

        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);



        for (i = 0; i < 5; i++)

        {

            for (j = 0; j < 5; j++)

            {

                if (Ai[i * 5 + j] == INT_MAX)

                    printf("*\t");

                else printf("%d\t", Ai[i * 5 + j]);

            }

            printf("\n\n");

        }

        printf("�÷��̾� ���� : %d\n", bingo);

        printf("AI ���� : %d\n", aibingo);

        if (bingo == 8)

        {

            printf("�÷��̾� �¸�!");

            break;

        }

        if (aibingo == 8)

        {

            printf("�÷��̾� �й�!");

            break;

        }

        if (bingo == 8 && aibingo == 8)

        {

            printf("�����ϴ�.");

            break;

        }

        printf("1 ~ 25 ������ ���ڸ� �Է����ּ��� (�������� : 0) : ");

        int input;

        scanf_s("%d", &input);

        getchar();





        if (input == 0)

            break;

        if (input < 1 || input > 25) // ����ó��

        {

            printf("\n�߸��Է��ϼ̽��ϴ�. �ٽ��Է��Ͻ÷��� Enter�� �����ּ���");

            getchar();

            continue;

        }

        bool Check = true; // �ߺ������Է� Ȯ�ο�

        for (i = 0; i < 25; i++) // �÷��̾ �Է��Ѱ��� *�� ��ȯ - �÷��̾��

        {

            if (Player[i] == input)

            {

                Player[i] = INT_MAX;

                Check = false;

                break;

            }

        }

        for (i = 0; i < 25; i++) // �÷��̾ �Է��Ѱ��� *�� ��ȯ - ai ����

        {

            if (Ai[i] == input)

            {

                Ai[i] = INT_MAX;

                break;

            }

        }

        if (Check)

        {

            printf("\n�ߺ��� ���ڸ� �Է��ϼ̽��ϴ�. �ٽ��Է����ּ���");

            getchar();

            continue;

        }

        printf("�÷��̾��� ���� : %d\n", input);

        //���̵��� ���� ��ǻ���� ���ð� ����

        switch (Mode)

        {

        case Easy:

        {

            int noneSelect[25]; // ������ ���ڸ� �����ϰ� �������ڸ� �����ϴ� ����

            int noneSelectCount = 0;

            for (i = 0; i < 25; i++)

            {

                if (Ai[i] != INT_MAX)

                {

                    noneSelect[i] = Ai[i];   // ��ǥ ǥ�ð��ƴ�(�ߺ����ڰ� �ƴ�) ���� �����ؼ� noneSelect �迭�� ������� �־��ش�

                    noneSelectCount++; // �迭�� ����(���� ���ڰ� �����)�� ���Ѵ�

                }

            }

            input = noneSelect[rand() % noneSelectCount]; // �������ڸ� ������ �迭���� �����ϰ� ���ڸ� �����´�.

        }

        break;



        case Hard: // ���� �������� ���� ���ڸ� ã�Ƽ� �����Ѵ�

        {

            int starCount = 0; int saveCount = 0; int line;

            for (i = 0; i < 5; i++)  // ���ζ����� �����ƴϰ� *�� ���帹�� ������ ã�´�.

            {

                starCount = 0;

                for (j = 0; j < 5; j++)

                {

                    if (Ai[i * 5 + j] == INT_MAX)

                        starCount++;

                }

                if (starCount < 5 && starCount > saveCount)

                {

                    saveCount = starCount;

                    line = i;

                }

            }

            for (i = 0; i < 5; i++)  // ���ζ����� �����ƴϰ� *�� ���帹�� ������ ã�´�.

            {

                starCount = 0;

                for (j = 0; j < 5; j++)

                {

                    if (Ai[j * 5 + i] == INT_MAX)

                        starCount++;

                }

                if (starCount < 5 && starCount > saveCount)

                {

                    saveCount = starCount;

                    line = i + 5;  // ���ζ����� 0 ~ 4�� ���ζ����� 5 ~ 9��������� ����

                }

            }

            starCount = 0;

            for (i = 0; i < 25; i += 6)  // �»�� �밢�� üũ

            {

                if (Ai[i] == INT_MAX)

                    starCount++;

            }

            if (starCount < 5 && starCount > saveCount)

            {

                saveCount = starCount;

                line = xy;

            }

            starCount = 0;

            for (i = 4; i < 21; i += 4)  // �»�� �밢�� üũ

            {

                if (Ai[i] == INT_MAX)

                    starCount++;

            }

            if (starCount < 5 && starCount > saveCount)

            {

                saveCount = starCount;

                line = yx;

            }

            // ===== ����Ȯ���� ������� ���� ������ =====

            // ������ ���ο��� ���̾ƴ� ������ �����ϰ� �̴´�

            int noneSelect[4]; int noneSelectCount = 0;

            if (line < y1)  // ������ �������� ���

            {

                for (i = 0; i < 5; i++)

                {

                    if (Ai[line * 5 + i] != INT_MAX)

                    {

                        noneSelect[noneSelectCount] = Ai[line * 5 + i];

                        noneSelectCount++;

                    }

                }

                input = noneSelect[rand() % noneSelectCount];

                break;

            }

            noneSelectCount = 0;

            if (line > x5 && line < xy) // ������ �������� ���

            {

                for (i = 0; i < 5; i++)

                {

                    if (Ai[i * 5 + (line - 5)] != INT_MAX)

                    {

                        noneSelect[noneSelectCount] = Ai[i * 5 + (line - 5)];

                        noneSelectCount++;

                    }

                }

                input = noneSelect[rand() % noneSelectCount];

                break;

            }

            noneSelectCount = 0;

            if (line == xy) // ������ �»�� �밢���� ���

            {

                for (i = 0; i < 5; i++)

                {

                    if (Ai[i * 6] != INT_MAX)

                    {

                        noneSelect[noneSelectCount] = Ai[i * 6];

                        noneSelectCount++;

                    }

                }

                input = noneSelect[rand() % noneSelectCount];

                break;

            }

            noneSelectCount = 0;

            if (line == yx) // ������ ���� �밢���� ���

            {

                for (i = 0; i < 5; i++)

                {

                    if (Ai[i * 4 + 4] != INT_MAX)

                    {

                        noneSelect[noneSelectCount] = Ai[i * 4 + 4];

                        noneSelectCount++;

                    }

                }

                input = noneSelect[rand() % noneSelectCount];

                break;

            }



        }

        break;

        }

        // easy ��� or hard ��忡�� ���� input���� *�� �ٲ۴�

        for (i = 0; i < 25; i++)

        {

            if (Ai[i] == input)

            {

                Ai[i] = INT_MAX;

                break;

            }

        }

        for (i = 0; i < 25; i++)

        {

            if (Player[i] == input)

            {

                Player[i] = INT_MAX;

                break;

            }

        }

        printf("AI�� ���� : %d\nPress Enter", input);

        getchar();







        // ������� ī��Ʈ

        int star_x = 0; int star_y = 0;

        int aistar_x = 0; int aistar_y = 0;

        bingo = 0; aibingo = 0;

        for (i = 0; i < 5; i++)  // player + ai ����,���� ����üũ

        {

            star_x = 0; star_y = 0;

            aistar_x = 0; aistar_y = 0;   //���� ī��Ʈ�ϰ� �ʱ�ȭ�ؾ� �ߺ�ī��Ʈ�� �ȵ�

            for (j = 0; j < 5; j++)

            {

                if (Player[i * 5 + j] == INT_MAX)   // ���κ��� üũ

                    star_x++;

                if (Player[j * 5 + i] == INT_MAX)  // ���κ��� üũ

                    star_y++;

                if (Ai[i * 5 + j] == INT_MAX)

                    aistar_x++;

                if (Ai[j * 5 + i] == INT_MAX)

                    aistar_y++;



                if (star_x == 5)

                    bingo++;

                if (star_y == 5)

                    bingo++;

                if (aistar_x == 5)

                    aibingo++;

                if (aistar_y == 5)

                    aibingo++;

            }

        }



        // �밢�� ���� üũ

        star_x = 0; aistar_x = 0;

        for (i = 0; i < 25; i += 6)  // ������� �밢��

        {

            if (Player[i] == INT_MAX)

                star_x++;

            if (Ai[i] == INT_MAX)

                aistar_x++;

        }

        if (star_x == 5)

            bingo++;

        if (aistar_x == 5)

            aibingo++;



        star_x = 0; aistar_x = 0;

        for (i = 4; i < 21; i += 4) // ������� �밢��

        {

            if (Player[i] == INT_MAX)

                star_x++;

            if (Ai[i] == INT_MAX)

                aistar_x++;

        }

        if (star_x == 5)

            bingo++;

        if (aistar_x == 5)

            aibingo++;



    }



}