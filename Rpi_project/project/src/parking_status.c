#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "enter_exit_manage.h"
#include "parking_status.h"

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

// parking_status_check제거예정@

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

int info_car_num(LPARRAY lpArray,char *car_num, int *flag)
{
  Car_state *tmp;
  for(int i=0; i<arraySize(lpArray);i++){
    arrayGetAt(lpArray,i,(LPDATA*) &tmp);
    if (strcmp(tmp->plate_num, car_num)==0) 
    {
      disp_car_state(tmp);
      *flag=0;
      return 0;
    }
  }  
  return 1;
}

int info_car_loc(LPARRAY lpArray, char* car_loc, int *flag)
{
  extern Car_state parking_lot[3][10][10];
  Car_state *tmp;
  for(int i=0; i<arraySize(lpArray);i++){
    arrayGetAt(lpArray,i,(LPDATA*) &tmp);
  
    int floor, row, col;
    floor = (int)car_loc[1]-(int)'0'-1;
    row = (int)car_loc[3]-(int)'0'-1;
    col = (int)car_loc[5]-(int)'0'-1;

    if(strcmp(parking_lot[floor][row][col].plate_num,"")!=0){ 
      disp_car_state(tmp);
      *flag=0;
      return 0;
    }
  }  
  return 1;
}

int parking_check(LPARRAY lpArray)
{
  extern Car_state parking_lot[3][10][10];
  int parking_check_key;
  int cErr;
  char *car_num;
  char *car_loc;
  int flag=1;
  while(flag)
  {
    printf("1: 차량번호를 입력, 2: 위치 입력, -1: 종료\n");
    char sel[5];
    scanf("%s",&sel); getchar(); //flush newline
    parking_check_key=atoi(sel); 

    switch(parking_check_key){
      case 1:
        printf("차량 번호를 형식에 맞게 입력해주세요(예시: 111가1111)");
        inputline(stdin, &car_num);
        cErr = info_car_num(lpArray, car_num, &flag);
        if(cErr){
            printf("해당 자동차는 주차장에 없습니다.\n");
        }
        break;
      case 2:
        printf("위치를 형식에 맞게 입력해주세요(예시: B1-3-3)");
        inputline(stdin, &car_loc);
        cErr = info_car_loc(lpArray, car_loc, &flag);
        if(cErr){
            printf("해당 자동차는 주차장에 없습니다.\n");
        }
        break;
      case -1:
        return 0;
    }
  }
}