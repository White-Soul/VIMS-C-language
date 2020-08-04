main:main.o lnitialize.o violation.o payment.o Help.o
	gcc main.o lnitialize.o violation.o payment.o Help.o -o main
main.o:main.c
	gcc -c main.c
lnitialize.o:lnitialize.c
	gcc -c lnitialize.c
violation.o:violation.c
	gcc -c violation.c
payment.o:payment.c
	gcc -c payment.c
Help.o:Help.c
	gcc -c Help.c
.PHONY:clean

clean:
	@echo "======clean project======"
	del *.o
	@echo "======clean conpleted======"