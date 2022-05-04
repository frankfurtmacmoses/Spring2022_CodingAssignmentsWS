# 

include ../../make.def

EXES=matrix_sequential$(EXE) matrix_OMP_Parallel$(EXE) 

all: $(EXES)

hello$(EXE): matrix_sequential.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o matrix_sequential matrix_sequential.$(OBJ) $(LIBS)

hello_omp$(EXE): matrix_OMP_Parallel.$(OBJ) 
	$(CLINKER) $(OMPFLAG) $(OPTFLAGS) -o matrix_OMP_Parallel matrix_OMP_Parallel.$(OBJ) $(LIBS)

run: $(EXES)
	$(PRE)matrix_sequential$(EXE) 
	$(PRE)matrix_OMP_Parallel$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
