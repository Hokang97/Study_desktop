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

        printf("게임이 종료되었습니다.\n\n다시하려면 1, 종료하려면 1을 제외한 수를 입력해주세요");

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



    for (i = 0; i < 25; i++) // 배열에 1 ~ 25까지 숫자 넣기

    {

        Player[i] = i + 1;

        Ai[i] = i + 1;

    }

    for (i = 0; i < 100; i++) // 숫자 섞기

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

    enum SelectMode // 모드선택용

    {

        Easy = 1,

        Hard

    };

    enum Line // 하드모드 라인선택용

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

        xy, // 좌상단 대각선

        yx// 우상단 대각선



    };

    const char* mode_s = "";

    while (true)       // 난이도 선택

    {

        system("cls");

        printf("난이도를 선택해주세요\n");

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

            printf("잘못입력하셨습니다. 다시입력해주세요\n");

            getchar();

            continue;

        }

        break;

    }



    // 게임시작 



    while (true)

    {

        system("cls");

        printf("===============Player==============\n"); // 플레이어 보드판

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



        printf("================AI==================  "); // AI 보드판

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

        printf("플레이어 빙고 : %d\n", bingo);

        printf("AI 빙고 : %d\n", aibingo);

        if (bingo == 8)

        {

            printf("플레이어 승리!");

            break;

        }

        if (aibingo == 8)

        {

            printf("플레이어 패배!");

            break;

        }

        if (bingo == 8 && aibingo == 8)

        {

            printf("비겼습니다.");

            break;

        }

        printf("1 ~ 25 사이의 숫자를 입력해주세요 (게임종료 : 0) : ");

        int input;

        scanf_s("%d", &input);

        getchar();





        if (input == 0)

            break;

        if (input < 1 || input > 25) // 예외처리

        {

            printf("\n잘못입력하셨습니다. 다시입력하시려면 Enter를 눌러주세요");

            getchar();

            continue;

        }

        bool Check = true; // 중복숫자입력 확인용

        for (i = 0; i < 25; i++) // 플레이어가 입력한값을 *로 변환 - 플레이어보드

        {

            if (Player[i] == input)

            {

                Player[i] = INT_MAX;

                Check = false;

                break;

            }

        }

        for (i = 0; i < 25; i++) // 플레이어가 입력한값을 *로 변환 - ai 보드

        {

            if (Ai[i] == input)

            {

                Ai[i] = INT_MAX;

                break;

            }

        }

        if (Check)

        {

            printf("\n중복된 숫자를 입력하셨습니다. 다시입력해주세요");

            getchar();

            continue;

        }

        printf("플레이어의 선택 : %d\n", input);

        //난이도에 따라 컴퓨터의 선택값 조정

        switch (Mode)

        {

        case Easy:

        {

            int noneSelect[25]; // 선택한 숫자를 제외하고 남은숫자만 저장하는 공간

            int noneSelectCount = 0;

            for (i = 0; i < 25; i++)

            {

                if (Ai[i] != INT_MAX)

                {

                    noneSelect[i] = Ai[i];   // 별표 표시가아닌(중복숫자가 아닌) 수를 선택해서 noneSelect 배열에 순서대로 넣어준다

                    noneSelectCount++; // 배열의 길이(남은 숫자가 몇개인지)를 정한다

                }

            }

            input = noneSelect[rand() % noneSelectCount]; // 남은숫자를 저장한 배열에서 랜덤하게 숫자를 꺼내온다.

        }

        break;



        case Hard: // 빙고 성공률이 높은 숫자를 찾아서 선택한다

        {

            int starCount = 0; int saveCount = 0; int line;

            for (i = 0; i < 5; i++)  // 가로라인중 빙고가아니고 *이 가장많은 라인을 찾는다.

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

            for (i = 0; i < 5; i++)  // 세로라인중 빙고가아니고 *이 가장많은 라인을 찾는다.

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

                    line = i + 5;  // 가로라인은 0 ~ 4번 세로라인은 5 ~ 9번까지라고 설정

                }

            }

            starCount = 0;

            for (i = 0; i < 25; i += 6)  // 좌상단 대각선 체크

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

            for (i = 4; i < 21; i += 4)  // 좌상단 대각선 체크

            {

                if (Ai[i] == INT_MAX)

                    starCount++;

            }

            if (starCount < 5 && starCount > saveCount)

            {

                saveCount = starCount;

                line = yx;

            }

            // ===== 빙고확률이 가장높은 라인 설정끝 =====

            // 설정한 라인에서 별이아닌 숫자중 랜덤하게 뽑는다

            int noneSelect[4]; int noneSelectCount = 0;

            if (line < y1)  // 라인이 가로줄일 경우

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

            if (line > x5 && line < xy) // 라인이 세로줄일 경우

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

            if (line == xy) // 라인이 좌상단 대각선일 경우

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

            if (line == yx) // 라인이 우상단 대각선일 경우

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

        // easy 모드 or hard 모드에서 뽑은 input값을 *로 바꾼다

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

        printf("AI의 선택 : %d\nPress Enter", input);

        getchar();







        // 빙고라인 카운트

        int star_x = 0; int star_y = 0;

        int aistar_x = 0; int aistar_y = 0;

        bingo = 0; aibingo = 0;

        for (i = 0; i < 5; i++)  // player + ai 가로,세로 빙고체크

        {

            star_x = 0; star_y = 0;

            aistar_x = 0; aistar_y = 0;   //한줄 카운트하고 초기화해야 중복카운트가 안됨

            for (j = 0; j < 5; j++)

            {

                if (Player[i * 5 + j] == INT_MAX)   // 가로빙고 체크

                    star_x++;

                if (Player[j * 5 + i] == INT_MAX)  // 세로빙고 체크

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



        // 대각선 빙고 체크

        star_x = 0; aistar_x = 0;

        for (i = 0; i < 25; i += 6)  // 좌측상단 대각선

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

        for (i = 4; i < 21; i += 4) // 우측상단 대각선

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