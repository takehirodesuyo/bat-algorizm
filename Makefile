# 定義済みマクロの再定義
CC            = gcc
CFLAGS        = -O2 -g -Wno-unused-result #-Wall
LIBS          = -lm
# OBJS1         = myfopen.o crane_3dmodel.o neural_network.o genetic_algorithm.o crane_control.o crane-ga01.o
# PROGRAM1      = crane-ga01
OBJS2         = myfopen.o crane_3dmodel.o neural_network.o cuckoo_search.o crane_control.o crane-cs01.o
PROGRAM2      = crane-cs01
# OBJS3         = myfopen.o crane_3dmodel.o neural_network.o firefly_algorithm.o crane_control.o crane-fa01.o
# PROGRAM3      = crane-fa01
#OBJS3         = myfopen.o runge_kutta.o neural_network.o genetic_algorithm.o crane-nc02.o
#PROGRAM3      = crane-nc02
#OBJS4         = crane-verf01.o 
#PROGRAM4      = crane-verf01
#OBJS5         = crane-verf02.o 
#PROGRAM5      = crane-verf02

.PHONY: all
all:	$(PROGRAM1) $(PROGRAM2) $(PROGRAM3)

# サフィックスルール適用対象の拡張子の定義
.SUFFIXES: .c .o

# プライマリターゲット
$(PROGRAM1): $(OBJS1)
	$(CC) -o $(PROGRAM1) $^ $(LIBS)
$(PROGRAM2): $(OBJS2)
	$(CC) -o $(PROGRAM2) $^ $(LIBS)
$(PROGRAM3): $(OBJS3)
	$(CC) -o $(PROGRAM3) $^ $(LIBS)
#$(PROGRAM4): $(OBJS4)
#	$(CC) -o $(PROGRAM4) $^ $(LIBS)
#$(PROGRAM5): $(OBJS5)
#	$(CC) -o $(PROGRAM5) $^ $(LIBS)

# サフィックスルール
.c.o:
	$(CC) $(CFLAGS) -c $<

# ファイル削除用ターゲット
.PHONY: clean
clean:
	$(RM) $(PROGRAM1) $(OBJS1) $(PROGRAM2) $(OBJS2) $(PROGRAM3) $(OBJS3) $(PROGRAM4) $(OBJS4) $(PROGRAM5) $(OBJS5) *.dat

# ヘッダファイルの依存関係
crane_3dmodel.o: crane.h
neural_network.o: nn.h
genetic_algorithm.o:nn.h ga.h
cuckoo_search.o:crane.h nn.h cuckoo.h
firefly_algorithm.o:crane.h nn.h firefly.h
crane_control.o:nn.h crane.h
crane-ga01.o: crane.h nn.h ga.h
crane-cs01.o: crane.h nn.h cuckoo.h
crane-fa01.o: crane.h nn.h firefly.h