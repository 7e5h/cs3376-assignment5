int initfunc(int *array, int len) {
  int i;
  for(i=1; i <= len; i++) {
    array[i] = i;
  }
 return 0;
}

int main(int argc, char* argv[]){

  int*  myarray=new int[10];
  initfunc(myarray,10);
}
