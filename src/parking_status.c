#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "enter_exit_manage.h"
// #include "parking_status.h"

int init_parking_lot(LPARRAY lpArray,Car_state parking_lot[3][10][10])
{
  printf("배열 초기화 시작");
  getchar();
  // 주차장을 표현할 3차원 배열

  Car_state* tmp; // lpArray에 있는 차 한대에 대한 정보를 받아옴
  int nErr;  // Error code
  int floor, row, col; // 차의 위치에 대한 정보 저장

  // lpArray 내의 정보를 읽어와서 주차장에 배열에 배치
  for(int i=0;i<arraySize(lpArray);i++){
    nErr = arrayGetAt(lpArray, i, (LPDATA*) &tmp);
    if (nErr){
        printf("Error while loading lpArray\n");
        return 1;
    }
    floor = (int)(tmp->location.floor[1]) - (int)'0' - 1;
    row = (int)(tmp->location.row)-1;
    col = (int)(tmp->location.col)-1;
    // parking_lot[floor][row][col] = *tmp;
    printf("%d %d %d\n", floor,row,col);
    parking_lot[floor][row][col] = *tmp;
    // ppl[floor][row][col] = *tmp;
  }

 for(int i=0;i<3;i++){
        for(int j=0;j<10;j++){
            for(int k=0;k<10;k++){
                printf("%d", parking_lot[i][j][k].location.row);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
    }
  getchar();
}

int parking_status_check(LPARRAY lpArray, Car_state parking_lot[3][10][10])
{
  int floor;
  printf("안내받을 층을 입력해주세요 : ");
  scanf("%d", &floor);getchar();

  if (floor == -1){
    return 0;
  }


  printf("### %d층 ###\n",floor);
  printf("┌────────────────────────────────────────────┐\n");
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        if (parking_lot[floor-1][i][j].location.floor == ""){
          printf("O");
        }
        else{
          // printf("%s", parking_lot[floor-1][i][j].plate_num);
          printf("X");
        }
      }
      printf("\n");
      printf("──────────────────────────────────────────────\n");
      printf("\n");
    }
  printf("└────────────────────────────────────────────┘\n");
    printf("\n\n");
 }


int inputline(FILE* fp, char** str)
{
  static char line[256];
  int i;
  for (i=0;i<256;i++){
    line[i] = fgetc(fp);
    if (line[i] == '\n'){
      break;
    }
    if (line[i] == EOF){
      break;
    }
  }
  line[i] = '\0';

  // static 지역변수의 주소를 반환 -> 다른 함수에서 사용 가능
  *str = line;
  return 0;
  // return line;
}

int info_car_num(LPARRAY lpArray,char* car_num)
{
  Car_state *tmp;
  for(int i=0; i<arraySize(lpArray);i++){

  arrayGetAt(lpArray,i,(LPDATA*) &tmp);
    if (strcmp(tmp->plate_num, car_num)==0) // 두 문자열이 같으면 0 반환
        {
        printf("%s %s %s %s %d %d\n", tmp->car_type, tmp->color, tmp->plate_num, tmp->location.floor, tmp->location.row, tmp->location.col);
        return 0;
        }
  }  
  return 1;
}

int info_car_loc(LPARRAY lpArray, Car_state parking_lot[3][10][10], char* car_loc)
{
    Car_state *tmp;
    for(int i=0; i<arraySize(lpArray);i++){
        arrayGetAt(lpArray,i,(LPDATA*) &tmp);
        // printf("%s\n", car_loc);
        int floor, row, col;
        floor = (int)car_loc[1]-(int)'0'-1;
        row = (int)car_loc[3]-(int)'0'-1;
        col = (int)car_loc[5]-(int)'0'-1;

        printf("%d %d %d \n", floor, row, col);

        if (parking_lot[floor][row][col].plate_num != NULL){ // 두 문자열이 같으면 0 반환
            printf("%s %s %s %s %d %d\n", tmp->car_type, tmp->color, tmp->plate_num, tmp->location.floor, tmp->location.row, tmp->location.col);
            return 0;
        }
    }  
  return 1;
}

int parking_check(LPARRAY lpArray, Car_state parking_lot[3][10][10])
{
  int parking_check_key;
  int cErr;
  char *car_num;
  char *car_loc;
  while(1)
  {
    printf("1. 차량번호를 입력하시겠습니까?\n");
    printf("2. 위치를 입력하시겠습니까?\n");
    scanf("%d", &parking_check_key);getchar();

    switch(parking_check_key){
      case 1:
        printf("차량 번호를 형식에 맞게 입력해주세요(예시 : 111가1111)");
        inputline(stdin, &car_num);
        cErr = info_car_num(lpArray, car_num);
        if(cErr){
            printf("Matching car not found\n");
        }
        break;
      case 2:
        printf("위치를 형식에 맞게 입력해주세요(예시 : B1-3-3)");
        inputline(stdin, &car_loc);
        cErr = info_car_loc(lpArray, parking_lot, car_loc);
        if(cErr){
            printf("Matching car not found\n");
        }
        break;
      case -1:
        return 0;
    }
  }
}
