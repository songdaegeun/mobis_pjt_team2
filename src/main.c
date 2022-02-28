#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "enter_exit_manage.h"

int main(void){
    //배열을 관리하는 구조체 변수를 선언
    LPARRAY lpArray = NULL; 
    int nErr = ERR_ARRAY_OK;
    //배열 구조체 메모리를 할당
    nErr = arrayCreate(&lpArray);
    if (ERR_ARRAY_OK != nErr) {
        return nErr;
    }
    Time now;
    Car_state car1={ "sonata", "red", "111가1111", {"B1",1,1}, now, now, {101,01011111111,"kim"} };
    Car_state car2={ "G70", "blue", "222가2222", {"B1",1,2}, now, now, {102,01022222222,"lee"} };
    Car_state car3={ "casper", "white", "333가3333", {"B1",1,3}, now, now, {103,01033333333,"park"} };
    
    // array.c를 참고해서 (hash table or linked list)로 연결. 
    // 프로그램 실행중에 car객체를 만들고 싶다면 
    // 기존 car를 txt에서 load하고 (hash table or linked list)에 만든 객체를 추가하는 방식을 사용하는 것이 좋아보인다. 
    
    //배열에 값을 추가
    nErr = arrayAdd(lpArray, (const LPDATA) &car1);
    if (ERR_ARRAY_OK != nErr) {
        goto exit;
    }
    nErr = arrayAdd(lpArray, (const LPDATA) &car2);
    if (ERR_ARRAY_OK != nErr) {
        goto exit;
    }
    nErr = arrayAdd(lpArray, (const LPDATA) &car3);
    if (ERR_ARRAY_OK != nErr) {
        goto exit;
    }
   
    // load() //iparking_state.txt load해서 (hash table or linked list) 생성
    do{
        printf("1. 입출차관리 \n");
        printf("2. 정산기능 \n");
        printf("3. 주차현황확인기능 \n");
        printf("4. 차량정보조회 \n");  
        printf("5. 주차이력관리 \n");
        printf("6. 빈공간추천 \n");
        printf("7. 장기주차목록 \n");
        printf("8. exit \n");
        printf("select ---> ");
        int no=0;
        scanf("%d",&no); getchar(); //flush newline
        switch(no){
            case 1:
                while(1){
                    printf("입출차 여부를 선택하세요.(-1:이전으로, 1:입차, 2:출차) \n>> ");
                    // system()  @@
                    int sel_en_ex=0;
                    scanf("%d",&sel_en_ex); getchar(); //flush newline
                    // aaa @
                    if(sel_en_ex==1){    //입차 기능
                        printf("입차하는 자동차는 몇번 자동차입니까? \n>>");
                        int car_num=0;
                        scanf("%d",&car_num); getchar(); //flush newline
                        if(car_num<1){          
                            printf("해당 자동차는 없습니다. \n");
                        } else if(car_state_append(lpArray, car_num-1)){      //(hash table or linked list)에 추가
                            printf("fail to execute car_state_append.\n");
                            return 1;   
                        }
                        
                    } else if(sel_en_ex==2){    //출차 기능
                        // printf("출차하는 자동차는 몇번 자동차입니까? \n>>");
                        // scanf("%d",&car_num);
                        // if(!car_state_remove(lpArray, car_num-1)){      //(hash table or linked list)에서 제거
                        //     printf("fail to execute car_state_remove.\n");
                        //     return 1;   
                        // }
                    } else {
                        if(sel_en_ex==-1) break;
                        printf("잘못 눌렀습니다. \n");
                    }
                }
                break;
            case 2:
                printf("정산기능 \n");
                break;
            case 3:
                printf("주차현황확인기능 \n");
                break;
            case 4:
                printf("차량정보조회 \n");
                break;
            case 5:
                printf("주차이력관리 \n");
                break;
            case 6:
                printf("빈공간추천 \n");
                break;
            case 7:
                printf("장기주차목록 \n");
                break;
            case 8:
                printf("exit function \n");
                //save()  //iparking_state.txt에 (hash table or linked list) 저장
                exit(0);
                break;
            default:
                printf("Wrong choice!!\n");
                break;
        }
    }while(1);

    return 0;
exit:
    //메모리를 해제합니다
    if (NULL != lpArray) {
        arrayDestroy(lpArray);
    }
    return nErr;
}