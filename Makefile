TARGETSS := testTarget


run:
	@echo $(TARGETSS)
	gcc hello.c -o hello.a

$(info #makefile start#)
TARGETSS += testTarget2